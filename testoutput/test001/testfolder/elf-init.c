// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    union { __size8 x; struct { __size8 bit1:1; __size8 bit2:1; __size8 bit3:1; __size8 bit4:1; __size8 bit5:1; __size8 bit6:1; __size8 bit7:1; __size8 bit8:1; } m; } a; 		// r8

    a.m.bit8 = 1;
    return a.x;
}

