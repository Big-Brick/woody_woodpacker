
#include "elf.h"
#include <stdio.h>

void print_elf_headers(void *ptr) {

    /* ELF Header */
    Elf64_Ehdr *header = ptr;
    fprintf(stderr, "[%p] ELF Header START:\n", (void *)header);
    fprintf(stderr, "    e_ident     : %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", \
            header->e_ident[EI_MAG0],
            header->e_ident[EI_MAG1],
            header->e_ident[EI_MAG2],
            header->e_ident[EI_MAG3],
            header->e_ident[EI_CLASS],
            header->e_ident[EI_DATA],
            header->e_ident[EI_VERSION],
            header->e_ident[EI_OSABI],
            header->e_ident[EI_ABIVERSION]);
    fprintf(stderr, "    e_type      : %10d     (Object file type)\n", header->e_type);
    fprintf(stderr, "    e_machine   : %10d     (Architecture)\n", header->e_machine);
    fprintf(stderr, "    e_version   : %10d     (Object file version)\n", header->e_version);
    fprintf(stderr, "    e_entry     : %10p     (Entry point virtual address)\n", (void *)header->e_entry);
    fprintf(stderr, "    e_phoff     : %10lu     (Program header table file offset)\n", (unsigned long)header->e_phoff);
    fprintf(stderr, "    e_shoff     : %10lu     (Section header table file offset)\n", (unsigned long)header->e_shoff);
    fprintf(stderr, "    e_flags     : %10u     (Processor-specific flags)\n", header->e_flags);
    fprintf(stderr, "    e_ehsize    : %10hu     (ELF header size in bytes)\n", header->e_ehsize);
    fprintf(stderr, "    e_phentsize : %10hu     (Program header table entry size)\n", header->e_phentsize);
    fprintf(stderr, "    e_phnum     : %10hu     (Program header table entry count)\n", header->e_phnum);
    fprintf(stderr, "    e_shentsize : %10hu     (Section header table entry size)\n", header->e_shentsize);
    fprintf(stderr, "    e_shnum     : %10hu     (Section header table entry count)\n", header->e_shnum);
    fprintf(stderr, "    e_shstrndx  : %10hu     (Section header string table index)\n", header->e_shstrndx);

    fprintf(stderr, "[%p] ELF Header END:\n", (void *)header + sizeof(*header));
    fprintf(stderr, "\n");

    /* ELF Program Header */
    Elf64_Phdr *pheader = (void *)header + header->e_phoff;
    for (size_t i = 0; i < header->e_phnum; i++) {
        fprintf(stderr, "[%p] ELF Program header(%zu) START:\n", &pheader[i], i);

        fprintf(stderr, "    p_type       : %10d    (Segment type)\n",                           pheader[i].p_type);
        fprintf(stderr, "    p_flags      : %10d    (Segment flags)\n",                          pheader[i].p_flags);
        fprintf(stderr, "    p_offset     : %10lu    (Segment file offset)\n",    (unsigned long)pheader[i].p_offset);
        fprintf(stderr, "    p_vaddr      : %10p    (Segment virtual address)\n",        (void *)pheader[i].p_vaddr);
        fprintf(stderr, "    p_paddr      : %10p    (Segment physical address)\n",       (void *)pheader[i].p_paddr);
        fprintf(stderr, "    p_filesz     : %10lu    (Segment size in file)\n",   (unsigned long)pheader[i].p_filesz);
        fprintf(stderr, "    p_memsz      : %10lu    (Segment size in memory)\n", (unsigned long)pheader[i].p_memsz);
        fprintf(stderr, "    p_align      : %10lu    (Segment alignment)\n",      (unsigned long)pheader[i].p_align);

        fprintf(stderr, "[%p] ELF Program header(%zu) END:\n", &pheader[i] + sizeof(*pheader), i);
        fprintf(stderr, "\n");
    }

    /* ELF Section Header */
    Elf64_Shdr *sheader = (void *)header + header->e_shoff;
    for (size_t i = 0; i < header->e_shnum; i++) {
        fprintf(stderr, "[%p] ELF Section header(%zu) START:\n", &sheader[i], i);

        fprintf(stderr, "    sh_name      : %10d    (Section name (string tbl index))\n",           sheader[i].sh_name);
        fprintf(stderr, "    sh_type      : %10d    (Section type)\n",                              sheader[i].sh_type);
        fprintf(stderr, "    sh_flags     : %10lu    (Section flags)\n",             (unsigned long)sheader[i].sh_flags);
        fprintf(stderr, "    sh_addr      : %10p    (Section virtual addr at execution)\n", (void *)sheader[i].sh_addr);
        fprintf(stderr, "    sh_offset    : %10lu    (Section file offset)\n",       (unsigned long)sheader[i].sh_offset);
        fprintf(stderr, "    sh_size      : %10lu    (Section size in bytes)\n",     (unsigned long)sheader[i].sh_size);
        fprintf(stderr, "    sh_link      : %10d    (Link to another section)\n",                   sheader[i].sh_link);
        fprintf(stderr, "    sh_info      : %10d    (Additional section information)\n",            sheader[i].sh_info);
        fprintf(stderr, "    sh_addralign : %10lu    (Section alignment)\n",         (unsigned long)sheader[i].sh_addralign);
        fprintf(stderr, "    sh_entsize   : %10lu    (Entry size if section holds table)\n", (unsigned long)sheader[i].sh_entsize);

        fprintf(stderr, "[%p] ELF Section header(%zu) END:\n", &sheader[i] + sizeof(*sheader), i);
        fprintf(stderr, "\n");
    }

}
