//
// Created by Andrea Covre on 3/6/21.
//

#ifndef chatserver_h
#define chatserver_h

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<signal.h>

void *connection_handler(void *);
void *receiver_handler(void *);

void printRed(char *string);
void printYellow(char *string);
void printMagenta(char *string);
void printBoldGreen(char *string);

int port_number = 5001;

struct connection_t
{
    int p_sock;
    int status;
    int auth;
    char username[50];
    struct connection_t *next;
};

struct connection_t *head;
struct connection_t *tail;
int open_connections = 0;

void add_socket(struct connection_t *socket);
void delete_socket(struct connection_t *socket);
void broadcast(struct connection_t *socket, char *message, int type);

FILE *fp;
void INThandler(int);
char output_file_name[] = "serveroutput.txt";

#endif