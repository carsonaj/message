#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT_NUM 18000
#define BUF_SIZE 100 

int main(int arc, char **argv) {

    // **variables**

    // buffer for data
    char buf[BUF_SIZE];

    // server socket file descriptors
    int srv_fd; // 
    int conn_fd;
    
    // server/client socket IPv6 address structures
    struct sockaddr_in6 srv_addr, cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    //******************************************************************************

    // **set server address**

    // set all server address bytes in memory to 0
    memset(&srv_addr, 0, sizeof(struct sockaddr_in6));
    srv_addr.sin6_family = AF_INET6;

    // convert port number from host byte order to network byte order
    srv_addr.sin6_port = htons(PORT_NUM);

    // set server address to wild card IPv6 address to receive 
    // connections from any client IPv6 address
    srv_addr.sin6_addr = in6addr_any;
    //******************************************************************************

    // **create server**

    // create server socket file descriptor:
    srv_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (srv_fd == -1)
        exit(EXIT_FAILURE);


    // bind server socket to address:
    if (bind(srv_fd, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) == -1)
        exit(EXIT_FAILURE);


    // mark server socket as passive and listen for connections:
    if (listen(srv_fd, 3) == -1)
        exit(EXIT_FAILURE);
    //******************************************************************************

    // **upon accepting a connection, assign a thread for I/O**

    while (1)
    {
        // accept connections
        conn_fd = accept(srv_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (conn_fd == -1)
            exit(EXIT_FAILURE);
        
        // read data from client
        if(read(conn_fd, buf, BUF_SIZE - 1) == -1)
            exit(EXIT_FAILURE);
        buf[BUF_SIZE] = '\0';

        printf("%s", buf);

    }
    

    return 0;
}

