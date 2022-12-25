#pragma once

#include <BigInt.h>

class BigIrreducibleFraction {
	public:
		BigIrreducibleFraction();
		BigIrreducibleFraction(const std::string& irreducibleFraction);
		BigIrreducibleFraction(const BigInt& numerator, const BigInt& denominator);
		BigIrreducibleFraction operator+(const BigIrreducibleFraction& summand);
		BigIrreducibleFraction operator-(const BigIrreducibleFraction& subtrahend);
		BigIrreducibleFraction operator*(const BigIrreducibleFraction& multiplier);
		BigIrreducibleFraction operator/(const BigIrreducibleFraction& divisor);
		BigIrreducibleFraction operator+=(const BigIrreducibleFraction& summand);
		BigIrreducibleFraction operator-=(const BigIrreducibleFraction& subtrahend);
		BigIrreducibleFraction operator*=(const BigIrreducibleFraction& multiplier);
		BigIrreducibleFraction operator/=(const BigIrreducibleFraction& divisor);
		BigIrreducibleFraction& operator++();
		BigIrreducibleFraction& operator--();
		BigIrreducibleFraction operator++(int);
		BigIrreducibleFraction operator--(int);
		BigIrreducibleFraction operator+();
		BigIrreducibleFraction operator-();
		BigIrreducibleFraction operator=(const std::string& irreducibleFraction);

		bool operator<(const BigIrreducibleFraction& num);
		bool operator<=(const BigIrreducibleFraction& num);
		bool operator>(const BigIrreducibleFraction& num);
		bool operator>=(const BigIrreducibleFraction& num);
		bool operator==(const BigIrreducibleFraction& num);
		bool operator!=(const BigIrreducibleFraction& num);

		friend std::ostream& operator<<(std::ostream& os, const BigIrreducibleFraction& num);
	private:
		BigInt numerator;
		BigInt denominator;
		static BigIrreducibleFraction Reduce(BigIrreducibleFraction num);
};

BigIrreducibleFraction BigIrreducibleFraction::Reduce(BigIrreducibleFraction num) {
	BigInt nod = 1;
	do {
		BigInt numNumeratorCopy = (num.numerator > 0 ? num.numerator : -num.numerator);
		BigInt numDenominatorCopy = (num.denominator > 0 ? num.denominator : -num.denominator);
		while ((numNumeratorCopy != 0) && (numDenominatorCopy != 0))
			if (numNumeratorCopy > numDenominatorCopy)
				numNumeratorCopy %= numDenominatorCopy;
			else
				numDenominatorCopy %= numNumeratorCopy;
		BigInt nod = numNumeratorCopy + numDenominatorCopy;
		num.numerator /= nod;
		num.denominator /= nod;
	} while (nod != 1);
	if (num.denominator < 0)
		num *= BigIrreducibleFraction(-1, 1);
	return num;
}
BigIrreducibleFraction::BigIrreducibleFraction() {
	numerator = 0;
	denominator = 1;
}
BigIrreducibleFraction::BigIrreducibleFraction(const std::string& irreducibleFraction) {
	int forwardSlashPos = irreducibleFraction.find('/');
	if (forwardSlashPos == std::string::npos) {
		numerator = irreducibleFraction;
		denominator = 1;
	}
	else {
		numerator = irreducibleFraction.substr(0, forwardSlashPos);
		denominator = irreducibleFraction.substr(forwardSlashPos + 1, irreducibleFraction.length() - forwardSlashPos - 1);
	}
	BigInt nod = 1;
	do {
		BigInt numNumeratorCopy = (numerator > 0 ? numerator : -numerator);
		BigInt numDenominatorCopy = (denominator > 0 ? denominator : -denominator);
		while ((numNumeratorCopy != 0) && (numDenominatorCopy != 0))
			if (numNumeratorCopy > numDenominatorCopy)
				numNumeratorCopy %= numDenominatorCopy;
			else
				numDenominatorCopy %= numNumeratorCopy;
		BigInt nod = numNumeratorCopy + numDenominatorCopy;
		numerator /= nod;
		denominator /= nod;
	} while (nod != 1);
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
}
BigIrreducibleFraction::BigIrreducibleFraction(const BigInt& inNumerator, const BigInt& inDenominator) {
	numerator = inNumerator;
	denominator = inDenominator;
	BigInt nod = 1;
	do {
		BigInt numNumeratorCopy = (numerator > 0 ? numerator : -numerator);
		BigInt numDenominatorCopy = (denominator > 0 ? denominator : -denominator);
		while ((numNumeratorCopy != 0) && (numDenominatorCopy != 0))
			if (numNumeratorCopy > numDenominatorCopy)
				numNumeratorCopy %= numDenominatorCopy;
			else
				numDenominatorCopy %= numNumeratorCopy;
		BigInt nod = numNumeratorCopy + numDenominatorCopy;
		numerator /= nod;
		denominator /= nod;
	} while (nod != 1);
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
}

