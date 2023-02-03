#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>

static int _charToInt(char c) noexcept(false) {
	switch (c) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default:
		std::string message("Char in string not a int. Received: ");
		message.push_back(c);
		throw std::invalid_argument(message);
	}
}



	class BigInt {

	public: 
		BigInt(std::string string) {
			if (string.length() > 0) {
				if (string.at(0) == '-' || string.at(0) == '+') {
					this->_positive = string.at(0) == '+';
					string = string.substr(1);
				}
				this->_digits.reserve(string.length());
				for (int i = string.size() - 1; i >= 0; i--) {
					this->_digits.push_back(_charToInt(string[i]));
				}
			}
			else {
				this->_digits.push_back(0);
			}
			this->_removeLeftZeros();
		}

		BigInt() : BigInt("0") {}

		BigInt(long long value) : BigInt(std::to_string(value)) {}

		BigInt& operator=(const BigInt& number) {
			this->_digits = number._digits;
			this->_positive = number._positive;
			return *this;
		}

		BigInt operator+() const {
			return *this;
		}
		BigInt operator-() const {
			BigInt number = *this;
			if (!number._isZero()) {
				number._positive = !number._isPositive();
			}
			return number;
		}

		BigInt operator+(const BigInt& number) const {
			if (this->_isPositive() && !number._isPositive()) {
				return *this - number._absoluteValue();
			}
			else if (!this->_isPositive() && number._isPositive()) {
				return -(number - this->_absoluteValue());
			}
			if (number._isZero()) {
				return *this;
			}
			if (this->_isZero()) {
				return number;
			}

			BigInt result = *this;

			for (int i = 0; i < number._lenght(); i++) {
				int digit = number._digits[i];
				if (i < result._lenght()) {
					result._digits[i] += digit;
				}
				else {
					result._digits.push_back(digit);
				}
			}
			result._doCarryOver();
			result._afterOperation();
			return result;
		}

		BigInt operator-(const BigInt& number) const {
			if (this->_isPositive() && !number._isPositive()) {
				return *this + number._absoluteValue();
			}
			else if (!this->_isPositive() && number._isPositive()) {
				return -(number + this->_absoluteValue());
			}
			if (number._isZero()) {
				return *this;
			}
			if (this->_isZero()) {
				return number;
			}

			BigInt result;
			const BigInt* smaller;

			if (this->_lenght() >= number._lenght()) {
				result = *this;
				smaller = &number;
			}
			else {
				result = number;
				smaller = this;
			}

			for (int i = 0; i < smaller->_lenght(); i++) {
				int dif = result._digits[i] - smaller->_digits[i];
				if (dif < 0) {
					for (int j = i + 1; j < result._lenght(); j++) {
						if (result._digits[j] == 0) {
							result._digits[j] = 9;
						}
						else {
							dif += 10;
							result._digits[j]--;
							break;
						}
					}
				}

				result._digits[i] = dif;
			}
			result._positive = *this >= number;
			result._afterOperation();
			return result;
		}

		BigInt operator*(const BigInt& number) const {
			if (this->_isZero() || number._isZero()) {
				return BigInt(0);
			}
			if (this->_isOne()) {
				return number;
			}
			if (number._isOne()) {
				return *this;
			}

			if (this->_lenght() < 10 && number._lenght() < 10) {
				return BigInt(this->_asLongLong() * number._asLongLong());
			}

			int maxLenght = std::max(this->_lenght(), number._lenght());
			int splitPoint = maxLenght / 2;
			std::pair<BigInt, BigInt> splitThis = this->_splitAt(splitPoint);
			std::pair<BigInt, BigInt> splitNumber = number._splitAt(splitPoint);

			BigInt secondProduct = splitThis.second * splitNumber.second;
			BigInt firstProduct = splitThis.first * splitNumber.first;
			BigInt sumProduct = (splitThis.second + splitThis.first) * (splitNumber.second + splitNumber.first);

			BigInt firstPadded = firstProduct._times10(splitPoint * 2);
			BigInt deltaPadded = (sumProduct - firstProduct - secondProduct)._times10(splitPoint);

			return firstPadded + deltaPadded + secondProduct;
		}

		BigInt operator/(const BigInt& number) const {
			return this->_divide(number).first;
		}
		BigInt operator%(const BigInt& number) const {
			return this->_divide(number).second;
		}
		BigInt pow(BigInt number) const {
			if (this->_isZero() && number._isZero()) {
				throw std::invalid_argument("Zero to the power of Zero is undefined.");
			}
			if (!number._isPositive()) {
				throw std::invalid_argument("Power cannot be negative.");
			}
			if (this->_isZero()) {
				return BigInt(0);
			}
			if (number._isZero()) {
				return BigInt(1);
			}
			if (number._isOdd()) {
				return *this * (*this * *this).pow((number - 1) / 2);
			}
			else {
				return (*this * *this).pow(number / 2);
			}
		}

		BigInt& operator+=(const BigInt& number) {
			*this = *this + number;
			return *this;
		}

		BigInt& operator-=(const BigInt& number) {
			*this = *this - number;
			return *this;
		}

		BigInt& operator*=(const BigInt& number) {
			*this = *this * number;
			return *this;
		}

		BigInt& operator/=(const BigInt& number) {
			*this = *this / number;
			return *this;
		}

		BigInt& operator%=(const BigInt& number) {
			*this = *this % number;
			return *this;
		}

		BigInt& operator++() {
			*this += 1;
			return *this;
		}

		BigInt& operator--() {
			*this -= 1;
			return *this;
		}


		BigInt operator++(int) {
			BigInt copy = *this;
			*this += 1;
			return copy;
		}


		BigInt operator--(int) {
			BigInt copy = *this;
			*this -= 1;
			return copy;
		}

		bool operator<(const BigInt& number) const {
			if (this->_positive != number._positive) {
				return !this->_positive;
			}
			if (this->_lenght() != number._lenght()) {
				return this->_lenght() < number._lenght();
			}
			if (this->_positive) {
				return this->_asString() < number._asString();
			}
			return -(*this) > -number;
		}

		bool operator>(const BigInt& number) const {
			return *this >= number && !(*this == number);
		}

		bool operator<=(const BigInt& number) const {
			return *this == number || *this < number;
		}

		bool operator>=(const BigInt& number) const {
			return !(*this < number);
		}

		bool operator==(const BigInt& number) const {
			return this->_positive == number._positive && this->_digits == number._digits;
		}

		bool operator!=(const BigInt& number) const {
			return !(*this == number);
		}

		friend std::ostream& operator<<(std::ostream& stream, BigInt const& number) {
			stream << number._asString();
			return stream;
		}

		friend std::istream& operator>>(std::istream& istream, BigInt& number) {
			std::string in;
			istream >> in;
			number = BigInt(in);
			return istream;
		}

		std::string _asString() const {
			std::stringstream ss;
			if (!this->_isPositive()) {
				ss << '-';
			}
			for (int i = this->_lenght() - 1; i >= 0; i--) {
				ss << this->_digits[i];
			}
			return ss.str();
		}

		BigInt _absoluteValue() const {
			BigInt temp = *this;
			temp._positive = true;
			return temp;
		}

		BigInt _times10(int times = 1) const {
			BigInt temp = *this;
			for (int i = 0; i < times; i++) {
				temp._digits.insert(temp._digits.begin(), 0);
			}
			temp._afterOperation();
			return temp;
		}

		std::pair<BigInt, BigInt> _splitAt(long long splitPos) const {
			splitPos = std::min(std::max(splitPos, (long long)0), (long long)this->_lenght());

			std::vector<int> firstHalf;
			firstHalf.reserve(splitPos);

			std::vector<int> secondHalf;
			secondHalf.reserve(this->_lenght() - splitPos);

			for (size_t i = 0; i < this->_lenght(); i++) {
				int digit = this->_digits[i];
				if (i > splitPos - 1) {
					firstHalf.push_back(digit);
				}
				else {
					secondHalf.push_back(digit);
				}
			}

			return std::make_pair(BigInt(firstHalf), BigInt(secondHalf));
		}

		bool _fitsInLongLong() const {
			return this->_lenght() < 19;
		}

		long long _asLongLong() const {
			return std::stoll(this->_asString());
		}

		size_t _lenght() const {
			return this->_digits.size();
		}

		bool _isOdd() const {
			return this->_digits[0] & 1;
		}

		bool _isEven() const {
			return !this->_isOdd();
		}

		bool _isZero() const {
			return this->_lenght() == 1 && this->_digits[0] == 0;
		}

		bool _isOne() const {
			return this->_positive && this->_lenght() == 1 && this->_digits[0] == 1;
		}

		bool _isPositive() const {
			return this->_positive;
		}


	private:

		bool _positive = true;
		std::vector<int> _digits;

		void _removeLeftZeros() {
			for (int i = this->_lenght() - 1; i >= 1; i--) {
				if (this->_digits[i] == 0) {
					this->_digits.pop_back();
				}
				else {
					break;
				}
			}
		}

		void _doCarryOver(int start = 0) {
			for (int i = start; i < this->_lenght(); i++) {
				if (this->_digits[i] > 9) {
					this->_digits[i] -= 10;
					if (i + 1 < this->_lenght()) {
						this->_digits[i + 1]++;
					}
					else {
						this->_digits.push_back(1);
						return _doCarryOver(i);
					}
				}
			}
		}

		void _afterOperation() {
			this->_removeLeftZeros();
			if (this->_isZero()) {
				this->_positive = true;
			}
		}

		std::pair<BigInt, BigInt> _divide(const BigInt& number) const {
			if (number._isZero()) {
				throw std::invalid_argument("Division or Module by 0 is undefined.");
			}
			if (number._isOne()) {
				return std::make_pair(*this, BigInt(0));
			}
			if (number == *this) {
				return std::make_pair(BigInt(1), BigInt(0));
			}
			if (number > * this) {
				return std::make_pair(BigInt(0), *this);
			}

			if (this->_fitsInLongLong() && number._fitsInLongLong()) {
				long long llThis = this->_asLongLong();
				long long llNumber = number._asLongLong();
				return std::make_pair(BigInt(llThis / llNumber), BigInt(abs(llThis % llNumber)));
			}

			BigInt mod = this->_absoluteValue();
			const BigInt absoluteNumber = number._absoluteValue();

			BigInt div;

			int lenghDifference = mod._lenght() - absoluteNumber._lenght();
			while (lenghDifference-- >= 0) {
				BigInt toSubtract = absoluteNumber._times10(lenghDifference);
				while (mod >= toSubtract) {
					div += BigInt(1)._times10(lenghDifference);
					mod -= toSubtract;
				}
			}
			div._positive = this->_positive == number._positive;
			div._afterOperation();
			mod._afterOperation();
			return std::make_pair(div, mod);
		}

		BigInt(const std::vector<int>& vector, bool reversed = false) {
			if (vector.size() > 0) {
				this->_digits = vector;
				if (reversed) {
					std::reverse(this->_digits.begin(), this->_digits.end());
				}
			}
			else {
				this->_digits.push_back(0);
			}
			this->_afterOperation();
		}
	};