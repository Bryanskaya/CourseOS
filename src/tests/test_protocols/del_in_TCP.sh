#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --protocol TCP
${FW} --delete --in --protocol TCP
echo

echo ${FW} --all
${FW} --all
echo