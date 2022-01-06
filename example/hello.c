/* simple Hello World program on the QEMU serial port */
void clear();
void puts(const char *s);

void _start(void)
{
    clear();
    puts("Hello World! ");
    while (1);
}

void outb(int port, int val)
{
    asm("outb %b1, %w0" : : "d" (port), "a" (val));
}

unsigned char inb(int port)
{
    int val;
    asm("inb %w1, %b0" : "=a"(val) : "d" (port));
    return val;
}
void clear(){
    char *scr = (char*)0xb8000;
    int i;
    for(i=0;i<2000;i++){*scr++=' ';*scr++='0';}
}
void puts(const char *s)
{
    const char*t = s;
    while (*s) {
        outb(0x3f8, *s++);
        while ((inb(0x3f8 + 5) & 0x60) != 0x60);
    }
    char *scr = (char*)0xb8000;
    while(*t){
	    *scr = *t++;
	    scr += 2;
    }
}


