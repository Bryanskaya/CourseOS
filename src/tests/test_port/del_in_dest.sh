#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --dest_port 443
${FW} --delete --in --dest_port 443
echo

echo ${FW} --all
${FW} --all
echo