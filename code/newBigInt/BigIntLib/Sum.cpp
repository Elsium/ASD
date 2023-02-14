#include "BigInt.h"


BigInt operator +(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber._positive && !secondNumber._positive) {
        secondNumber._positive = true;
        return firstNumber - secondNumber;
    }
    if (!firstNumber._positive && secondNumber._positive) {
        firstNumber._positive = true;
        return secondNumber - firstNumber;
    }
    if (!firstNumber._positive && !secondNumber._positive) {
        secondNumber._positive = true;
    }
    if (firstNumber._digits.size() > secondNumber._digits.size()) {
        secondNumber = BigInt::_shiftRight(secondNumber, firstNumber._digits.size() - secondNumber._digits.size());
    }
    else {
        firstNumber = BigInt::_shiftRight(firstNumber, secondNumber._digits.size() - firstNumber._digits.size());
    }
    int sum;
    int carry = 0;
    for (long long i = firstNumber._digits.size() - 1; i >= 0; i--) {
        sum = firstNumber._digits[i] + secondNumber._digits[i] + carry;
        carry = sum / BigInt::_BASE;
        firstNumber._digits[i] = sum % BigInt::_BASE;
    }
    if (carry != 0) {
        firstNumber._digits.insert(firstNumber._digits.begin(), carry);
    }
    return firstNumber;
}
BigInt BigInt::operator +=(BigInt number) {
    return *this = *this + std::move(number);
}
BigInt BigInt::operator ++() {
    return *this = *this + 1;
}
BigInt BigInt::operator ++(int) {
    *this = *this + 1;
    return *this = *this - 1;
}