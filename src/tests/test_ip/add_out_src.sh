#!/bin/sh

FW=../../fw.o

echo ${FW} --add --out --src_ip 192.168.45.4
${FW} --add --out --src_ip 192.168.45.4
echo

echo ${FW} --all
${FW} --all
echo