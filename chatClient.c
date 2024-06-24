/* 20195914 */
/* Jeong eui chan */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/select.h>
#include <netdb.h>
#include <errno.h>

#define PORT 2222
#define BUFFER_SIZE 1024

int sock = 0;


// Signal handler: Handles the SIGINT signal (Ctrl+C) to send a shutdown message to the server and close the socket.
void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\ngg~\n");
        send(sock, "\\quit\n", strlen("\\quit\n"), 0);
        close(sock);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <nickname>\n", argv[0]);
        return 1;
    }

    struct addrinfo hints, *res;
    char *nickname = argv[1];
    char buffer[BUFFER_SIZE];

    signal(SIGINT, handle_signal);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Get server address information
    int err = getaddrinfo("211.214.22.211", NULL, &hints, &res);
    if (err != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(err));
        return 1;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    ipv4->sin_port = htons(PORT);

    if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        printf("Socket creation error\n");
        freeaddrinfo(res);
        return 1;
    }

    /*여기에 1*/

   /*여기에 2*/

   /*여기에 3*/

   /*여기에 4*/

    close(sock);
    return 0;
}
