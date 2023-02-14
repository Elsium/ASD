#pragma once
#include <iostream>
#include <vector>


class BigInt {
public:
    BigInt();
    BigInt(std::string string);
    BigInt(signed int number);
    BigInt(unsigned int number);
    BigInt(signed long number);
    BigInt(unsigned long number);
    BigInt(signed long long number);
    BigInt(unsigned long long number);
    static std::string toString(BigInt number);
    friend std::ostream& operator <<(std::ostream& ostream, const BigInt& number);
    friend std::istream& operator >>(std::istream& ostream, BigInt& number);
    BigInt operator =(std::string);
    friend bool operator ==(BigInt firstNumber, BigInt secondNumber);
    friend bool operator !=(BigInt firstNumber, BigInt secondNumber);
    friend bool operator >(BigInt firstNumber, BigInt secondNumber);
    friend bool operator <(const BigInt& firstNumber, const BigInt& secondNumber);
    friend bool operator >=(const BigInt& firstNumber, const BigInt& secondNumber);
    friend bool operator <=(const BigInt& firstNumber, const BigInt& secondNumber);
    static BigInt _abs(BigInt firstNumber);
    static bool _isEven(BigInt number);
    static bool _isOdd(BigInt number);
    static long long _size(BigInt number);
    static BigInt max(BigInt firstNumber, BigInt secondNumber);
    static BigInt min(BigInt firstNumber, BigInt secondNumber);
    friend BigInt operator +(BigInt firstNumber, BigInt secondNumber);
    BigInt operator +=(BigInt number);
    BigInt operator ++();
    BigInt operator ++(int);
    friend BigInt operator -(BigInt firstNumber, BigInt secondNumber);
    BigInt operator -=(BigInt number);
    BigInt operator --();
    BigInt operator --(int);
    friend BigInt operator *(const BigInt& firstNumber, const BigInt& secondNumber);
    BigInt operator *=(const BigInt& number);
    friend BigInt operator /(BigInt firstNumber, BigInt secondNumber);
    BigInt operator /=(BigInt number);
    friend BigInt operator %(BigInt firstNumber, BigInt secondNumber);
    BigInt operator %=(BigInt number);
    static BigInt pow(BigInt firstNumber, BigInt secondNumber);
private:
    std::vector<int> _digits;
    bool _positive;
    static const _int64 _BASE = 1000000000;
    static const _int64 _BASELength = 9;
    static const _int64 _defaultKaratsuba = 256;
    static std::vector<int> _stringToVector(const std::string& string);
    static BigInt _removeLeadingZeros(BigInt number);
    static BigInt _shiftRight(BigInt number, long long shift_power);
    static BigInt _shiftLeft(BigInt number, long long shift_power);
    static BigInt _multiply(BigInt firstNumber, BigInt secondNumber, bool iteration_thirst);
    static std::pair<BigInt, BigInt> _divide(BigInt firstNumber, BigInt secondNumber);
};