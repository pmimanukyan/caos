#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

enum {SIZE = 2000};
int sfd;

void handler(int signum) {
    close(sfd);
    exit(0);
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    int port = atoi(argv[1]);

    struct sigaction str;
    str.sa_handler = handler;
    str.sa_flags = SA_RESTART;

    if (sigaction(SIGTERM, &str, NULL) < 0) {
        perror("sigaction");
        return 1;
    }


    sfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("socket");
        exit(1);
    }

    int val = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(port);
    if (bind(sfd, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(sfd, 1) < 0) {
        perror("listen");
        exit(1);
    }

    long long k = 0;

    while (1) {
        char buf[SIZE];
        struct sockaddr_in ss;
        socklen_t size = sizeof(ss);

        int afd = accept(sfd, (struct sockaddr *) &ss, &size);
        if (afd < 0) {
            perror("accept");
            close(sfd);
            return 1;
        }

        FILE* f = fdopen(afd, "r+");
        if (f == NULL) {
            perror("open");
            close(sfd);
            return 1;
        }

        long long bytes;
        int flag = 1;
        while ((bytes = read(afd, buf, SIZE)) > 0) {
            flag = 0;
            if (write(afd, buf, bytes) != bytes) {
                perror("write");
                close(sfd);
                return 1;
            }
        }
        if (flag && bytes == 0) {
            fprintf(f, "Empty message #%lld\n", ++k);
            fflush(f);
        } else if (bytes == -1) {
            perror("read");
            close(sfd);
            return 1;
        }
        fclose(f);
        close(afd);
    }
}