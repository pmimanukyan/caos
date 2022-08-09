#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/file.h>


enum {
    MAX = 100,
    BUFFER_SIZE = 1024,
};

struct Node {
    int fd;
    char query[MAX];
    struct Node *next;
};

void insert_node(struct Node *head, int fd, char query[MAX]) {
    struct Node *new_node = calloc(1, sizeof(*new_node));
    if (new_node == NULL) {
        exit(1); // safe_end()
    }
    new_node->fd = fd;
    memcpy(new_node->query, query, sizeof(new_node->query));
    new_node->next = NULL;
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void print_list_queries(struct Node *head) {
    struct Node *temp = head;
    printf("list queries:");
    while (temp != NULL) {
        printf("%s\n", temp->query);
        temp = temp->next;
    }
}

int find_and_print(struct Node *head, char query[MAX]) {
    struct Node *temp = head;
    while (temp != NULL) {
        if (!strcmp(temp->query, query)) {
            printf("FOUND!\n");
            FILE *fp = fdopen(temp->fd, "r");
            char c;
            lseek(temp->fd, 0, 0);
            while ((c = getc(fp)) != EOF) printf("%c", c);
            printf("\n");
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void safe_end(struct Node *head) {
    struct Node *current = head;
    struct Node *next;
    while (current != NULL) {
         next = current->next;
         close(current->fd);
         free(current);
         current = next;
    }
    head = NULL;
}

// Chat between client and server
void func(int connfd) {
    int file_index = 0;
    printf("\n\nSTART START START START START START START START START START\n\n");
    struct Node *head = calloc(1, sizeof(*head));
    if (head == NULL) {
        exit(1);
    }
    head->next = NULL;

    // infinite loop for chat
    while(1) {
        ++file_index;
        char query[MAX];
        bzero(query, MAX);
        read(connfd, query, sizeof(query));
        char query_copy[MAX];
        strcpy(query_copy, query);

        printf("query -- %s\n", query_copy);
        print_list_queries(head);

        if (!find_and_print(head, query_copy)) {
            char host[MAX], uri[MAX];
            char *part = strtok(query, " ");
            strcpy(host, part);
            while (part != NULL) {
                strcpy(uri, part);
                part = strtok(NULL, " ");
            }
            printf("host = %s\n", host);
            printf("uri = %s\n", uri);
            int fd1 = socket(AF_INET, SOCK_STREAM, 0);

            struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
            struct addrinfo *addrs = NULL;
            int res = getaddrinfo(host, "http", &hints, &addrs);
            if (res) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
                safe_end(head);
                exit(1);
            }
            if (connect(fd1, addrs->ai_addr, sizeof(struct sockaddr_in)) < 0) {
                printf("connect problem");
                safe_end(head);
                exit(1);
            }

            char header[BUFFER_SIZE] = {0};
            sprintf(header, "GET %s HTTP/1.0\r\nHost: www.%s\r\n\r\n", uri, host);
            write(fd1, header, strlen(header));

            char buffer[BUFFER_SIZE] = {0};

            char file_name[20];
            sprintf(file_name, "%d.txt", file_index);
            int file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
            if (file_fd < 0) {
                printf("fd creation problem");
                safe_end(head);
                exit(1);
            }
            int ret;
            while ((ret = read(fd1, buffer, BUFFER_SIZE - 1)) != 0) {
                buffer[ret] = '\0';
                dprintf(file_fd, "%s", buffer);
                fprintf(stdout, "%s", buffer);
            }

            printf("\n\nEND END END END END END END END END END END\n\n");

            insert_node(head, file_fd, query_copy);
            close(fd1);
        }
    }
}


int main(int argc, char *argv[]) {

    int len;
    struct sockaddr_in server_address, client;

    // socket create and verification
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("socket creation failed...\n");
        exit(1);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&server_address, sizeof(server_address));

    // assign IP, PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9000);

    // Binding
    if ((bind(fd, (struct sockaddr *) &server_address, sizeof(server_address))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    //Listening
    if ((listen(fd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(1);
    } else {
        printf("Server listening..\n");
    }
    len = sizeof(client);

    // Accepting
    int connfd = accept(fd, (struct sockaddr *) &client, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(1);
    } else {
        printf("server accept the client...\n");
    }

    func(connfd);

    close(fd);
}