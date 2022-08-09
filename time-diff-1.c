#define _XOPEN_SOURCE

#include <stdio.h>
#include <time.h>

enum { MAXLEN = 100 };

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    FILE *fptr = fopen(argv[1],"r");
    time_t last_seconds;
    int k = 0;
    char date_and_time[MAXLEN];
    while(fgets(date_and_time, MAXLEN, fptr)) {
        struct tm tm;
        strptime(date_and_time, "%Y/%m/%d %H:%M:%S", &tm);
        tm.tm_isdst = -1; // летнее-зимнее
        time_t seconds = mktime(&tm);
        if (!k) {
            k = 1;
        } else {
            printf("%ld\n", seconds - last_seconds);
        }
        last_seconds = seconds;
    }
}


// Input in input.txt
// 2011/09/01 08:45:00
// 2011/09/01 10:20:00
// 2011/09/01 10:30:00
// 2011/12/01 23:32:00
// 2011/11/30 23:32:00

// Output
// 5700
// 600
// 7909320
// -86400