#include <nes.h>

void write_string(char *str) {
    *((unsigned char*)0x2006) = 0x21;
    *((unsigned char*)0x2006) = 0x42;

    while(*str) {
        *((unsigned char*)0x2007) = *str;
        str++;
    }
}

int main(void) {
    waitvblank();

    *((unsigned char*)0x2006) = 0x3F;
    *((unsigned char*)0x2006) = 0x00;
    *((unsigned char*)0x2007) = 0x01;

    *((unsigned char*)0x2006) = 0x3F;
    *((unsigned char*)0x2006) = 0x03;
    *((unsigned char*)0x2007) = 0x30;

    write_string("Hello, NES");

    *((unsigned char*)0x2005) = 0x00;
    *((unsigned char*)0x2005) = 0x00;
    *((unsigned char*)0x2001) = 0x08;

    for(;;);

    return 0;
}
