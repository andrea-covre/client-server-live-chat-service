//
// Created by Andrea Covre on 3/6/21.
//

#include"chatclient.h"

int main(int argc , char *argv[]) {
    if (argc <= 3) {
        printRed("Error: pass in the port number to connect to, username and password "
                 "(e.g. ./chatclient 8080 user1 xxxxx)\n");
        return 1;
    }
    if (argc > 4) {
        printRed("Error: only pass the port number to connect to, username and password "
                 "(e.g. ./chatclient 8080 user1 xxxxx)\n");
        return 1;
    }

    port_number = atoi(argv[1]);
    if (port_number < 1024) {
        printRed("Error: invalid port number\n");
        return 1;
    }

    if (strlen(argv[2]) > 20) {
        printRed("Error: the username cannot exceed 20 characters\n");
        return 1;
    }

    if (strlen(argv[3]) > 20) {
        printRed("Error: the password cannot exceed 20 characters\n");
        return 1;
    }
    strcpy(username, argv[2]);
    strcpy(password, argv[3]);
    char ch = username[0];
    int i = 0;

    while (ch != '\0') {
        if (isalnum(ch)) {
            i++;
        } else {
            printRed("Error: only alphanumeric usernames are allowed\n");
            return 1;
        }
        ch = username[i];
    }

    if (strcmp(password, server_password) != 0) {
        printRed("Login error: the password is not correct\n");
        return 1;
    }

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port_number);

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
        puts("connect error");
        return 1;
    }

    status = 1;
    printMagenta("~~~ You have entered The Chat Room ~~~\n");

    pthread_t receiving_thread;
    int new_socket = socket_desc;
    int *new_sock;
    new_sock = malloc(1);
    *new_sock = new_socket;

    pthread_create( &receiving_thread , NULL ,  receiver_handler , (void*) new_sock);

    strcpy(auth_token, username);
    strcat(auth_token, "\n");

    //sending auth token
    if( send(socket_desc , auth_token , strlen(auth_token) , 0) < 0) {
        puts("Log in failed");
        return 1;
    }

    while (status) {
        char str[message_limit];
        fgets(str, message_limit+2, stdin);
        if(!status) {
            return 0;
        }
        if (str[0] == '\0' || str[0] == '\n') {
            printRed("Error: you can't send an empty message!\n");
            fflush(stdin);

        } else {
            fflush(stdin);
            if (strlen(str) > message_limit) {
                printRed("Error: your message cannot exceed 1024 characters\n");

            } else {
                if( send(socket_desc , str , strlen(str) , 0) < 0) {
                    puts("Send failed");
                    return 1;
                }
            }
        }
    }
    return 0;
}

/*
 * This will handle the receiver for the client
 * */
void *receiver_handler(void *socket) {
    //Get the socket descriptor
    int sock = *(int*)socket;
    int read_size;
    char server_message[2000];
    char processed_server_message[2000];

    //Receive a message from client
    while( (read_size = recv(sock , server_message , 2000 , 0)) > 0 ) {
        int ie = 0;
        for (int i = 0; i <= strlen(server_message); i++) {
            if (server_message[i] == '\n') {
                server_message[i] = '\0';
            }
            processed_server_message[i] = server_message[i];
            ie = i;
        }
        printBlue(processed_server_message);
        printf("\n");
        processed_server_message[ie] = '\n';
    }

    if(read_size == 0) {
        printYellow("Server disconnected\n");
        exit(0);
    } else if(read_size == -1) {
        perror("recv failed");
    }

    status = 0;

    //Free the socket pointer
    free(socket);

    return 0;
}

void printRed(char *string) {
    printf("\033[1;31m");
    printf("%s", string);
    printf("\033[0m");
}

void printMagenta(char *string) {
    printf("\033[1;35m");
    printf("%s", string);
    printf("\033[0m");
}

void printBlue(char *string) {
    printf("\033[0;36m");
    printf("%s", string);
    printf("\033[0m");
}

void printYellow(char *string) {
    printf("\033[1;33m");
    printf("%s", string);
    printf("\033[0m");
}
