#include <nes.h>
#include <stdio.h>

#define read_addr(pointer) *((unsigned char*)pointer)
#define write_addr(pointer, value) read_addr(pointer) = value

void write_string(char *str) {
    write_addr(0x2006, 0x21);
    write_addr(0x2006, 0x42);

    while(*str != '\0') {
        write_addr(0x2007, *str);
        str++;
    }
}

int main(void) {
    char text[12];

    waitvblank();

    write_addr(0x2006, 0x3F);
    write_addr(0x2006, 0x00);
    write_addr(0x2007, COLOR_VIOLET);

    write_addr(0x2006, 0x3F);
    write_addr(0x2006, 0x03);
    write_addr(0x2007, 0x30);

    sprintf(text, "just a test");
    write_string(text);

    write_addr(0x2005, 0x00);
    write_addr(0x2005, 0x00);
    write_addr(0x2001, 0x08);
    for(;;) {
    }

    return 0;
}
