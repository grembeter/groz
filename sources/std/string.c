/**
 * @file string.c
 */

#include <groz.h>

size_t std_strlen(const char *str, size_t maxlen)
{
    size_t len;
    for (len = 0; (len < maxlen) && (str[len] != '\0'); ++len) {
        ;
    }
    return len;
}

int std_strcmp(const char *str1, const char *str2, size_t maxlen)
{
    size_t len = 0;

    while (len < maxlen) {
        if (str1[len] > str2[len]) {
            return -1;
        } else if (str1[len] < str2[len]) {
            return 1;
        }

        if (str1[len] == '\0') {
            return 0;
        }

        ++len;
    }

    return 0;
}
