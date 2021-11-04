#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --src_ip 192.168.45.43
${FW} --delete --in --src_ip 192.168.45.43
echo

echo ${FW} --all
${FW} --all
echo