#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

enum { SIZE = 2000 };

void print_ip_and_port(struct addrinfo *lst) {
    struct sockaddr_in* addr4 = (struct sockaddr_in*)(lst->ai_addr);
    struct sockaddr_in* min_addr4 = addr4;

    for (struct addrinfo* cur = lst; cur != NULL; cur = cur->ai_next) {
        addr4 = (struct sockaddr_in*)(cur->ai_addr);
        if (ntohl(min_addr4->sin_addr.s_addr) > ntohl(addr4->sin_addr.s_addr)) {
            min_addr4 = addr4;
        }
    }

    printf("%s:%u\n", inet_ntoa(min_addr4->sin_addr), ntohs(min_addr4->sin_port));
    freeaddrinfo(lst);
}

int main() {
    char host[SIZE];
    char service[SIZE];

    int res;
    while ((res = scanf("%1999s %1999s", host, service)) == 2) {
        struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
        struct addrinfo *addrs = NULL;
        int res1 = getaddrinfo(host, service, &hints, &addrs);
        if (res1 != 0) {
            printf("%s\n", gai_strerror(res1));
            continue;
        }
        print_ip_and_port(addrs);
    }
    if (res != EOF) {
        return 1;
    }
}

// https://stackoverflow.com/questions/19817425/how-to-get-ip-addresses-from-sockaddr thoughts