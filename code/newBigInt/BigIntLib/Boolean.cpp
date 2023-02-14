#include <algorithm>
#include "BigInt.h"


bool operator ==(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber._positive != secondNumber._positive) {
        return false;
    }
    if (firstNumber._digits.size() != secondNumber._digits.size()) {
        return false;
    }
    for (long long i = 0; i < firstNumber._digits.size(); i++) {
        if (firstNumber._digits[i] != secondNumber._digits[i]) {
            return false;
        }
    }
    return true;
}
bool operator !=(BigInt firstNumber, BigInt secondNumber) {
    return !(std::move(firstNumber) == std::move(secondNumber));
}
bool operator >(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber == secondNumber) {
        return false;
    }
    if (firstNumber._positive and !secondNumber._positive) {
        return true;
    }
    if (!firstNumber._positive and secondNumber._positive) {
        return false;
    }
    if (!firstNumber._positive and !secondNumber._positive) {
        firstNumber._positive = true;
        secondNumber._positive = true;
        return !(firstNumber > secondNumber);
    }
    if (firstNumber._digits.size() > secondNumber._digits.size()) {
        return true;
    }
    if (firstNumber._digits.size() < secondNumber._digits.size()) {
        return false;
    }
    return !(std::lexicographical_compare(firstNumber._digits.begin(), firstNumber._digits.end(), secondNumber._digits.begin(), secondNumber._digits.end()));
}
bool operator <(const BigInt& firstNumber, const BigInt& secondNumber) {
    if (firstNumber != secondNumber and !(firstNumber > secondNumber)) {
        return true;
    }
    return false;
}
bool operator >=(const BigInt& firstNumber, const BigInt& secondNumber) {
    if (firstNumber > secondNumber or firstNumber == secondNumber) {
        return true;
    }
    return false;
}
bool operator <=(const BigInt& firstNumber, const BigInt& secondNumber) {
    if (firstNumber < secondNumber or firstNumber == secondNumber) {
        return true;
    }
    return false;
}