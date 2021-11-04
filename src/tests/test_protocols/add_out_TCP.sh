#!/bin/sh

FW=../../fw.o

echo ${FW} --add --out --protocol TCP
${FW} --add --out --protocol TCP
echo

echo ${FW} --all
${FW} --all
echo