#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --protocol UDP
${FW} --delete --in --protocol UDP
echo

echo ${FW} --all
${FW} --all
echo