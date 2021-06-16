//
// Created by Andrea Covre on 3/6/21.
//

#include"chatserver.h"

int main(int argc , char *argv[]) {
    if (argc <= 1) {
        printRed("Error: pass in the port number to bind to (e.g. ./chatserver 8080)\n");
        return 1;
    }
    if (argc > 2) {
        printRed("Error: only pass the port number to bind to (e.g. ./chatserver 8080)\n");
        return 1;
    }

    port_number = atoi(argv[1]);
    if (port_number < 1024) {
        printRed("Error: invalid port number\n");
        return 1;
    }

    int socket_desc , new_socket , c , *new_sock;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( port_number );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }
    //puts("bind done");

    fp  = fopen (output_file_name, "w");
    signal(SIGINT, INThandler);

    printMagenta("~~~ You have entered The Chat Room ~~~\n");
    fputs("~~~ You have entered The Chat Room ~~~\n", fp);

    //Listen
    listen(socket_desc , 5);

    //Accept and incoming connection
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        //puts("Connection accepted");

        struct connection_t *new_connection = (struct connection_t *) (struct connection *) malloc(
                sizeof(struct connection_t));
        new_connection->p_sock = new_socket;
        new_connection->status = 1;
        new_connection->auth = 0;
        add_socket(new_connection);

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_connection);

    }

    if (new_socket<0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *p_connection) {
    struct connection_t *connection = (struct connection_t*)p_connection;
    int dummy = 0;

    pthread_t receiving_thread;

    if( pthread_create( &receiving_thread , NULL ,  receiver_handler , (void*) p_connection) > 0) {
        perror("could not create receving thread");
        return 0;
    }

    while(connection->status) {
        dummy++;
    }

    //Free the socket pointer
    //printf("Terminating socket %d\n", connection->p_sock);
    broadcast(p_connection, "", 2);
    delete_socket(p_connection);
    free(p_connection);

    return 0;
}

/*
 * This will handle the receiver from each client
 * */
void *receiver_handler(void *p_connection) {
    struct connection_t *connection = (struct connection_t*)p_connection;
    //Get the socket descriptor
    int sock = connection->p_sock;
    char username[20];
    char token[41];

    //Get the socket descriptor
    int read_size;
    char client_message[2000];
    char processed_client_message[2000];

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        if (!connection->auth) {
            strcpy(token, client_message);

            char ch = token[0];
            int i = 0;
            while (ch != '\n' && ch != '\0') {
                username[i] = ch;
                i++;
                ch = token[i];
            }
            username[i] = '\0';
            strcpy(connection->username, username);

            printBoldGreen(connection->username);
            printBoldGreen(" has joined\n");
            fprintf(fp, "%s has joined\n", connection->username);

            broadcast(connection, "", 1);

            connection->auth = 1;

        } else {
            int ie = 0;
            for (int i = 0; i <= strlen(client_message); i++) {
                if (client_message[i] == '\n') {
                    client_message[i] = '\0';
                }
                processed_client_message[i] = client_message[i];
                ie = i;
            }

            printf("%s: %s\n", connection->username, processed_client_message);
            fprintf(fp, "%s: %s\n", connection->username, processed_client_message);

            processed_client_message[ie] = '\n';
            processed_client_message[ie+1] = '\0';

            broadcast(connection, processed_client_message, 0);
        }
    }

    if(read_size == 0) {
        //puts("Client disconnected");
        printYellow(connection->username);
        printYellow(" has left\n");
        fprintf(fp, "%s has left\n", connection->username);

        fflush(stdout);

    } else if(read_size == -1) {
        perror("recv failed");
    }

    connection->status = 0;

    return 0;
}

void printRed(char *string) {
    printf("\033[1;31m");
    printf("%s", string);
    printf("\033[0m");
}

void printYellow(char *string) {
    printf("\033[1;33m");
    printf("%s", string);
    printf("\033[0m");
}

void printMagenta(char *string) {
    printf("\033[1;35m");
    printf("%s", string);
    printf("\033[0m");
}

void printBoldGreen(char *string) {
    printf("\033[1;32m");
    printf("%s", string);
    printf("\033[0m");
}

void add_socket(struct connection_t *socket) {
    if (open_connections == 0) {
        socket->next = NULL;
        head = socket;
        tail = socket;
        open_connections++;

    } else if (open_connections > 0) {
        tail->next = socket;
        socket->next = NULL;
        tail = socket;
        open_connections++;
    }
}

void delete_socket(struct connection_t *socket) {
    if (open_connections == 1 && socket == head) {
        head = NULL;
        open_connections--;

    } else if (socket == head) {
        head = head->next;
        open_connections--;

    } else if (open_connections > 1) {

        struct connection_t *currentSocket = head;
        while (currentSocket->next != socket && currentSocket->next != NULL) {
            currentSocket = currentSocket->next;
        }

        if (tail == socket) {
            tail = currentSocket;
            currentSocket->next = NULL;

        } else {
            currentSocket->next = currentSocket->next->next;

        }
        open_connections--;
    }
}

void broadcast(struct connection_t *socket, char *message, int type) {
    char signed_message[strlen(socket->username) + 2 + strlen(message)];
    int size = strlen(socket->username) + 2;
    strcpy(signed_message, socket->username);

    if (type == 0) {        //message type
        strcat(signed_message, ": ");

        char happy_code[] = ":)\n";
        char sad_code[] = ":(\n";
        char mytime_code[] = ":mytime\n";
        char extrahour_code[] = ":+1hr\n";
        char exit_code[] = ":Exit\n";

        if (strcmp(happy_code, message) == 0) {
            strcat(signed_message, "[feeling happy]\n");
            size += strlen("[feeling happy]\n");

        } else if (strcmp(sad_code, message) == 0) {
            strcat(signed_message, "[feeling sad]\n");
            size += strlen("[feeling sad]\n");

        } else if (strcmp(mytime_code, message) == 0) {
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );

            char time_string[40] = "";
            sprintf(time_string, "%s\n", asctime (timeinfo));

            strcat(signed_message, time_string);
            size += strlen(time_string);


        } else if (strcmp(extrahour_code, message) == 0) {
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            timeinfo->tm_hour = timeinfo->tm_hour + 1;

            char time_string[40] = "";
            sprintf(time_string, "%s\n", asctime (timeinfo));

            strcat(signed_message, time_string);
            size += strlen(time_string);

        } else if (strcmp(exit_code, message) == 0) {
            socket->status = 0;
            shutdown(socket->p_sock, 2);
            return;

        } else {
            strcat(signed_message, message);
            size += strlen(message);
        }
        strcat(signed_message, "\0");

    } else if (type == 1) {         //Log in type
        strcat(signed_message, " has joined\n");
        size += strlen(" has joined\n");

    } else if (type == 2) {         //Log out type
        strcat(signed_message, " has left\n");
        size += strlen(" has left\n");
    }

    struct connection_t *currentSocket = head;
    int i = 0;
    while (i < open_connections) {

        if(socket != currentSocket) {
            write(currentSocket->p_sock, signed_message , size);
        }
        currentSocket = currentSocket->next;
        i++;
    }
}

void INThandler(int sig) {
    printYellow("\nDisconnected\n");
    fclose(fp);
    exit(0);
}
