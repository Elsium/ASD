#include "BigInt.h"
#include <sstream>

BigInt BigInt::_removeLeadingZeros(BigInt number) {
    long long border = number._digits.size() - 1;
    for (long long i = 0; i < number._digits.size() - 1; i = i + 1) {
        if (number._digits[i] != 0) {
            border = i;
            break;
        }
    }
    number._digits.erase(number._digits.begin(), number._digits.begin() + border);
    return number;
}
BigInt BigInt::_shiftRight(BigInt number, long long power) {
    number._digits.reserve(power);
    for (long long i = 0; i < power; i = i + 1) {
        number._digits.insert(number._digits.begin(), 0);
    }
    return number;
}
BigInt BigInt::_shiftLeft(BigInt number, long long power) {
    if (number == 0) {
        return number;
    }
    number._digits.resize(number._digits.size() + power);
    return number;
}
BigInt BigInt::_abs(BigInt firstNumber) {
    firstNumber._positive = true;
    return firstNumber;
}
bool BigInt::_isEven(BigInt number) {
    if (number._digits.back() % 2 == 0) {
        return true;
    }
    return false;
}
bool BigInt::_isOdd(BigInt number) {
    return !BigInt::_isEven(std::move(number));
}
long long BigInt::_size(BigInt number) {
    return (((long long)number._digits.size() - (long long)1) * (long long)_BASELength) + (long long)std::to_string(number._digits.front()).size();
}
BigInt BigInt::max(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber > secondNumber) {
        return firstNumber;
    }
    return secondNumber;
}
BigInt BigInt::min(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber < secondNumber) {
        return firstNumber;
    }
    return secondNumber;
}