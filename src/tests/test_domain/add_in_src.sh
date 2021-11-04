#!/bin/sh

FW=../../fw.o

echo ${FW} --add --in --src_domain google.ru
${FW} --add --in --src_domain google.ru
echo

echo ${FW} --all
${FW} --all
echo
