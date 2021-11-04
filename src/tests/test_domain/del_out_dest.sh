#!/bin/sh

FW=../../fw.o

echo ${FW} --delete --out --dest_domain vk.com
${FW} --delete --out --dest_domain vk.com
echo

echo ${FW} --all
${FW} --all
echo