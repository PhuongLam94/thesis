// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    union { __size8 byte; struct { __size8 TESTUPS1:1; __size8 bit2:1; __size8 bit3:1; __size8 bit4:1; __size8 bit5:1; __size8 bit6:1; __size8 bit7:1; __size8 bit8:1; } bits; } OPTIONS; 		// r114
    union { __size8 byte; struct { __size8 bit1:1; __size8 bit2:1; __size8 bit3:1; __size8 bit4:1; __size8 bit5:1; __size8 bit6:1; __size8 bit7:1; __size8 bit8:1; } bits; } a; 		// r8

    a.byte = *OPTIONS;
    OPTIONS.bits.TESTUPS1 = 1;
    a.bits.bit1 = 0;
    return a.x;
}

//phuong.lam test
