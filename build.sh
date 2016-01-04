#!/bin/bash
#../cc65/bin/cl65 -L ../cc65/lib -t nes -I ../cc65/include hello.c -o hello.nes
../cc65/bin/cc65 --add-source -t nes -I ../cc65/include hello.c
if [[ $? != 0 ]]; then
    exit $?
fi
cat chrtest.s hello.s > temp.s
mv temp.s hello.s
sed -i 's/\.import\s\+_foo//' hello.s
../cc65/bin/ca65 hello.s
../cc65/bin/ld65 -L ../cc65/lib -t nes hello.o ../cc65/lib/nes.lib -o hello.nes
