#!/bin/bash

# What you will need for build the Text Desktop Manager:

# You need to install notcurses from your package manager or
# build this from here: https://github.com/dankamongmen/notcurses

g++ ./src/main.cpp -o TextDM -lnotcurses -lnotcurses-core
