
#ifndef WOODY_H
#define WOODY_H

#include "elf.h"

#include <stddef.h> // size_t

#define EXEC_NAME "woody"

#define debug(fmt, ...) {\
    do {\
        fprintf(stderr, "[DEBUG] (%s():%d) " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);\
    } while(0);\
}

void    modify_elf(void *ptr, size_t size);

void    xxtea_encrypt(uint32_t *data, size_t len, const uint32_t *key);
void    xxtea_decrypt(uint32_t *data, size_t len, const uint32_t *key);

void   *ft_memset(void *b, int c, size_t len);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
void   *ft_memmove(void *dst, const void *src, size_t len);
size_t  ft_strlen(const char *s);
int     ft_strcmp(const char *s1, const char *s2);

void    error(char *err, char *err_str);

void    print_elf_headers(void *ptr);

#endif
