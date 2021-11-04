#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --protocol UDP
${FW} --add --in --protocol UDP
echo

echo ${FW} --all
${FW} --all
echo