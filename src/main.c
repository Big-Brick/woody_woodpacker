
#include "elf.h"

#include <sys/errno.h> // errno
#include <string.h>    // strerror()
#include <stdio.h>     // *printf()
#include <stdlib.h>    // exit()
#include <fcntl.h>     // open()
#include <unistd.h>    // close(), lseek()
#include <sys/mman.h>  // mmap()

#define debug(fmt, ...) {\
  do {\
    fprintf(stderr, "[DEBUG] (%s():%d) " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);\
  } while(0);\
}

static void error(char *err, char *err_str) {

    fprintf(stderr, "woody: %s: %s", err, err_str);
    exit(EXIT_FAILURE);
}

static void usage(int exit_code) {

    FILE *out = (exit_code == 0) ? stdout : stderr;
    fprintf(out, "Usage: woody FILE\n");
    exit(exit_code);
}

static void init(char *name, size_t *size, void **ptr) {

    int    fd;

    if ((fd = open(name, O_RDONLY)) == -1)
        error(name, strerror(errno));
    debug("fd   : %d", fd);

    if ((*size = lseek(fd, 0, SEEK_END)) == -1)
        error("lseek()", strerror(errno));
    debug("size : %zu", *size);

    if ((*ptr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        error("mmap()", strerror(errno));
    debug("addr : %p", *ptr);

    close(fd);
}

static void check_file_type(char *name, unsigned char *ptr) {

    debug("magic   : \"%.*s\"", SELFMAG, ptr);
    if (ptr[EI_MAG0] != ELFMAG0 || ptr[EI_MAG1] != ELFMAG1 ||
        ptr[EI_MAG2] != ELFMAG2 || ptr[EI_MAG3] != ELFMAG3)
        error(name, "wrong file type, only ELF files are allowed");

    debug("class   : %d", ptr[EI_CLASS]);
    if (ptr[EI_CLASS] != ELFCLASS64)
        error(name, "wrong file type, only 64-bit ELF files are allowed");

    debug("data    : %d", ptr[EI_DATA]);
    if (ptr[EI_DATA] != ELFDATA2LSB)
        error(name, "wrong file type, only little endian encoded ELF files are allowed");

    debug("version : %d", ptr[EI_VERSION]);
    if (ptr[EI_VERSION] != EV_CURRENT)
        error(name, "wrong ELF file version");

    debug("type    : %d", ((Elf64_Ehdr *)ptr)->e_type);
    if (((Elf64_Ehdr *)ptr)->e_type != ET_EXEC)
        error(name, "wrong file type, only executable ELF files are allowed");

    debug("arch    : %d", ((Elf64_Ehdr *)ptr)->e_machine);
    if (((Elf64_Ehdr *)ptr)->e_machine != EM_X86_64)
        error(name, "wrong file type, only ELF files for AMD x86-64 are allowed");
}

int main(int ac, char *av[]) {

    Elf64_Ehdr *header;
    size_t     size;
    void       *ptr;

    sleep(1);

    if (ac != 2)
        usage(EXIT_FAILURE);

    init(av[1], &size, &ptr);
    check_file_type(av[1], ptr);

    header = ptr;
}
