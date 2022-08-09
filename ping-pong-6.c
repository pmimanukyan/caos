#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void ping_pong(FILE *reader, FILE *writer, int n, int player_id) {
    int i;
    while (1) {
        if(fscanf(reader, "%d", &i) <= 0 || i == n) {
            fclose(reader);
            fclose(writer);
            return;
        }
        printf("%d %d\n", player_id, i);
        fflush(stdout);
        fprintf(writer, "%d\n", i + 1);
        fflush(writer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = atoi(argv[1]);
    int fd1[2];
    int fd2[2];
    if (pipe(fd1) < 0) {
        return 1;
    }
    if (pipe(fd2) < 0) {
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("pid1");
    } else if (pid1 == 0) {
        close(fd1[0]);
        close(fd2[1]);
        FILE *reader = fdopen(fd2[0], "r");
        FILE *writer = fdopen(fd1[1], "w");
        ping_pong(reader, writer, n, 1);
        return 0;
    } else {
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("pid2");
            return 1;
        } else if (pid2 == 0) {
            close(fd1[1]);
            close(fd2[0]);
            FILE *reader = fdopen(fd1[0], "r");
            FILE *writer = fdopen(fd2[1], "w");
            ping_pong(reader, writer, n, 2);
            return 0;
        }

        FILE *fd2w = fdopen(fd2[1], "w");
        fprintf(fd2w, "%d\n", 1);
        fclose(fd2w);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);

        int status1, status2;
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
        printf("Done\n");
    }
}

// 1 1
// 2 2
// 1 3
// 2 4
// Done