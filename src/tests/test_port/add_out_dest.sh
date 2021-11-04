#!/bin/sh

FW=../../fw.o

echo ${FW} --add --out --dest_port 443
${FW} --add --out --dest_port 443
echo

echo ${FW} --all
${FW} --all
echo