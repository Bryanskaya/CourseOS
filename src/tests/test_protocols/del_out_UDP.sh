#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --out --protocol UDP
${FW} --delete --out --protocol UDP
echo

echo ${FW} --all
${FW} --all
echo