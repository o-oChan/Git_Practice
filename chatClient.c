#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/select.h>
#include <netdb.h>
#include <errno.h>

#define PORT 25914
#define BUFFER_SIZE 1024

int sock = 0;



void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\ngg~\n");
        send(sock, "\\quit\n", strlen("\\quit\n"), 0);
        close(sock);
        exit(0);
    }
}