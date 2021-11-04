#!/bin/sh

SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_WARNING="echo \\033[1;33m"
SETCOLOR_NORMAL="\\033[0;39m"

FW=../../fw.o

clear
echo ---------------------TEST COMMANDS---------------------
echo

${SETCOLOR_WARNING}${FW} ${SETCOLOR_NORMAL}
${FW}    
echo            # No commands

${SETCOLOR_WARNING}${FW} --add --delete ${SETCOLOR_NORMAL}
${FW} --add --delete    
echo            # No rule for delete

${SETCOLOR_WARNING}${FW} --in --out ${SETCOLOR_NORMAL}
${FW} --in --out                 # Forbidden to mention in and out direction at the same time
echo

${SETCOLOR_WARNING}${FW} --add ${SETCOLOR_NORMAL}
${FW} --add   # No rule
echo

${SETCOLOR_WARNING}${FW} --add --in TCP ${SETCOLOR_NORMAL}
${FW} --add --in TCP   # No keys
echo

${SETCOLOR_WARNING}${FW} --in --protocol TCP ${SETCOLOR_NORMAL}
${FW} --in --protocol TCP   # No action
echo

${SETCOLOR_WARNING}${FW} --add --protocol UDP ${SETCOLOR_NORMAL}
${FW} --add --protocol UDP  # No direction
echo

${SETCOLOR_WARNING}${FW} --add --in --protocol QWE ${SETCOLOR_NORMAL}
${FW} --add --in --protocol QWE          # Wrong type of protocol
echo

${SETCOLOR_WARNING}${FW} --add --in --protocol ${SETCOLOR_NORMAL}
${FW} --add --in --protocol       # No type of protocol
echo

${SETCOLOR_WARNING}${FW} --add --out --src_ip ${SETCOLOR_NORMAL}
${FW} --add --out --src_ip # No param
echo

${SETCOLOR_WARNING}${FW} --add --out --dest_ip 1000.56.56.121 ${SETCOLOR_NORMAL}
${FW} --add --out --dest_ip 1000.56.56.121 # ERROR
echo

${SETCOLOR_WARNING}${FW} --delete qw34 ${SETCOLOR_NORMAL}
${FW} --delete qw34 # Wrong index
echo

${SETCOLOR_WARNING}${FW} --delete ${SETCOLOR_NORMAL}
${FW} --delete # No index
echo

${SETCOLOR_WARNING}${FW} --add --help ${SETCOLOR_NORMAL}
${FW} --add --help # Action mentioned
echo

${SETCOLOR_WARNING}${FW} --add --all ${SETCOLOR_NORMAL}
${FW} --add --all # Action mentioned
echo

${SETCOLOR_WARNING}${FW} --help --add ${SETCOLOR_NORMAL}
${FW} --help --add # Useless command
echo

${SETCOLOR_WARNING}${FW} --add --in --src_domain ${SETCOLOR_NORMAL}
${FW} --add --in --src_domain # No param
echo

${SETCOLOR_WARNING}${FW} --add --in --src_domain vk.com --dest_domain google.com ${SETCOLOR_NORMAL}
${FW} --add --in --src_domain vk.com --dest_domain google.com # Two domain names
echo

${SETCOLOR_WARNING}${FW} --add --in --protocol --src_ip --dest_port ${SETCOLOR_NORMAL}
${FW} --add --in --protocol --src_ip --dest_port # No params
echo