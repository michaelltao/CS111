# Pipe Up

This program implements the pipe shell operator which redirects a files output to another's input.

## Building

Use "make" command to create the ./pipe executable.

## Running
To run the program, run the command [./pipe prog1 prog2 ... ] with at least one argument. 

Example input and output:
./pipe ls cat wc
    5   5   38

## Cleaning up

Command "make clean" removes .o files and executable
