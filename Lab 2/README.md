# You Spin Me Round Robin

C implementation of a round robin scheduler.

## Building

Use "make" command to create the ./rr executable.

## Running

After building the executable, run the command "./rr processes.txt quantum" 
where quantum is the desired quantum length.

An example input and output:
  ./rr processes.txt 5
    Average waiting time: 5.50
    Average response time: 3.25

## Cleaning up

Run the command "make clean" to remove all .o files and the executable
