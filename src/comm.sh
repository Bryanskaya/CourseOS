#!/bin/sh

echo ./fw.o --add --out --src_ip 101.102.103.104 --src_port 80 --dest_ip 123.125.147.25 --dest_port 55555 --protocol TCP
./fw.o --add --out --src_ip 101.102.103.104 --src_port 80 --dest_ip 123.125.147.25 --dest_port 55555 --protocol TCP
echo

echo ./fw.o --add --in --protocol TCP
./fw.o --add --in --protocol TCP
echo

echo ./fw.o --all
./fw.o --all
echo