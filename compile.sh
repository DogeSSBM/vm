#!/bin/sh
clear
set -ex
output="main.out"
flags="-std=c11 -Wall -Wextra -Wpedantic -Werror -g"
# flags="-std=c11 -Wall -Wextra -Wpedantic -Werror -Ofast"
gcc main.c $flags -lm -o $output
