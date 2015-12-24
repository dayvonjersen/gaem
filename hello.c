#include <nes.h>
#include <conio.h>

#define read_addr(pointer) *((unsigned char*)pointer)
#define write_addr(pointer, value) read_addr(pointer) = value

#define BUTTON_A        0x80
#define BUTTON_B        0x40
#define BUTTON_SELECT   0x20
#define BUTTON_START    0x10
#define BUTTON_UP       0x08
#define BUTTON_DOWN     0x04
#define BUTTON_LEFT     0x02
#define BUTTON_RIGHT    0x01

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

/*
int main(void) {
    char j, k, l, oy;
    unsigned int i;
    unsigned char pad, color, x, y;
    const char s[][33] = {
        " this was a triumph\0", 
        " i'm making a note here\0", 
        " HUGE SUCCESS\0",
        "it's hard to overstate my satis-\0"}; 
    waitvblank();
    screensize(&x,&y);

    bgcolor(COLOR_VIOLET);
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
        if(pad == BUTTON_UP) {
            color = COLOR_RED;
        } else if(pad == BUTTON_DOWN) {
            color = COLOR_WHITE;
        } else if(pad == BUTTON_LEFT) {
            color = COLOR_GRAY1;
        } else if(pad == BUTTON_RIGHT) {
            color = COLOR_GREEN;
        } else {
            color = 0;
        }
        if(color) {
            write_addr(0x2006, 0x3F);
            write_addr(0x2006, 0x00);
            write_addr(0x2007, color);
        }
    }

    return 0;
}*/

#define presskey(k) key & k
void main(void) {
    unsigned char key;
    unsigned char x=0,y=0,oldx=0,oldy=0;
//    unsigned char x2=0,y2=0,oldx2=0,oldy2=0;   
    cprintf("waiting for press joystick....",);
    while(1){   
        key=read_joystick1();
        if(presskey(BUTTON_UP))--y;
        if(presskey(BUTTON_DOWN))++y;
        if(presskey(BUTTON_LEFT))--x;
        if(presskey(BUTTON_RIGHT))++x;
/*        key=read_joystick();      
        if(presskey(BUTTON_UP))--y2;
        if(presskey(BUTTON_DOWN))++y2;
        if(presskey(BUTTON_LEFT))--x2;
        if(presskey(BUTTON_RIGHT))++x2;     */
        if(x!=oldx || y!=oldy /*|| x2!=oldx2 || y2!=oldy2*/){   
            clrscr();   
            gotoxy(1,1);
            cprintf("x=%u y=%u "/*"x=%u y=%u"*/,x,y/*,x2,y2*/);   
            gotoxy(x,y);    
            cprintf("A");   
/*            gotoxy(x2,y2);
            cprintf("B");*/
            oldx=x;
            oldy=y;
/*            oldx2=x2;
            oldy2=y2;*/
            delay(10);
        }
    }
}
