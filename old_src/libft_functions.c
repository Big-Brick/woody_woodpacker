
#include <stddef.h>

void *ft_memset(void *b, int c, size_t len) {

    unsigned char *str = (unsigned char *)b;

    while (len--)
        *str++ = (unsigned char)c;

    return (b);
}

int ft_memcmp(const void *s1, const void *s2, size_t n) {

    unsigned char chr1;
    unsigned char chr2;

    while (n--) {
        chr1 = *(unsigned char *)s1;
        chr2 = *(unsigned char *)s2;
        if (chr1 != chr2)
            return (chr1 - chr2);
        s1++;
        s2++;
    }

    return (0);
}

void *ft_memmove(void *dst, const void *src, size_t len) {

    unsigned char *s1 = (unsigned char *)dst;
    unsigned char *s2 = (unsigned char *)src;

    if (dst < src) {
        while (len--)
            *s1++ = *s2++;
    }
    else {
        s1 += len;
        s2 += len;
        while (len--)
            *--s1 = *--s2;
    }

    return (dst);
}

//size_t ft_strlen(const char *s) {
//
//    size_t len = 0;
//
//    while (*s) {
//        len++;
//        s++;
//    }
//
//    return (len);
//}

int ft_strcmp(const char *s1, const char *s2) {

    unsigned char *str1 = (unsigned char *)s1;
    unsigned char *str2 = (unsigned char *)s2;

    while (*str1 == *str2) {
        if (*str1 == '\0')
            return (0);

        str1++;
        str2++;
    }

    return (*str1 - *str2);
}
