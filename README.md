# Client-Server Live Chat Service

## OVERVIEW

**Title:** Client-Server Live Chat Service
<br>
**Author:** Andrea Covre
<br>
**Email:** andrea.covre@icloud.com
<br>
**Date:** March 10th, 2021
<br>

## DEMO

![Server DEMO by Andrea Covre](/figures/server.gif "Server DEMO")
<img src="/figures/client-1.gif" alt="Client 1 DEMO by Andrea Covre" width="250"/>
<img src="/figures/client-2.gif" alt="Client 2 DEMO by Andrea Covre" width="250"/>
<img src="/figures/client-3.gif" alt="Client 3 DEMO by Andrea Covre" width="250"/>

<!--
![Client 1 DEMO by Andrea Covre](/figures/client-1.gif "Client 1")
![Client 2 DEMO by Andrea Covre](/figures/client-2.gif "Client 2")
![Client 3 DEMO by Andrea Covre](/figures/client-3.gif "Client 3")
-->

## SHORTCUTS CODES

- `:)` → [feeling happy]
- `:(` → [feeling sad]
- `:mytime` → current time
- `:+1hr` → current time plus one hour
- `:Exit` → exit the chat

![Shortcuts codes DEMO by Andrea Covre](/figures/shortcuts-demo.gif "Shortcuts codes DEMO")

## FILES INCLUDED

- `chatclient.h`
<br>
    header file for the chat client (C)

- `chatclient.c`
<br>
    source file for the chat client (C)

- `chatserver.h`
<br>
    header file for the chat server (C)

- `chatserver.c`
<br>
    source file for the chat server (C)

- `Makefile`
<br>
    file to compile the executable server and client files

- `README.md`
<br>
    documentation with description, images and instruction


## COMPILING INSTRUCTIONS

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


## RUNNING INSTRUCTIONS

* First run the chatserver executable with the following
  usage:
  ```
    $ ./chatserver [port_number]
  ```
  e.g.
  ```
    $ ./chatserver 5001
  ```

<br>

* To run a client executable use:
  ```
    $ ./chatclient [port_number] [username] [password]
  ```
  e.g.
  ```
    $ ./chatclient 5001 andy secret-password
  ```

## OUTPUTS

- serveroutput.txt
    complete log of the chat from the server view with
    logins/logouts and messages received (shortcuts
    will be displayed as received by the client, therefore
    not yet transformed);


## SPECIFICATIONS

- C Standard: C99
- Compiler: GCC
- IP address: 127.0.0.1 (hardcoded)
- Password: secret-password (hardcoded)
- Max length of message inputtable by the client: 1024 characters
- Edited with: CLion 2020.2.4
- Written on: MacOS 11.2.1
- Tested on:
<br>
                  - MacOS 11.2.1
<br>
                  - Ubuntu 18.04


## LIBRARIES USED

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

