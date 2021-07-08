/****************************
 * @toc: BigInteger.h
 * @author: steve
 * @time: 2021-07-04
 * @dev: This class is used
 * to store and handle Big-
 * Integers. It can express
 * 2 ^ 1024 at most.
 ***************************/
#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>
#include <cstring>
#include <string>

class BigInt {
    std::string val;
    BigInt mutiply(const BigInt& , const BigInt& );
public:
    BigInt(){val = "0";}
    BigInt(const char* );
    BigInt(const BigInt& );
    BigInt(const std::string& );
    BigInt operator+ (const BigInt& );
    BigInt operator- (const BigInt& );
    BigInt operator* (const BigInt& );
    BigInt operator/ (const BigInt& );
    BigInt operator% (const BigInt& );
    BigInt& operator+= (const BigInt& );
    BigInt& operator-= (const BigInt& );
    BigInt& operator*= (const BigInt& );
    BigInt& operator/= (const BigInt& );
    BigInt& operator%= (const BigInt& );
    BigInt& operator= (const BigInt& );
    bool operator> (const BigInt& );
    bool operator>= (const BigInt& );
    bool operator< (const BigInt& );
    bool operator<= (const BigInt& );
    bool operator== (const BigInt& );
    friend std::ostream& operator<< (std::ostream& output, const BigInt& obj);
};

#endif