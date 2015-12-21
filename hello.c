#include <nes.h>

#define write_addr(pointer, value) *((unsigned char*)pointer) = value

void write_string(char *str) {
    write_addr(0x2006, 0x21);
    write_addr(0x2006, 0x42);

    while(*str) {
        write_addr(0x2007, *str);
        str++;
    }
}

int main(void) {
    int i;
    long t;
    waitvblank();

    i = 0;
    t = 0;
    for(;;) {
        t++;
        if(t > 350) {
            write_addr(0x2006, 0x3F);
            write_addr(0x2006, 0x00);
            write_addr(0x2007, i);

            i++;
            if(i > 255) i = 0;

            write_string("._.");
            write_addr(0x2005, 0x00);
            write_addr(0x2005, 0x00);
            write_addr(0x2001, 0x02|0x04|0x08);

            t = 0;
        }
    }

    return 0;
}
