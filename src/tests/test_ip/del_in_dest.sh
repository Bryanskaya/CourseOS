#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --dest_ip 192.168.45.4
${FW} --delete --in --dest_ip 192.168.45.4
echo

echo ${FW} --all
${FW} --all
echo