#include "BigInt.h"
#include <sstream>


std::vector<int> BigInt::_stringToVector(const std::string& string) {
    std::vector<int> result;
    if (string.size() % _BASELength == 0) {
        result.resize(string.size() / _BASELength);
    }
    else {
        result.resize(string.size() / _BASELength + 1);
    }
    for (long long stringPosition = string.size() - 1, resultPosition = result.size() - 1; stringPosition >= 0; stringPosition -= _BASELength, resultPosition--) {
        if ((stringPosition + 1) - _BASELength <= 0) {
            result[resultPosition] = std::stoi(string.substr(0, stringPosition + 1));
        }
        else {
            result[resultPosition] = std::stoi(string.substr(stringPosition - _BASELength + 1, _BASELength));
        }
    }
    return result;
}
std::string BigInt::toString(BigInt number) {
    if (number._digits.size() == 1 and number._digits.front() == 0) {
        return "0";
    }
    std::string result;
    if (!number._positive) {
        result.append("-");
    }
    result.reserve(number._digits.size() * (_BASELength - 1));
    std::string tmp;
    result.append(std::to_string(number._digits[0]));
    for (long long i = 1; i < number._digits.size(); i = i + 1) {
        tmp = std::to_string(number._digits[i]);
        tmp.reserve(_BASELength - tmp.size());
        while (tmp.size() < _BASELength) {
            tmp.insert(tmp.begin(), '0');
        }
        result.append(tmp);
    }
    return result;
}
BigInt::BigInt() {
    _digits.resize(1);
    _positive = true;
}
BigInt::BigInt(std::string string) {
    if (string.empty() or (string.size() == 1 and string[0] == '-')) {
        throw "String does not contain a number.";
    }
    if (string.front() == '-') {
        string.erase(string.begin());
        _positive = false;
    }
    else {
        _positive = true;
    }
    for (long long i = 0; i < string.size(); i = i + 1) {
        if (string[i] < 48 or string[i] > 57) {
            throw "String contains not int char.";
        }
    }
    while (string.size() != 1 and string.front() == '0') {
        string.erase(string.begin());
    }
    _digits = BigInt::_stringToVector(string);
}
BigInt::BigInt(signed int number) {
    std::string string = std::to_string(number);
    if (string.front() == '-') {
        string.erase(string.begin());
        _positive = false;
    }
    else {
        _positive = true;
    }
    _digits = BigInt::_stringToVector(string);
}
BigInt::BigInt(unsigned int number) {
    _positive = true;
    _digits = BigInt::_stringToVector(std::to_string(number));
}
BigInt::BigInt(signed long number) {
    std::string string = std::to_string(number);
    if (string.front() == '-') {
        string.erase(string.begin());
        _positive = false;
    }
    else {
        _positive = true;
    }
    _digits = BigInt::_stringToVector(string);
}
BigInt::BigInt(unsigned long number) {
    _positive = true;
    _digits = BigInt::_stringToVector(std::to_string(number));
}
BigInt::BigInt(signed long long number) {
    std::string string = std::to_string(number);
    if (string.front() == '-') {
        string.erase(string.begin());
        _positive = false;
    }
    else {
        _positive = true;
    }
    _digits = BigInt::_stringToVector(string);
}
BigInt::BigInt(unsigned long long number) {
    _positive = true;
    _digits = BigInt::_stringToVector(std::to_string(number));
}
std::ostream& operator <<(std::ostream& ostream, const BigInt& number) {
    std::string string = BigInt::toString(number);
    ostream << string;
    return ostream;
}
std::istream& operator>>(std::istream& istream, BigInt& number) {
    std::string in;
    istream >> in;
    number = BigInt(in);
    return istream;
}
BigInt BigInt::operator =(std::string number) {
    return *this = BigInt(number);
}