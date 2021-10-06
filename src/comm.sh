#!/bin/sh

echo ./fw.o --add --out --src_ip 123.125.147.25 --src_port 80 --dest_ip 123.125.147.25 --dest_port 55555 --protocol TCP
./fw.o --add --out --src_ip 123.125.147.25 --src_port 80 --dest_ip 147.258.36.123 --dest_port 55555 --protocol TCP
echo

echo ./fw.o --add --in --protocol TCP
./fw.o --add --in --protocol TCP
echo

echo ./fw.o --all
./fw.o --all
echo