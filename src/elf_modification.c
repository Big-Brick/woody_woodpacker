
#include "woody.h"
#include <stdio.h>
#include <stdlib.h> // malloc(), free()
#include <fcntl.h>  // open()
#include <unistd.h> // close(), lseek()
#include <assert.h>

const char  *key = "1234567890abcdef";

void loader(void);
extern uint32_t _loader;     // loader size
extern uint32_t sloader;     // loader size
static uint32_t aloader;     // loader align
static uint32_t oloader;     // loader offset
static uint32_t dloader = 4; // loader data
static uint32_t new_ep;      // new entry point

/*

 sample object file with three sections:
             +-------------------+
             | ELF Header        |---+
 +---------> +-------------------+   | e_shoff
 |           |                   |<--+
 | Section   | Section header 0  |
 |           |                   |---+ sh_offset
 | Header    +-------------------+   |
 |           | Section header 1  |---|--+ sh_offset
 | Table     +-------------------+   |  |
 |           | Section header 2  |---|--|--+
 +---------> +-------------------+   |  |  |
             | Section 0         |<--+  |  |
             +-------------------+      |  | sh_offset
             | Section 1         |<-----+  |
             +-------------------+         |
             | Section 2         |<--------+
             +-------------------+

 But nothing (except sanity) prevents the following topology:
             +-------------------+
             | ELF Header        |---+ e_shoff
             +-------------------+   |
             | Section 1         |<--|--+
 +---------> +-------------------+   |  |
 |           |                   |<--+  | sh_offset
 | Section   | Section header 0  |      |
 |           |                   |------|---------+
 | Header    +-------------------+      |         |
 |           | Section header 1  |------+         |
 | Table     +-------------------+                |
 |           | Section header 2  |---+            | sh_offset
 +---------> +-------------------+   | sh_offset  |
             | Section 2         |<--+            |
             +-------------------+                |
             | Section 0         |<---------------+
             +-------------------+

 */

//static void expand_load_segment(void *ptr, Elf64_Shdr *sh_text, size_t diff) {
//
//    Elf64_Phdr *pheader = ptr + ((Elf64_Ehdr *)ptr)->e_phoff;
//
//    for (size_t i = 0; i < ((Elf64_Ehdr *)ptr)->e_phnum; i++) {
//        Elf64_Addr start = pheader[i].p_vaddr;
//        Elf64_Addr end   = pheader[i].p_vaddr + pheader[i].p_memsz;
//
//        if (pheader[i].p_type == PT_LOAD &&
//            sh_text->sh_addr >= pheader[i].p_vaddr &&
//            sh_text->sh_addr < pheader[i].p_vaddr + pheader[i].p_memsz) {
//            pheader[i].p_memsz += diff;
//            return ;
//        }
//    }
//    // error ???
//}

static Elf64_Shdr* get_section_header(void *ptr, const char *sect) {

    Elf64_Ehdr *header  = ptr;
    Elf64_Shdr *sheader = ptr + header->e_shoff;
    void       *strtab  = ptr + sheader[header->e_shstrndx].sh_offset;
    char       *secname;

    for (size_t i = 0; i < header->e_shnum; i++) {
        secname = strtab + sheader[i].sh_name;
        if (!ft_strcmp(secname, sect))
            return (&(sheader[i]));
    }

    return (NULL);
}

static void encrypt_text_section(void *ptr, size_t size) {

    void   *text; /* .text      */
    size_t stext; /* .text size */
    Elf64_Shdr *sheader = get_section_header(ptr, ".text");

    if (sheader == NULL)
        error("can't find .text section", NULL);

    text = ptr + sheader->sh_offset;
    stext = sheader->sh_size;

    /* XXTEA works with blocks of 32 bits */
//    xxtea_encrypt(text, stext / 4, (uint32_t *)key);
//    xxtea_decrypt(text, stext / 4, (uint32_t *)key);
}

/* returns loader offset in file */
void modify_segment(void *ptr) {

    Elf64_Ehdr *header  = ptr;
    Elf64_Phdr *pheader = ptr + header->e_phoff;
    Elf64_Shdr *sheader = ptr + header->e_shoff;
    Elf64_Addr  p_vaddr = 0;
    size_t load = 0;

//    /* find executable load segment */
    for (size_t i = 0; i < header->e_phnum; i++) {
        if (pheader[i].p_type == PT_LOAD && pheader[i].p_vaddr > p_vaddr) {
            p_vaddr = pheader[i].p_vaddr;
            load = i;
        }
    }
    assert(load != 0);

    pheader[load].p_flags |= PF_X;
    aloader = pheader[load].p_memsz  - pheader[load].p_filesz;
    oloader = pheader[load].p_offset + pheader[load].p_filesz;

//    if (header->e_phoff > _oloader)
//        header->e_phoff += _aloader + _sloader;
//
//    /* edit segments after the loader */
//    for (size_t i = 0; i < header->e_phnum; i++) {
//        if (pheader[i].p_offset > _oloader) {
//            pheader[i].p_offset += _aloader + _sloader;
//        }
//    }

    if (header->e_shoff > oloader)
        header->e_shoff += aloader + sloader;

    /* edit sections after the loader */
    for (size_t i = 0; i < header->e_shnum; i++) {
        if (sheader[i].sh_offset > oloader) {
            sheader[i].sh_offset += aloader + sloader;
            if (sheader[i].sh_addr)
                sheader[i].sh_addr += aloader + sloader;
        }
    }
    uint32_t e_entry = ((Elf64_Ehdr *)ptr)->e_entry;
    header->e_entry = pheader[load].p_vaddr + pheader[load].p_filesz + aloader + _loader;
    pheader[load].p_memsz  += sloader;
    pheader[load].p_filesz += aloader + sloader;
    new_ep = pheader[load].p_vaddr + pheader[load].p_memsz - e_entry;
    debug("new_ep        : %p",  (void *)new_ep);
}

#include <string.h>
#include <errno.h>
void modify_elf(void *ptr, size_t size) {

    int fd;
    uint32_t e_entry = ((Elf64_Ehdr *)ptr)->e_entry;

    encrypt_text_section(ptr, size);
    modify_segment(ptr);

    if ((fd = open(EXEC_NAME, O_RDWR | O_CREAT, 0755)) == -1)
        error(EXEC_NAME, strerror(errno));

    debug("loader        : %p",  loader);
    debug("loader size   : %d",  sloader);
    debug("loader offset : %ld", (long)oloader);
    debug("loader align  : %ld", (long)aloader);
    debug("rest          : %lu", (unsigned long)(size - oloader));
    debug("e_entry       : %p",  (void *)e_entry);

    write(fd, ptr, oloader);
    for (size_t i = 0; i < aloader; i++)
        write(fd, "\0", 1);
    write(fd, &loader, sloader - 4);
    write(fd, &e_entry, 4);
//    write(fd, size, 4);
    write(fd, ptr + oloader, size - oloader);

    close(fd);
}
