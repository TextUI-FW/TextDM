#include "main.hpp"

#include <iostream>
#include <cstdio>
#include <string>

#include <notcurses/notcurses.h>

using namespace std;

int main() {
    // Set locale options
    struct notcurses_options opts = {
        .flags = NCOPTION_INHIBIT_SETLOCALE,
    };

    // Starting notcurses
    struct notcurses* nc = notcurses_init(&opts, NULL);
    struct ncplane* stdplane = notcurses_stdplane(nc);

    renderWelcomeMsg(nc, stdplane);

    sleep(5);

    // Closing notcurses
    notcurses_stop(nc);
    return 0;
}

void getDistroName(struct ncplane* stdplane) {
    string command = "cat /etc/os-release | grep NAME | head -n1 | cut -d '=' -d '\"' -f2"; // Command to find the distro name

    FILE* pipe = popen(command.c_str(), "r"); // Using popen

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        ncplane_printf(stdplane, " %s!", buffer);
    } // Reading the popen buffer to ncplane_putstr

    pclose(pipe); // Closing popen
}

void renderWelcomeMsg(struct notcurses* nc, struct ncplane* stdplane) {
    // Putting some text
    ncplane_set_styles(stdplane, NCSTYLE_BOLD); // Italic
    ncplane_putstr(stdplane, "Welcome to"); //Welcome message
    getDistroName(stdplane);

    // Render the changes
    notcurses_render(nc);
}
