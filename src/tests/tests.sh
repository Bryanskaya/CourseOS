#!/bin/sh

SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_WARNING="echo \\033[1;33m"
SETCOLOR_NORMAL="\\033[0;39m"


clear
echo ---------------------TEST COMMANDS---------------------
echo

${SETCOLOR_WARNING}../fw.o ${SETCOLOR_NORMAL}
../fw.o    
echo            # No commands

${SETCOLOR_WARNING}../fw.o --add --delete ${SETCOLOR_NORMAL}
../fw.o --add --delete    
echo            # No rule for delete

${SETCOLOR_WARNING}../fw.o --in --out ${SETCOLOR_NORMAL}
../fw.o --in --out                 # Forbidden to mention in and out direction at the same time
echo

${SETCOLOR_WARNING}../fw.o --add ${SETCOLOR_NORMAL}
../fw.o --add   # No rule
echo

${SETCOLOR_WARNING}../fw.o --add --in TCP ${SETCOLOR_NORMAL}
../fw.o --add --in TCP   # No keys
echo

${SETCOLOR_WARNING}../fw.o --in --protocol TCP ${SETCOLOR_NORMAL}
../fw.o --in --protocol TCP   # No action
echo

${SETCOLOR_WARNING}../fw.o --add --protocol UDP ${SETCOLOR_NORMAL}
../fw.o --add --protocol UDP  # No direction
echo

${SETCOLOR_WARNING}../fw.o --add --in --protocol QWE ${SETCOLOR_NORMAL}
../fw.o --add --in --protocol QWE          # Wrong type of protocol
echo

${SETCOLOR_WARNING}../fw.o --add --in --protocol ${SETCOLOR_NORMAL}
../fw.o --add --in --protocol       # No type of protocol
echo

${SETCOLOR_WARNING}../fw.o --add --out --src_ip ${SETCOLOR_NORMAL}
../fw.o --add --out --src_ip # No param
echo

${SETCOLOR_WARNING}../fw.o --add --out --dest_ip 1000.56.56.121 ${SETCOLOR_NORMAL}
../fw.o --add --out --dest_ip 1000.56.56.121 # ERROR
echo

${SETCOLOR_WARNING}../fw.o --delete qw34 ${SETCOLOR_NORMAL}
../fw.o --delete qw34 # Wrong index
echo

${SETCOLOR_WARNING}../fw.o --delete ${SETCOLOR_NORMAL}
../fw.o --delete # No index
echo

${SETCOLOR_WARNING}../fw.o --add --help ${SETCOLOR_NORMAL}
../fw.o --add --help # Action mentioned
echo

${SETCOLOR_WARNING}../fw.o --add --all ${SETCOLOR_NORMAL}
../fw.o --add --all # Action mentioned
echo

${SETCOLOR_WARNING}../fw.o --help --add ${SETCOLOR_NORMAL}
../fw.o --help --add # Useless command
echo

${SETCOLOR_WARNING}../fw.o --add --in --src_domain ${SETCOLOR_NORMAL}
../fw.o --add --in --src_domain # No param
echo

${SETCOLOR_WARNING}../fw.o --add --in --src_domain vk.com --dest_domain google.com ${SETCOLOR_NORMAL}
../fw.o --add --in --src_domain vk.com --dest_domain google.com # Two domain names
echo

${SETCOLOR_WARNING}../fw.o --add --in --protocol --src_ip --dest_port ${SETCOLOR_NORMAL}
../fw.o --add --in --protocol --src_ip --dest_port # No params
echo