#include "BigInt.h"


BigInt BigInt::pow(BigInt firstNumber, BigInt secondNumber) {
    if (firstNumber == 0 and secondNumber == 0) {
        throw "Can`t raise zero to zero degree.";
    }
    if (secondNumber < 0) {
        throw "Specified number is less than zero.";
    }
    BigInt result = 1;
    while (secondNumber != 0) {
        if (_isEven(secondNumber)) {
            secondNumber = secondNumber / 2;
            firstNumber = firstNumber * firstNumber;
        }
        else {
            secondNumber = secondNumber - 1;
            result = result * firstNumber;
        }
    }
    return result;
}