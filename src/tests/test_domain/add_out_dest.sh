#!/bin/sh

FW=../../fw.o

echo ${FW} --add --out --dest_domain vk.com
${FW} --add --out --dest_domain vk.com
echo

echo ${FW} --all
${FW} --all
echo