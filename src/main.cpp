#include "main.hpp"
#include <notcurses/notcurses.h>

#include <iostream>

using namespace std;

int main() {
    struct notcurses_options opts = {
        .flags = NCOPTION_INHIBIT_SETLOCALE,
    };

    // Starting notcurses
    struct notcurses* nc = notcurses_init(&opts, NULL);
    struct ncplane* stdplane = notcurses_stdplane(nc);

    // Putting some text
    ncplane_putstr(stdplane, "Welcome to TextDE!");

    // Render the changes
    notcurses_render(nc);

    sleep(5);

    // Closing notcurses
    notcurses_stop(nc);
    return 0;
}
