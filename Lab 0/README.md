# A Kernel Seedling

Count then number of running (alive) processes in the system.

## Building

1. make clean to ensure a new build
2. make to build the neccessary files -- namely proc_count.ko
3. sudo insmod proc_count.ko to install the module into the kernel

## Running

Run the command cat /proc/count to view the current number of running processes

## Cleaning Up

sudo rmmod proc_count for module removal from kernel

## Testing

Tested module on kernel release version 5.14.8-arch1-1 with provided python test file test_lab0.py.
