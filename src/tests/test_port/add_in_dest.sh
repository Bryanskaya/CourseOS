#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --dest_port 443
${FW} --add --in --dest_port 443
echo

echo ${FW} --all
${FW} --all
echo