#!/bin/sh

SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_WARNING="echo \\033[1;33m"
SETCOLOR_NORMAL="\\033[0;39m"

FW=../../fw.o

echo 
${SETCOLOR_WARNING}${FW} --help ${SETCOLOR_NORMAL}
${FW} --help          # OK
echo

${SETCOLOR_WARNING}${FW} -h ${SETCOLOR_NORMAL}
${FW} -h              # OK
echo