#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void find_substr(const char *v, char *cur_substring, int* cur_substring_iter, int *l, int *r, int *count_number, int *cur_substring_size, int* flag_v_ptr) {
    int found_digit = 0;
    while (*r != strlen(v)) {
        if (found_digit) {
            if (isdigit(v[*r])) {
                cur_substring[*cur_substring_iter] = v[*r];
                ++(*r);
                ++(*cur_substring_iter);
                continue;
            } else {
                ++(*count_number);
                *cur_substring_size = *r - *l;
                break;
            }
        }
        if (isdigit(v[*r])) {
            if (v[*r] == '0') {
                *flag_v_ptr = 1;
            }
            //char a = v[*r];
            cur_substring[*cur_substring_iter] = v[*r];
            ++(*cur_substring_iter);
            *l = *r;
            found_digit = 1;
        }
        ++(*r);
    }
    if (found_digit) {
        ++(*count_number);
        *cur_substring_size = *r - *l;
    }
}

int correct_arr(char* arr) {
    int i = 0;
    int k = 0;
    while (arr[i] == '0') {
        ++arr;
        ++k;
    }
    return k;
}
int vercmp(const char* v1, const char* v2) {
    int flag_v1 = 0;
    int *flag_v1_ptr = &flag_v1;

    int flag_v2 = 0;
    int *flag_v2_ptr = &flag_v2;
    int l1 = 0;
    int *l1_ptr = &l1;
    int r1 = 0;
    int *r1_ptr = &r1;

    int l2 = 0;
    int *l2_ptr = &l2;
    int r2 = 0;
    int *r2_ptr = &r2;

    int cur_substring_v1_iter = 0;
    int *cur_substring_v1_iter_ptr = &cur_substring_v1_iter;
    int cur_substring_v2_iter = 0;
    int *cur_substring_v2_iter_ptr = &cur_substring_v2_iter;

    int count_number1 = 0;
    int *count_number1_ptr = &count_number1;
    int count_number2 = 0;
    int *count_number2_ptr = &count_number2;

    int cur_substring_v1_size = 0;
    int *cur_substring_v1_size_ptr = &cur_substring_v1_size;
    int cur_substring_v2_size = 0;
    int *cur_substring_v2_size_ptr = &cur_substring_v2_size;

    char cur_substring_v1[10000] = {0};
    char cur_substring_v2[10000] = {0};

    int result;
    while(*r1_ptr != strlen(v1) || *r2_ptr != strlen(v2)) {
        find_substr(v1, cur_substring_v1, cur_substring_v1_iter_ptr, l1_ptr, r1_ptr, count_number1_ptr, cur_substring_v1_size_ptr, flag_v1_ptr);
        find_substr(v2, cur_substring_v2, cur_substring_v2_iter_ptr, l2_ptr, r2_ptr, count_number2_ptr, cur_substring_v2_size_ptr, flag_v2_ptr);

        int k1 = correct_arr(cur_substring_v1);
        int x = 0;
        for (int i = k1; i < strlen(cur_substring_v1); ++i) {
            cur_substring_v1[i - k1] = cur_substring_v1[i];
            ++x;
        }
        for (; x < strlen(cur_substring_v1); ++x) {
            cur_substring_v1[x] = 0;
        }


        int k2 = correct_arr(cur_substring_v2);
        x = 0;
        for (int i = k2; i < strlen(cur_substring_v2); ++i) {
            cur_substring_v2[i - k2] = cur_substring_v2[i];
            ++x;
        }
        for (; x < strlen(cur_substring_v2); ++x) {
            cur_substring_v2[x] = 0;
        }
        if (flag_v1) {
            cur_substring_v1[0] = '0';
        }
        if (flag_v2) {
            cur_substring_v2[0] = '0';
        }
        flag_v1 = 0;
        flag_v2 = 0;
        result = strcmp(cur_substring_v1, cur_substring_v2);
        if(result != 0) {
            if(result > 0) {
                return 1;
            } else {
                return -1;
            }
        }
        for (int i = 0; i < strlen(cur_substring_v1); ++i) {
            cur_substring_v1[i] = '0';
            cur_substring_v2[i] = '0';
        }
    }
    return 0;

}
//int main() {
//    printf("%d", vercmp("beta1", "beta1.0"));
//}