#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --out --protocol TCP
${FW} --delete --out --protocol TCP
echo

echo ${FW} --all
${FW} --all
echo