// address: 0x104f4
int main(int argc, char *argv[], char *envp[]) {
    __size32 g3; 		// r3
    __size32 local0; 		// m[o6 - 8]
    int o0; 		// r8

    __isoc99_scanf();
    o0 = add1(local0, g3 + local0);
    printf("Sum = %ld\n", o0);
    return 0;
}

// address: 0x1055c
__size32 add1(__size32 param1, __size32 param2) {
    __size32 o0; 		// r8

    o0 = add2(param1, param2);
    return o0;
}

// address: 0x1057c
__size32 add2(__size32 param1, __size32 param2) {
    return param2 + param1 + 2;
}
