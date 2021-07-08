#include "BigInteger.h"
#include <stdio.h>

int main () {
    std::cout << (BigInt("-1024102410241024") / BigInt("1234")) << std::endl;
    return 0;
}