#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --out --src_ip 192.168.45.4
${FW} --delete --out --src_ip 192.168.45.4
echo

echo ${FW} --all
${FW} --all
echo