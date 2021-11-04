#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --src_ip 192.168.45.43
${FW} --add --in --src_ip 192.168.45.43
echo

echo ${FW} --all
${FW} --all
echo