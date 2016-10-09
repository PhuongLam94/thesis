// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    union { __size32 byte; struct { __size8 TESTUPS1:1; __size8 TESTUPS2:1; __size8 TESTUPS3:1; __size8 TESTUPS4:1; __size8 TESTUPS5:1; __size8 TESTUPS6:1; __size8 TESTUPS7:1; __size8 TESTUPS8:1; } bits; } OPTIONS; 		// r114
    union { __size32 byte; struct { __size8 TESTUPS21:1; __size8 TESTUPS22:1; __size8 TESTUPS23:1; __size8 TESTUPS24:1; __size8 TESTUPS25:1; __size8 TESTUPS26:1; __size8 TESTUPS27:1; __size8 TESTUPS28:1; } bits; } OPTIONS2; 		// r117
    __size8 a; 		// r8

    a = *OPTIONS.byte;
    OPTIONS.TESTUPS1.bits = 1;
    a = *OPTIONS2.byte;
    OPTIONS.TESTUPS1.bits = 0;
    return a;
}

//phuong.lam test
