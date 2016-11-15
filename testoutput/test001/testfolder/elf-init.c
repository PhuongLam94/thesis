// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    __size8 *BTS; 		// r66
    __size32 SLVFLGMAP; 		// r208
    __size32 SMPDUP; 		// r117
    __size32 XROVLY; 		// r123
    union { __size8 byte; struct { __size8 bit1:1; __size8 bit2:1; __size8 bit3:1; __size8 bit4:1; __size8 bit5:1; __size8 bit6:1; __size8 bit7:1; __size8 bit8:1; } bits; } a; 		// r8
    __size8 a_1; 		// r8
    __size32 specbits5; 		// r224

    if (SMPDUP != 0) {
        a_1 = *(__size8 *)56;
        if (specbits5 == 1) {
            a_1 = *BTS;
            a_1 = *(__size8 *)(XROVLY + 20);
        }
    } else {
        a_1 = *(__size8 *)(SLVFLGMAP + 20);
        *(__size8*)(SLVFLGMAP + 20) = a_1;
    }
    return a_1;
}

//phuong.lam test
