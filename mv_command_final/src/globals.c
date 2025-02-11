#include "../include/globals.h"
#include <getopt.h>

int option_force = 0;
int option_interactive = 0;
int option_no_clobber = 0;
int option_verbose = 0;
int option_help = 0;
int option_backup = 0;

struct option long_options[] = {
    {"force", no_argument, NULL, 'f'},
    {"interactive", no_argument, NULL, 'i'},
    {"no-clobber", no_argument, NULL, 'n'},
    {"verbose", no_argument, NULL, 'v'},
    {"backup", no_argument, NULL, 'b'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

