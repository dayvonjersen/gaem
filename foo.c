#define read_addr(pointer) *((unsigned char*)pointer)
#define write_addr(pointer, value) read_addr(pointer) = value

extern unsigned char foo[];

void main(void) {
    int i;

    write_addr(0x2000, 0);
    write_addr(0x2001, 0);

    write_addr(0x2006, 0x3f);
    write_addr(0x2006, 0x00);

    write_addr(0x2007, 0x0C);
    write_addr(0x2007, 0x17);
    write_addr(0x2007, 0x28);
    write_addr(0x2007, 0x39);

    write_addr(0x2006, 0x21);
    write_addr(0x2006, 0xca);

    for(i=0;i<100;++i) {
        write_addr(0x2007, foo[i]);
    }

    write_addr(0x2006, 0x00);
    write_addr(0x2006, 0x00);
    write_addr(0x2005, 0x00);
    write_addr(0x2005, 0x00);

    write_addr(0x2000, 0x90);
    write_addr(0x2001, 0x1e);

    for(;;);
}
