#/bin/bash
../cc65/bin/cc65 -Oi foo.c --add-source
../cc65/bin/ca65 reset.s 
../cc65/bin/ca65 foo.s 
../cc65/bin/ld65 -C nes.cfg -o foo.nes reset.o foo.o ../cc65/lib/nes.lib