BigIrreducibleFraction BigIrreducibleFraction::operator+(const BigIrreducibleFraction & summand) {
	return Reduce(BigIrreducibleFraction(this->numerator * summand.denominator + this->denominator * summand.numerator, this->denominator * summand.denominator));
}
BigIrreducibleFraction BigIrreducibleFraction::operator-(const BigIrreducibleFraction & subtrahend) {
	return Reduce(BigIrreducibleFraction(this->numerator * subtrahend.denominator - this->denominator * subtrahend.numerator, this->denominator * subtrahend.denominator));
}
BigIrreducibleFraction BigIrreducibleFraction::operator*(const BigIrreducibleFraction& multiplier) {
	return Reduce(BigIrreducibleFraction(this->numerator * multiplier.numerator, this->denominator * multiplier.denominator));
}
BigIrreducibleFraction BigIrreducibleFraction::operator/(const BigIrreducibleFraction& divisor) {
	return Reduce(BigIrreducibleFraction(this->numerator * divisor.denominator, this->denominator * divisor.numerator));
}
BigIrreducibleFraction BigIrreducibleFraction::operator+=(const BigIrreducibleFraction & summand) {
	return *this = *this + summand;
}
BigIrreducibleFraction BigIrreducibleFraction::operator-=(const BigIrreducibleFraction & subtrahend) {
	return *this = *this - subtrahend;
}
BigIrreducibleFraction BigIrreducibleFraction::operator*=(const BigIrreducibleFraction & multiplier){
	return *this = *this * multiplier;
}
BigIrreducibleFraction BigIrreducibleFraction::operator/=(const BigIrreducibleFraction & divisor){
	return *this = *this / divisor;
}
BigIrreducibleFraction& BigIrreducibleFraction::operator++() {
	BigIrreducibleFraction one(1, 1);
	return *this = *this + one;
}
BigIrreducibleFraction& BigIrreducibleFraction::operator--() {
	BigIrreducibleFraction one(1, 1);
	return *this = *this - one;
}
BigIrreducibleFraction BigIrreducibleFraction::operator++(int) {
	BigIrreducibleFraction temp = *this;
	++*this;
	return temp;
}
BigIrreducibleFraction BigIrreducibleFraction::operator--(int) {
	BigIrreducibleFraction temp = *this;
	--*this;
	return temp;
}
BigIrreducibleFraction BigIrreducibleFraction::operator+() {
	return *this;
}
BigIrreducibleFraction BigIrreducibleFraction::operator-() {
	BigIrreducibleFraction one(-1, 1);
	return *this * one;
}
bool BigIrreducibleFraction::operator<(const BigIrreducibleFraction& num) {
	return (*this - num).numerator < 0;
}
bool BigIrreducibleFraction::operator<=(const BigIrreducibleFraction& num) {
	return (*this - num).numerator <= 0;
}
bool BigIrreducibleFraction::operator>(const BigIrreducibleFraction& num) {
	return (*this - num).numerator > 0;
}
bool BigIrreducibleFraction::operator>=(const BigIrreducibleFraction& num) {
	return (*this - num).numerator >= 0;
}
bool BigIrreducibleFraction::operator==(const BigIrreducibleFraction& num) {
	return (*this - num).numerator == 0;
}
bool BigIrreducibleFraction::operator!=(const BigIrreducibleFraction& num) {
	return (*this - num).numerator != 0;
}
BigIrreducibleFraction BigIrreducibleFraction::operator=(const std::string& irreducibleFraction){
	int forwardSlashPos = irreducibleFraction.find('/');
	if (forwardSlashPos == std::string::npos) {
		numerator = irreducibleFraction;
		denominator = 1;
	}
	else {
		numerator = irreducibleFraction.substr(0, forwardSlashPos);
		denominator = irreducibleFraction.substr(forwardSlashPos + 1, irreducibleFraction.length() - forwardSlashPos - 1);
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const BigIrreducibleFraction& num) {
	os << num.numerator << '/' << num.denominator;
	return os;
}
