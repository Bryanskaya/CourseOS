#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --out --dest_port 443
${FW} --delete --out --dest_port 443
echo

echo ${FW} --all
${FW} --all
echo