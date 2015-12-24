#include <nes.h>
#include <conio.h>

#define read_addr(pointer) *((unsigned char*)pointer)
#define write_addr(pointer, value) read_addr(pointer) = value

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

void delay(int i) {
    while(i--) {
        waitvblank();
    }
}

int main(void) {
    char j, k, l, oy;
    unsigned int i;
    unsigned char pad, bgcolor, x, y;
    const char s[][33] = {
        " this was a triumph\0", 
        " i'm making a note here\0", 
        " HUGE SUCCESS\0",
        "it's hard to overstate my satis-\0"}; 
    waitvblank();
    screensize(&x,&y);

    textcolor(COLOR_WHITE);

    clrscr();

    j = y - 4;
    oy = j;

    cprintf(" push buttan\r\n");

    for(i = 0; i < 256; i++) {
        cprintf("%c", (char)i);
        if((i % 30)==0) {
            cprintf("\r\n");
        }
    }

    write_addr(0x2005, 0x00);
    write_addr(0x2005, 0x00);
    write_addr(0x2001, 0x08);
    for(;;) {
        delay(50);
        for(k = 0; k < 4; k++) {
            gotoxy(0, oy + k);
            for(l = 0; l < x; l++) {
                cputc(32);
            }
        }
        if(--j < 4) {
            j = y - 4;
        }
        for(k = 0; k < 4; k++) {
            gotoxy(0, j + k);
            cputs(s[k]);
        }
        oy = j;
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
