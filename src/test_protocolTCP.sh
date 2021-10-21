#!/bin/sh

echo ./fw.o --add --in --protocol TCP
./fw.o --add --in --protocol TCP
echo

echo ./fw.o --all
./fw.o --all
echo