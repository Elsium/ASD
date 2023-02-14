#include "BigInt.h"

std::pair<BigInt, BigInt> BigInt::_divide(BigInt firstNumber, BigInt secondNumber) {
    if (secondNumber == 0) {
        throw "Division by zero.";
    }
    if (secondNumber == 0) {
        throw "Remainder of the division can`t be unpositive.";
    }
    if (secondNumber._digits.size() == 1) {
        int divider = secondNumber._digits.front();
        int carry = 0;
        long long composition;
        for (long long i = 0; i < firstNumber._digits.size(); i++) {
            composition = (long long)firstNumber._digits[i] + (long long)carry * (long long)BigInt::_BASE;
            firstNumber._digits[i] = composition / divider;
            carry = composition % divider;
        }
        firstNumber._positive = (firstNumber._positive == secondNumber._positive);
        return std::make_pair(BigInt::_removeLeadingZeros(firstNumber), BigInt(carry));
    }

    BigInt div;
    div._positive = (firstNumber._positive == secondNumber._positive);
    BigInt mod;
    firstNumber._positive = true;
    secondNumber._positive = true;
    if (firstNumber < secondNumber) {
        return std::make_pair(BigInt(0), firstNumber);
    }
    div._digits.resize(0);
    mod._digits.resize(0);
    int quotient;
    int left;
    int middle;
    int right;
    BigInt tmp;
    for (long long i = 0; i < firstNumber._digits.size(); i++) {
        mod._digits.push_back(firstNumber._digits[i]);
        quotient = 0;
        left = 0;
        right = BigInt::_BASE;
        while (left <= right) {
            middle = (left + right) / 2;
            tmp = secondNumber * middle;
            if (tmp <= mod) {
                quotient = middle;
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
        mod = mod - (secondNumber * quotient);
        if (!div._digits.empty() or quotient != 0) {
            div._digits.push_back(quotient);
        }
        if (mod == 0) {
            mod._digits.resize(0);
        }
    }
    if (mod._digits.empty()) {
        return std::make_pair(div, BigInt(0));
    }
    return std::make_pair(div, mod);
}
BigInt operator /(BigInt firstNumber, BigInt secondNumber) {
    return BigInt::_divide(firstNumber, secondNumber).first;
}
BigInt BigInt::operator /=(BigInt number) {
    return *this = *this / std::move(number);
}
BigInt operator %(BigInt firstNumber, BigInt secondNumber) {
    return BigInt::_divide(firstNumber, secondNumber).second;
}
BigInt BigInt::operator %=(BigInt number) {
    return *this = *this % std::move(number);
}