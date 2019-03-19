
#include <stdio.h>  // *printf()
#include <stdlib.h> // exit()

void error(char *err, char *err_str) {

    fprintf(stderr, "woody: %s: %s", err, err_str);
    exit(EXIT_FAILURE);
}
