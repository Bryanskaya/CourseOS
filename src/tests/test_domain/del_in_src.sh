#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --in --src_domain google.ru
${FW} --delete --in --src_domain google.ru
echo

echo ${FW} --all
${FW} --all
echo