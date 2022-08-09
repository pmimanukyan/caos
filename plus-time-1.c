#include <stdio.h>
#include <time.h>

enum {
    MAXLEN = 80,
    SECONDS_IN_DAY = 86400
};

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    int res;
    int number_of_days;
    while ((res = scanf("%d", &number_of_days)) == 1) {
        time_t seconds_after;
        if(__builtin_mul_overflow(number_of_days, SECONDS_IN_DAY, &seconds_after)) {
            printf("OVERFLOW\n");
            continue;
        }
        time_t time_to_find;
        if (__builtin_add_overflow(t, seconds_after, &time_to_find)) {
            printf("OVERFLOW\n");
            continue;
        }
        char buffer[MAXLEN];
        struct tm *timeinfo;
        timeinfo = localtime(&time_to_find);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
        printf("%s\n", buffer);
    }
    if (res != EOF) {
        return 1;
    }
}