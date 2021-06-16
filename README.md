# Client-Server Live Chat Service

## =========================== OVERVIEW ===========================

> Title: Programming Assignment #1
> Author: Andrea Covre
> GT Username: acovre3
> Email: andrea.covre@icloud.com
> GT Email: andrea.covre@gatech.edu
> Date: March 10th, 2021
> Class: CS 3251
> Section: B


## ======================== FILES INCLUDED ========================

- chatclient.h
    header file for the chat client (C)

- chatclient.c
    source file for the chat client (C)

- chatserver.h
    header file for the chat server (C)

- chatserver.c
    source file for the chat server (C)

- Makefile
    file to compile the executable server and client files

- README.txt
    documentation with description and instruction

- README.md
    documentation with description, images and instruction


## ==================== COMPILING INSTRUCTIONS ====================

* To build the executables for both chatclient and chatserver
  run the following command from the terminal inside the project
  directory:
    ```
    $ make
    ```

* To delete the executable files you can run:
    ```
    $ make clean
    ```


## ===================== RUNNING INSTRUCTIONS =====================

* First run the chatserver executable with the following
  usage:
  ```
    $ ./chatserver [port_number]
    $ ./chatserver 5001
  ```

* To run a client executable use:
  ```
    $ ./chatclient [port_number] [username] [password]
    $ ./chatclient 5001 andy cs3251secret
  ```


## =========================== OUTPUTS ============================

- serveroutput.txt
    complete log of the chat from the server view with
    logins/logouts and messages received (shortcuts
    will be displayed as received by the client, therefore
    not yet transformed);


## ======================== SPECIFICATIONS ========================

> C Standard: C99
> Compiler: GCC
> IP address: 127.0.0.1 (hardcoded)
> Password: cs3251secret (hardcoded)
> Max length of message inputtable by the client: 1024 characters
> Edited with: CLion 2020.2.4
> Written on: MacOS 11.2.1
> Tested on:
            - MacOS 11.2.1
            - Ubuntu 18.04


## ======================== LIBRARIES USED ========================

+ arpa/inet
+ ctype         (C Standard Library)
+ pthread
+ signal        (C Standard Library)
+ stdio         (C Standard Library)
+ stdlib        (C Standard Library)
+ string        (C Standard Library)
+ sys/socket
+ time          (C Standard Library)
+ unistd

