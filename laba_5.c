#include <stdio.h>
#include <string.h>

void Help(void)
{
    printf
        ("================================================================================\n"
         "MANUAL:\n"
         "===============================================================================\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!(strcmp(argv[1], "-h")))
            Help();
    }
    return 0;
}
