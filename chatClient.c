// 최종본


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

    // create socket
    if (connect(sock, (struct sockaddr *)ipv4, sizeof(*ipv4)) < 0) {
        printf("Connection Failed\n");
        close(sock);
        freeaddrinfo(res);
        return 1;
    }

    freeaddrinfo(res);

    // Send nickname
    if (send(sock, nickname, strlen(nickname), 0) == -1) {
        perror("send");
        close(sock);
        return 1;
    }
    if (send(sock, "\n", 1, 0) == -1) {
        perror("send");
        close(sock);
        return 1;
    }

    fd_set readfds;
    int max_sd = (sock > STDIN_FILENO) ? sock : STDIN_FILENO;

// Main loop: Process data from input and socket
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            perror("select error");
        }

        // (1)번 작성 줄
       

        // (2)번 작성 줄
    }


    close(sock);
    return 0;
}

