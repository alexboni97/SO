#!/bin/bash
directorio=$1

if [ ! -d "$directorio" ]; then
    mkdir "$directorio"
else
    rm -r "$directorio"/*
fi
cd "$directorio"
mkdir  "subdir"
touch "fichero1"
echo "0123456789" > "fichero2"
ln -s "fichero2" "enlaceS" 
ln "fichero2" "enlaceH"

