
#include "woody.h"

#include <sys/errno.h> // errno
#include <string.h>    // strerror()
#include <stdio.h>     // *printf()
#include <stdlib.h>    // exit()
#include <fcntl.h>     // open()
#include <unistd.h>    // close(), lseek()
#include <sys/mman.h>  // mmap()

static void usage(int exit_code) {

    FILE *out = (exit_code == 0) ? stdout : stderr;
    fprintf(out, "Usage: woody FILE\n");
    exit(exit_code);
}

static void init(char *name, size_t *size, void **ptr) {

    int fd;

    if ((fd = open(name, O_RDONLY)) == -1)
        error(name, strerror(errno));

    if ((*size = lseek(fd, 0, SEEK_END)) == -1)
        error("lseek()", strerror(errno));

    if ((*ptr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        error("mmap()", strerror(errno));

    close(fd);
}

static void check_file_type(char *name, unsigned char *ptr) {

    if (ptr[EI_MAG0] != ELFMAG0 || ptr[EI_MAG1] != ELFMAG1 ||
        ptr[EI_MAG2] != ELFMAG2 || ptr[EI_MAG3] != ELFMAG3)
        error(name, "wrong file type, only ELF files are allowed");

    if (ptr[EI_CLASS] != ELFCLASS64)
        error(name, "wrong file type, only 64-bit ELF files are allowed");

    if (ptr[EI_DATA] != ELFDATA2LSB)
        error(name, "wrong file type, only little endian encoded ELF files are allowed");

    if (ptr[EI_VERSION] != EV_CURRENT)
        error(name, "wrong ELF file version");

    if (((Elf64_Ehdr *)ptr)->e_type != ET_EXEC)
        error(name, "wrong file type, only executable ELF files are allowed");

    if (((Elf64_Ehdr *)ptr)->e_machine != EM_X86_64)
        error(name, "wrong file type, only ELF files for AMD x86-64 are allowed");
}

int main(int ac, char *av[]) {

    int        fd;
    void       *elf;
    size_t     self;

    sleep(1);

    if (ac != 2)
        usage(EXIT_FAILURE);

    init(av[1], &self, &elf);
    check_file_type(av[1], elf);

    modify_elf(elf, self);

    if ((fd = open(EXEC_NAME, O_RDWR | O_CREAT, 0755)) == -1)
        error(EXEC_NAME, strerror(errno));
    write(fd, elf, self);

    return (EXIT_SUCCESS);
}
