#!/bin/bash
#../cc65/bin/cl65 -L ../cc65/lib -t nes -I ../cc65/include hello.c -o hello.nes
../cc65/bin/cc65 --add-source -t nes -I ../cc65/include hello.c
cat hello.s chrtest.s > temp.s
mv temp.s hello.s
../cc65/bin/ca65 hello.s
../cc65/bin/ld65 -L ../cc65/lib -t nes hello.o ../cc65/lib/nes.lib -o hello.nes
