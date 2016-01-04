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
    while(i--) waitvblank();
}

void game_over(void) {
    const char s[][33] = {
        " this was a triumph\0", 
        " i'm making a note here\0", 
        " HUGE SUCCESS\0",
        "it's hard to overstate my satis-\0"}; 
    char j, k, l, oy;
    unsigned char key, x, y;

    screensize(&x,&y);
    clrscr();
    bgcolor(COLOR_CYAN);

    j = y - 4;
    oy = j;    
    for(;;) {
        key = read_joystick1();
        if(key & BUTTON_START) {
            break;
        }

        clrscr();
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
        delay(50);
    }
}

struct meme {
    int x, y;
};

const struct meme faec[14] = {
    {7,10},
    {7,18},
    {12,14},
    {16,14},
    {19,18},
    {21,17},
    {22,16},
    {23,13},
    {23,14},
    {23,15},
    {19,10},
    {21,11},
    {22,12}
};

void memefaec(void) {
    short i;
    for(i = 0; i < 14; i++) {
        if(faec[i].x) {
            gotoxy(faec[i].x,faec[i].y);
            cprintf(":^)");
        }
    }
}

extern unsigned char foo[100];

void main(void) {
    unsigned char key;
    unsigned char x, y, oldx, oldy;
    int i;
start:
    x = 14; y = 12; oldx = 0; oldy = 0;

    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);

    waitvblank();

    // XXX
//    write_addr(0x2006, 0x21);
//    write_addr(0x2006, 0x42);
    for(i = 0; i < sizeof(foo); i++) {
      //  write_addr(0x2007, foo[i]);
      gotoxy(i, 0);
      cprintf("%u", foo[i]);
    }
    while(1);
    // XXX

    memefaec();

    for(;;) {   
        key = read_joystick1();
        if(key & BUTTON_UP)    y--;
        if(key & BUTTON_DOWN)  y++;
        if(key & BUTTON_LEFT)  x--;
        if(key & BUTTON_RIGHT) x++;

        if(y > 27) {
            if(oldy < 26) y = 0;
            else y = 27;
        }
        if(x > 29) {
            if(oldx < 28) x = 0;
            else x = 29;
        }

        if(x != oldx || y != oldy) {   
            clrscr();
            memefaec();
            gotoxy(1,1);
            cprintf("x=%u y=%u", x, y);   
            gotoxy(x,y);    
            cprintf(":^)");   
            oldx = x;
            oldy = y;
            delay(10);

            if(x == 20 && y == 21) {
                game_over();
                goto start;
            }
        }
    }
}
