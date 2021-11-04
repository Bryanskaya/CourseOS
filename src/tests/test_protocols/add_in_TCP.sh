#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --protocol TCP
${FW} --add --in --protocol TCP
echo

echo ${FW} --all
${FW} --all
echo