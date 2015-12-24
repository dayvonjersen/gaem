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

unsigned char read_joystick1() {
    unsigned char n = 8, joy_state = 0;
    write_addr(0x4016, 1);
    write_addr(0x4016, 0);
    while(n) {
        joy_state = (joy_state << 1) | read_addr(0x4016) & 1;
        n--;
    }
    return joy_state;
}

int main(void) {
    char text[12];
    unsigned char pad, bgcolor;

    waitvblank();

    write_addr(0x2006, 0x3F);
    write_addr(0x2006, 0x00);
    write_addr(0x2007, COLOR_VIOLET);

    write_addr(0x2006, 0x3F);
    write_addr(0x2006, 0x03);
    write_addr(0x2007, 0x30);

    sprintf(text, "push buttan");
    write_string(text);

    write_addr(0x2005, 0x00);
    write_addr(0x2005, 0x00);
    write_addr(0x2001, 0x08);
    for(;;) {
        pad = read_joystick1();
        if(pad == KEY_UP) {
            bgcolor = COLOR_RED;
        } else if(pad == KEY_DOWN) {
            bgcolor = COLOR_WHITE;
        } else if(pad == KEY_LEFT) {
            bgcolor = COLOR_GRAY1;
        } else if(pad == KEY_RIGHT) {
            bgcolor = COLOR_GREEN;
        } else {
            bgcolor = 0;
        }
        if(bgcolor) {
            write_addr(0x2006, 0x3F);
            write_addr(0x2006, 0x00);
            write_addr(0x2007, bgcolor);
        }
    }

    return 0;
}
