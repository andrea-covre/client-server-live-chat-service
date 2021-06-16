//
// Created by Andrea Covre on 3/10/21.
//

#ifndef chatclient_h
#define chatclient_h

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<ctype.h>
#include<signal.h>

char ip_address[] = "127.0.0.1";
int port_number = 80;
int status = 0;
int socket_desc;
struct sockaddr_in server;
char username[20];
char password[20];
char auth_token[41];
char server_password[] = "secret-password";

int message_limit = 1024+1;

void *receiver_handler(void *socket);
void printRed(char *string);
void printMagenta(char *string);
void printBlue(char *string);
void printYellow(char *string);

#endif