#!/bin/sh

FW=../../fw.o

echo ${FW} --add --out --protocol UDP
${FW} --add --out --protocol UDP
echo

echo ${FW} --all
${FW} --all
echo