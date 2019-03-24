
#include <stdio.h>  // *printf()
#include <stdlib.h> // exit()

void error(char *err, char *err_str) {

    if (err && err_str)
        fprintf(stderr, "woody: %s: %s", err, err_str);
    else if (err)
        fprintf(stderr, "woody: %s", err);

    exit(EXIT_FAILURE);
}
