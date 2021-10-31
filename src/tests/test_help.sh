#!/bin/sh

SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_WARNING="echo \\033[1;33m"
SETCOLOR_NORMAL="\\033[0;39m"

echo 
${SETCOLOR_WARNING}../fw.o --help ${SETCOLOR_NORMAL}
../fw.o --help          # OK
echo

${SETCOLOR_WARNING}../fw.o -h ${SETCOLOR_NORMAL}
../fw.o -h              # OK
echo