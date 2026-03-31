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

    // Init the screen blocks
    renderWelcomeMsg(nc, stdplane);

    // Render the login screen
    notcurses_render(nc);

    sleep(5);

    // Closing notcurses
    notcurses_stop(nc);
    return 0;
}

/*
*    This function gets the distro name using a BASH
*    command and prints with a welcome message.
*
*    /param plane -> The plane to use
*/
void getDistroName(struct ncplane* plane) {
    string command = "cat /etc/os-release | grep NAME | head -n1 | cut -d '=' -d '\"' -f2"; // Command to find the distro name

    FILE* pipe = popen(command.c_str(), "r"); // Using popen to execute the command in the console

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        ncplane_printf_aligned(plane, 1, NCALIGN_CENTER,"Welcome to %s!", buffer);
    } // Reading the popen buffer to ncplane_printf()

    pclose(pipe); // Closing popen/console instance
}

/*
 *    This function renders the welcome message:
 *    "Welcome to (your_distro_name)!".
 *
 *    /param nc -> The notcurses instance
 */
void renderWelcomeMsg(struct notcurses* nc, struct ncplane* plane) {
    ncplane_set_styles(plane, NCSTYLE_BOLD); // Setting the font style to bold
    getDistroName(plane); // Welcome message
}
