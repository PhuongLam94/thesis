// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    union { __size32 byte; struct { __size8 TESTUPS1:1; __size8 TESTUPS2:1; __size8 TESTUPS3:1; __size8 TESTUPS4:1; __size8 TESTUPS5:1; __size8 TESTUPS6:1; __size8 TESTUPS7:1; __size8 TESTUPS8:1; } bits; } OPTIONS; 		// r114

    OPTIONS.bits.TESTUPS1 = 1;
    *(__size8*)OPTIONS.byte = 0x270f;
    ACC.1.bits.bit57570094 = 0;
    return;
}

//phuong.lam test
