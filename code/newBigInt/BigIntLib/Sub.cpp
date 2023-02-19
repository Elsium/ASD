#include "BigInt.h"


BigInt operator -(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber._positive && !secondNumber._positive) {
        secondNumber._positive = true;
        return firstNumber + secondNumber;
    }
    if (!firstNumber._positive && secondNumber._positive) {
        firstNumber._positive = true;
        BigInt tmp = firstNumber + secondNumber;
        tmp._positive = false;
        return tmp;
    }
    if (!firstNumber._positive && !secondNumber._positive) {
        firstNumber._positive = true;
        secondNumber._positive = true;
        BigInt tmp;
        tmp = firstNumber;
        firstNumber = secondNumber;
        secondNumber = tmp;
        delete& tmp;
    }
    if (firstNumber < secondNumber) {
        BigInt tmp = firstNumber;
        firstNumber = secondNumber;
        secondNumber = tmp;
        firstNumber._positive = false;
        delete& tmp;
    }
    secondNumber = BigInt::_shiftRight(secondNumber, firstNumber._digits.size() - secondNumber._digits.size());
    int different;
    for (long long i = firstNumber._digits.size() - 1; i >= 0; i--) {
        different = firstNumber._digits[i] - secondNumber._digits[i];
        if (different >= 0) {
            firstNumber._digits[i] = different;
        }
        else {
            firstNumber._digits[i] = different + BigInt::_BASE;
            for (long long j = i - 1; true; j--) {
                if (firstNumber._digits[j] == 0) {
                    firstNumber._digits[j] = BigInt::_BASE - 1;
                }
                else {
                    firstNumber._digits[j] = firstNumber._digits[j] - 1;
                    break;
                }
            }
        }
    }
    return BigInt::_removeLeadingZeros(firstNumber);
}
BigInt BigInt::operator -=(BigInt number) {
    return *this = *this - std::move(number);
}
BigInt BigInt::operator --() {
    return *this = *this - 1;
}
BigInt BigInt::operator --(int) {
    *this = *this - 1;
    return *this = *this + 1;
}