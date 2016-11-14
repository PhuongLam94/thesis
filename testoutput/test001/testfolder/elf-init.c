// address: 0x10474
int main(int argc, char *argv[], char *envp[]) {
    __size32 OPTIONS; 		// r214
    __size8 TESTUPS1; 		// r117
    __size8 a; 		// r8

    a = *(__size8 *)(OPTIONS + 10);
    TESTUPS1 = 1;
    return a;
}

//phuong.lam test
