
#include "woody.h"
#include <stdio.h>
#include <stdlib.h> // malloc(), free()
#include <fcntl.h>     // open()
#include <unistd.h>    // close(), lseek()

const char   *key    = "1234567890abcdef";
const char   *loader = "loadloadloadloadloadloadloadloadloadloadloadloadloadloadloadload";
const size_t sloader = 64;

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
    xxtea_encrypt(text, stext / 4, (uint32_t *)key);
//    xxtea_decrypt(text, stext / 4, (uint32_t *)key);
}

void modify_elf(void *ptr, size_t size) {

    encrypt_text_section(ptr, size);
    // .loader
    // modify entrypoint
}
