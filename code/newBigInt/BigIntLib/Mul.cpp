#include <future>
#include "BigInt.h"

BigInt BigInt::_multiply(BigInt firstNumber, BigInt secondNumber, bool iteration_thirst) {
    if (std::min(firstNumber._digits.size(), secondNumber._digits.size()) <= _defaultKaratsuba) {
        firstNumber = BigInt::_removeLeadingZeros(firstNumber);
        secondNumber = BigInt::_removeLeadingZeros(secondNumber);
        BigInt result;
        result._digits.resize(firstNumber._digits.size() + secondNumber._digits.size());
        long long composition;
        for (long long fPosition = firstNumber._digits.size() - 1; fPosition >= 0; fPosition--) {
            for (long long sPosition = secondNumber._digits.size() - 1; sPosition >= 0; sPosition--) {
                composition = (long long)firstNumber._digits[fPosition] * (long long)secondNumber._digits[sPosition] + result._digits[fPosition + sPosition + 1];
                result._digits[fPosition + sPosition + 1] = composition % BigInt::_BASE;
                result._digits[fPosition + sPosition] = result._digits[fPosition + sPosition] + (composition / BigInt::_BASE);
            }
        }
        return BigInt::_removeLeadingZeros(result);
    }
    if (firstNumber._digits.size() % 2 != 0) {
        firstNumber._digits.insert(firstNumber._digits.begin(), 0);
    }
    if (secondNumber._digits.size() % 2 != 0) {
        secondNumber._digits.insert(secondNumber._digits.begin(), 0);
    }
    if (firstNumber._digits.size() > secondNumber._digits.size()) {
        secondNumber = BigInt::_shiftRight(secondNumber, firstNumber._digits.size() - secondNumber._digits.size());
    }
    else {
        firstNumber = BigInt::_shiftRight(firstNumber, secondNumber._digits.size() - firstNumber._digits.size());
    }
    long long maxSize = firstNumber._digits.size();
    long long splitPoint = maxSize / 2;

    BigInt firstNumberLeft;
    BigInt firstNumberRight;
    BigInt secondNumberLeft;
    BigInt secondNumberRight;

    firstNumberLeft._digits.resize(splitPoint);
    firstNumberRight._digits.resize(splitPoint);
    secondNumberLeft._digits.resize(splitPoint);
    secondNumberRight._digits.resize(splitPoint);

    std::copy(firstNumber._digits.begin(), firstNumber._digits.begin() + splitPoint, firstNumberLeft._digits.begin());
    std::copy(secondNumber._digits.begin(), secondNumber._digits.begin() + splitPoint, secondNumberLeft._digits.begin());
    std::copy(firstNumber._digits.begin() + splitPoint, firstNumber._digits.begin() + maxSize, firstNumberRight._digits.begin());
    std::copy(secondNumber._digits.begin() + splitPoint, secondNumber._digits.begin() + maxSize, secondNumberRight._digits.begin());

    BigInt firstProduct;
    BigInt secondProduct;
    BigInt thirdProduct;

    if (iteration_thirst and std::thread::hardware_concurrency() >= 3) {
        auto thread_first = std::async(BigInt::_multiply, firstNumberLeft, secondNumberLeft, false);
        auto thread_second = std::async(BigInt::_multiply, firstNumberRight, secondNumberRight, false);
        thirdProduct = BigInt::_multiply(BigInt::_removeLeadingZeros(firstNumberLeft)
            + BigInt::_removeLeadingZeros(firstNumberRight), BigInt::_removeLeadingZeros(secondNumberLeft)
            + BigInt::_removeLeadingZeros(secondNumberRight), false);
        firstProduct = thread_first.get();
        secondProduct = thread_second.get();
    }
    else if (iteration_thirst and std::thread::hardware_concurrency() == 2) {
        auto thread_first = std::async(BigInt::_multiply, firstNumberLeft, secondNumberLeft, false);
        secondProduct = BigInt::_multiply(firstNumberRight, secondNumberRight, false);
        thirdProduct = BigInt::_multiply(BigInt::_removeLeadingZeros(firstNumberLeft)
            + BigInt::_removeLeadingZeros(firstNumberRight), BigInt::_removeLeadingZeros(secondNumberLeft)
            + BigInt::_removeLeadingZeros(secondNumberRight), false);
        firstProduct = thread_first.get();
    }
    else {
        firstProduct = BigInt::_multiply(firstNumberLeft, secondNumberLeft, false);
        secondProduct = BigInt::_multiply(firstNumberRight, secondNumberRight, false);
        thirdProduct = BigInt::_multiply(BigInt::_removeLeadingZeros(firstNumberLeft)
            + BigInt::_removeLeadingZeros(firstNumberRight), BigInt::_removeLeadingZeros(secondNumberLeft)
            + BigInt::_removeLeadingZeros(secondNumberRight), false);
    }
    return BigInt::_shiftLeft(firstProduct, maxSize) + BigInt::_shiftLeft(thirdProduct - (firstProduct + secondProduct), splitPoint) + secondProduct;
}
BigInt operator *(const BigInt& firstNumber, const BigInt& secondNumber) {
    BigInt result = BigInt::_multiply(firstNumber, secondNumber, true);
    result._positive = (firstNumber._positive == secondNumber._positive);
    return result;
}
BigInt BigInt::operator *=(const BigInt& number) {
    return *this = *this * number;
}