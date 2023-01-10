#ifndef UNTITLED3_BIGINT_H
#define UNTITLED3_BIGINT_H

#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>

class BigInt {
private:
    static const int BASE = 1000000000;
    std::vector<int> _digits;
    bool _isNegative;
    void _removeLeadingZero();
    void _shiftRight();
    BigInt(std::vector<int>);
public:
    class divideByZero: public std::exception {  };

    BigInt();
    BigInt(const BigInt&);
    BigInt(std::string);
    BigInt(signed char);
    BigInt(unsigned char);
    BigInt(signed short);
    BigInt(unsigned short);
    BigInt(signed int);
    BigInt(unsigned int);
    BigInt(signed long);
    BigInt(unsigned long);
    BigInt(signed long long);
    BigInt(unsigned long long);

    friend std::ostream& operator <<(std::ostream&, const BigInt&);
    operator std::string() const;

    const BigInt operator +() const;
    const BigInt operator -() const;
    const BigInt operator ++();
    const BigInt operator ++(int);
    const BigInt operator --();
    const BigInt operator --(int);
    friend bool operator ==(const BigInt&, const BigInt&);
    friend bool operator <(const BigInt&, const BigInt&);
    friend bool operator !=(const BigInt&, const BigInt&);
    friend bool operator <=(const BigInt&, const BigInt&);
    friend bool operator >(const BigInt&, const BigInt&);
    friend bool operator >=(const BigInt&, const BigInt&);
    friend const BigInt operator +(BigInt, const BigInt&);
    BigInt& operator +=(const BigInt&);
    friend const BigInt operator -(BigInt, const BigInt&);
    BigInt& operator -=(const BigInt&);
    friend const BigInt operator *(const BigInt&, const BigInt&);
    BigInt& operator *=(const BigInt&);
    friend const BigInt operator /(const BigInt&, const BigInt&);
    BigInt& operator /=(const BigInt&);
    friend const BigInt operator %(const BigInt&, const BigInt&);
    BigInt& operator %=(const BigInt&);
};
BigInt::BigInt() {
    this->_isNegative = false;
    this->_digits.push_back(0);
}
BigInt::BigInt(const BigInt& x) {
    this->_digits = x._digits;
    this->_isNegative = x._isNegative;
};
BigInt::BigInt(std::string str) {
    if (str.length() == 0) {
        this->_isNegative = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_isNegative = true;
        } else {
            this->_isNegative = false;
        }
        for (long long i = str.length(); i > 0; i-=9) {
            if (i < 9) this->_digits.push_back(atoi(str.substr(0,i).c_str()));
            else this->_digits.push_back(atoi(str.substr(i-9,9).c_str()));
        }
        this->_removeLeadingZero();
    }
}
BigInt::BigInt(unsigned short l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(signed short l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(unsigned int l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(signed int l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(unsigned long l) {
    this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(signed long l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(unsigned long long l) {
    this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(signed long long l) {
    if(l < 0) {
        this->_isNegative = true;
        l = -l;
    } else this->_isNegative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while(l != 0);
}
BigInt::BigInt(std::vector <int> v) {
    this->_digits = v;
}

void BigInt::_removeLeadingZero() {
    while(this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }
    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_isNegative = false;
}
void BigInt::_shiftRight() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
    if(bi._digits.empty()) os << 0;
    else {
        if(bi._isNegative) os << '-';
        os << bi._digits.back();
        char oldFill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; i--) {
            os << std::setw(9) << bi._digits[i];
        }
        os.fill(oldFill);
    }
    return os;
}
BigInt::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

const BigInt BigInt::operator +() const {
    return BigInt(*this);
}
const BigInt BigInt::operator -() const {
    BigInt copy(*this);
    copy._isNegative = !copy._isNegative;
    return copy;
}
const BigInt BigInt::operator++() {
    return *this += (long long)1;
}
const BigInt BigInt::operator--() {
    return *this -= (long long)1;
}
const BigInt BigInt::operator ++(int) {
    *this += 1;
    return *this - 1;
}
const BigInt BigInt::operator--(int) {
    *this -= (long long)1;
    return *this + (long long)1;
}

bool operator ==(const BigInt& left, const BigInt& right) {
    if (left._isNegative != right._isNegative) return false;
    if (left._digits.empty()) {
        if(right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }
    if (right._digits.empty()) {
        if(left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }
    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;
    return true;
}
bool operator !=(const BigInt& left, const BigInt& right) {
    return !(left == right);
}
bool operator <(const BigInt& left, const BigInt& right) {
    if (left == right) return false;
    if (left._isNegative) {
        if(right._isNegative) return ((-right) < (-left));
        else return true;
    } else if (right._isNegative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        } else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }
            return false;
        }
    }
}
bool operator >(const BigInt& left, const BigInt& right) {
    return !(left < right);
}
bool operator <=(const BigInt& left, const BigInt& right) {
    return (left < right || left == right);
}
bool operator >=(const BigInt& left, const BigInt& right) {
    return (left > right || left == right);
}

const BigInt operator +(BigInt left, const BigInt& right) {
    if (left._isNegative) {
        if(right._isNegative) return -(-left + (-right));
        else return right - (-left);
    } else if (right._isNegative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= BigInt::BASE;
        if (carry != 0) left._digits[i] -= BigInt::BASE;
    }
    return left;
}
const BigInt operator -(BigInt left, const BigInt& right) {
    if (right._isNegative) return left + (-right);
    else if (left._isNegative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += BigInt::BASE;
    }

    left._removeLeadingZero();
    return left;
}

BigInt& BigInt::operator +=(const BigInt& value) {
    return *this = (*this + value);
}
BigInt& BigInt::operator -=(const BigInt& value) {
    return *this = (*this - value);
}

const BigInt operator *(const BigInt& left, const BigInt& right) {
    BigInt result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                            left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % BigInt::BASE);
            carry = static_cast<int>(cur / BigInt::BASE);
        }
    }
    result._isNegative = left._isNegative != right._isNegative;
    result._removeLeadingZero();
    return result;
}
const BigInt operator /(const BigInt& left, const BigInt& right) {
    if (right == 0) throw BigInt::divideByZero();
    BigInt b = right;
    b._isNegative = false;
    BigInt result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shiftRight();
        current._digits[0] = left._digits[i];
        current._removeLeadingZero();
        int x = 0, l = 0, r = BigInt::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInt t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._isNegative = left._isNegative != right._isNegative;
    result._removeLeadingZero();
    return result;
}

BigInt& BigInt::operator *=(const BigInt& value) {
    return *this = (*this * value);
}
BigInt& BigInt::operator /=(const BigInt& value) {
    return *this = (*this / value);
}

const BigInt operator %(const BigInt& left, const BigInt& right) {
    BigInt result = left - (left / right) * right;
    if (result._isNegative) result += right;
    return result;
}
BigInt& BigInt::operator %=(const BigInt& value) {
    return *this = (*this % value);
}
#endif