#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int mysystem(const char *cmd) {
    char* copy1 = strdup(cmd);

    /* предподсчет */
    int c1 = 0;
    int c2 = 0;
    int arr_index = 0;
    int isstr = 0;
    char last_character;
    int counter = 0;
    while (copy1[c1] != '\0') {
        last_character = copy1[c1];
        if (isspace(copy1[c1])) {
            if (isstr) {
                ++counter;
                isstr = 0;
            }
        } else {
            isstr = 1;
        }
        ++c1;
    }
    if (!isspace(last_character)) {
        ++counter;
        copy1[c1] = ' ';
    }

    if (counter < 2) {
        return -1;
    }

    char* arr[counter];
    // добавляем в конец пробел

    // "parsing"
    int null_counter = 0;
    isstr = 0;
    char* copy1_copy = strdup(copy1);
    while (copy1_copy[c2] != '\0') {
        if (isspace(copy1_copy[c2])) {
            if (isstr) {
                copy1[c2 - null_counter] = '\0';
                arr[arr_index++] = copy1;
                copy1 += c2 - null_counter + 1;
                null_counter = 0;
                isstr = 0;
            } else {
                ++copy1;
                ++null_counter;
            }
        } else {
            isstr = 1;
        }
        ++c2;
    }
    char* last_string = arr[counter - 1];
    int x = 0;
    while (last_string[x] != '\0') {
        if (isspace(last_string[x])) {
            last_string[x] = '\0';
        }
        ++x;
    }
    arr[counter - 1] = last_string;
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        if (execvp(arr[0], arr) < 0) {
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return 1024 + WTERMSIG(status);
        } else {
            return WEXITSTATUS(status);
        }
    }
    return 0;
}