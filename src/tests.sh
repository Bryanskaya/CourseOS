#!/bin/sh

SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_WARNING="echo \\033[1;33m"
SETCOLOR_NORMAL="echo \\033[0;39m"


clear
echo ---------------------TEST COMMANDS---------------------
make
./fw_comm.o --add --del                # Forbidden to mention add and delete action at the same time
./fw_comm.o --in --out                 # Forbidden to mention in and out direction at the same time
echo -------------------------------------------------------
./fw_comm.o --add --in --protocol TCP   # OK
./fw_comm.o --add --out --protocol UDP  # OK
./fw_comm.o --add --in --protocol QWE          # Wrong type of protocol
echo -------------------------------------------------------
./fw_comm.o --help          # OK
./fw_comm.o -h              # OK

${SETCOLOR_WARNING}
echo -------------------------------------------------------
${SETCOLOR_NORMAL}
./fw_comm.o --add --out --src_ip 176.59.56.121 # OK
./fw_comm.o --add --out --dest_ip 1000.56.56.121 # ERROR