#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void launch(struct Server *server){

    char buffer[30000];

    while(1){

    printf(" ===== WAITING FOR A CONNECTION ======\n ");

    int address_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);

    char *hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win 32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type:text/html\nConnection: Closed\n\n<html><body><h1>Hello Vimansa</h1></body></html>";

    write(new_socket, hello, strlen(hello));
    close(new_socket);

    }

}

int main(){

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0 , INADDR_ANY, 5000, 10, launch);
    server.launch(&server);

}
