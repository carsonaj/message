#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT_NUM 18000
#define BUF_SIZE 50

int main(int arc, char **argv) {

    // **variables**

    // client socket file descriptors
    int cli_fd;

    // buffer for client data
    char buf[BUF_SIZE];

    // target server socket IPv6 address structure
    struct sockaddr_in6 srv_addr;

    // target server IPv6 address string
    char srv_addr_str[INET6_ADDRSTRLEN];
    //******************************************************************************

    // **set target server address**

    // set all target server address structure bytes in memory to 0
    memset(&srv_addr, 0, sizeof(struct sockaddr_in6));
    srv_addr.sin6_family = AF_INET6;

    // convert port number from host byte order to network byte order 
    // and set target server address structure port number
    srv_addr.sin6_port = htons(PORT_NUM);

    // convert IPv6 host address in string representation to binary representation and 
    // set target server address structure IPv6 address
    inet_pton(AF_INET6, "::1", &srv_addr.sin6_addr);
    //******************************************************************************

    // **create and connect client to target server**

    // create client socket file descriptor:
    cli_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (cli_fd == -1)
        exit(EXIT_FAILURE);

    // connect client socket to target server socket
     if (connect(cli_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
         exit(EXIT_FAILURE);
    //******************************************************************************

    // **client to server IO**
     
    // write argv[1] from client socket to server socket
    if(write(cli_fd, argv[1], BUF_SIZE) == -1)
        exit(EXIT_FAILURE);

    return 0;
}

