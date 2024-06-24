void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\ngg~\n");
        send(sock, "\\quit\n", strlen("\\quit\n"), 0);
        close(sock);
        exit(0);
    }
}