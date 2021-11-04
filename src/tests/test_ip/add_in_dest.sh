#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --dest_ip 192.168.45.4
${FW} --add --in --dest_ip 192.168.45.4
echo

echo ${FW} --all
${FW} --all
echo