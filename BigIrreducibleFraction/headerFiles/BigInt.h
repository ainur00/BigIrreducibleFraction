#pragma once

#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
	BigInt();
	// конструктор для создания BigInt с помощью строки
	BigInt(const std::string& inputNum);
	// конструктор для создания BigInt с помощью параметров BigInt
	BigInt(const std::vector<int>& inputReversedNumberAbsoluteValue, const bool& inputIsNegative);
	// конструктор для создания BigInt с помощью целого числа
	BigInt(const long long& inputNum);
	// операторы
	BigInt operator+(const BigInt& summand);
	BigInt operator-(const BigInt& subtrahend);
	BigInt operator*(const BigInt& multiplier);
	BigInt operator/(const BigInt& divisor);
	BigInt operator%(const BigInt& divisor);
	BigInt operator+=(const BigInt& summand);
	BigInt operator-=(const BigInt& subtrahend);
	BigInt operator*=(const BigInt& multiplier);
	BigInt operator/=(const BigInt& divisor);
	BigInt operator%=(const BigInt& divisor);
	BigInt& operator++();
	BigInt& operator--();
	BigInt operator++(int);
	BigInt operator--(int);
	BigInt operator+();
	BigInt operator-();
	bool operator==(const BigInt& num);
	bool operator!=(const BigInt& num);
	bool operator>(const BigInt& num);
	bool operator>=(const BigInt& num);
	bool operator<(const BigInt& num);
	bool operator<=(const BigInt& num);
	friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
	BigInt operator=(const std::string& inputNum);
	BigInt operator=(const long long& inputNum);
private:
	// то, из чего состоит BigInt
	// число в обратном порядке в виде вектора, элементы вектора - цифры
	std::vector<int> reversedNumberAbsoluteValue;
	// является ли число отрицательным
	bool isNegative;
	// работа с BigInt как с BigInt для рассмотрения случаев
	// слагаемлое + слагаемлое = сумма
	static BigInt GetSum(const BigInt& summand1, const BigInt& summand2);
	// уменьшаемое - вычитаемое = разность
	static BigInt GetDifference(const BigInt& minuend, const BigInt& subtrahend);
	// множитель * множитель = произведение
	static BigInt GetProduct(const BigInt& multiplier1, const BigInt& multiplier2);
	// делимое / делитель = частное
	static BigInt GetQuotient(const BigInt& dividend, const BigInt& divisor);
	// сравнение модулей (1 -> больше; 0 -> равно; -1 -> меньше)
	static int GetAbsoluteCompareResult(const BigInt& bigInt1, const BigInt& bigInt2);
	// сравнение (1 -> больше; 0 -> равно; -1 -> меньше)
	static int GetCompareResult(const BigInt& bigInt1, const BigInt& bigInt2);
	// работа с BigInt как с их векторами в частных случаях
	// сравнение модулей чисел как векторов (1 -> больше; 0 -> равно; -1 -> меньше)
	static int GetVectorsAbsoluteCompareResult(std::vector<int> num1, std::vector<int> num2);
	// возвращает сумму двух векторов как чисел в виде вектора
	static std::vector<int> GetVectorsSum(std::vector<int> summand1, std::vector<int> summand2);
	// возвращает разницу двух векторов как чисел в виде вектора (уменьшаемое должно быть больше вычитаемого)
	static std::vector<int> GetVectorsDifference(std::vector<int> minuend, std::vector<int> subtrahend);
	// возвращает произведение веткоров как чисел в виде вектора
	static std::vector<int> GetVectorsProduct(std::vector<int> multiplier1, std::vector<int> multiplier2);
	// возвращает частное деления веткоров как чисел в виде вектора
	static std::vector<int> GetVectorQuotient(std::vector<int> dividend, std::vector<int> divisor);
	// возвращает число с убранными незначащими нулями как вектор
	static std::vector<int> GetVectorWithoutLeadingZeros(std::vector<int> num);
};

BigInt::BigInt() {
	reversedNumberAbsoluteValue.push_back(0);
	isNegative = false;
}
BigInt::BigInt(const std::string& inputNum) {
	if (inputNum.length() == 0) {
		reversedNumberAbsoluteValue.push_back(0);
		isNegative = false;
	}
	else {
		// перевод строки в BigInt
		isNegative = ((inputNum[0] == '-') ? true : false);
		for (int i = inputNum.size() - 1; i >= (isNegative ? 1 : 0); --i)
			reversedNumberAbsoluteValue.push_back(inputNum[i] - '0');
		// удаление незначащих нулей
		while ((reversedNumberAbsoluteValue.size() != 1) && (reversedNumberAbsoluteValue[reversedNumberAbsoluteValue.size() - 1] == 0))
			reversedNumberAbsoluteValue.pop_back();
		// проверка числа на равенство 0 для того, чтобы если чего убрать его отрицательность
		if ((reversedNumberAbsoluteValue.size() == 1) && (reversedNumberAbsoluteValue[0] == 0))
			isNegative = false;
	}
}
BigInt::BigInt(const std::vector<int>& inputReversedNumberAbsoluteValue, const bool& inputIsNegative) {
	// копирование параметров
	isNegative = inputIsNegative;
	reversedNumberAbsoluteValue = inputReversedNumberAbsoluteValue;
	// удаление незначащих нулей
	while ((reversedNumberAbsoluteValue.size() != 1) && (reversedNumberAbsoluteValue[reversedNumberAbsoluteValue.size() - 1] == 0))
		reversedNumberAbsoluteValue.pop_back();
	// проверка числа на равенство 0 для того, чтобы если чего убрать его отрицательность
	if ((reversedNumberAbsoluteValue.size() == 1) && (reversedNumberAbsoluteValue[0] == 0))
		isNegative = false;
}
BigInt::BigInt(const long long& inputNum) {
	std::string inputNumStr = std::to_string(inputNum);
	if (inputNumStr.length() == 0) {
		reversedNumberAbsoluteValue.push_back(0);
		isNegative = false;
	}
	else {
		// перевод строки в BigInt
		isNegative = ((inputNumStr[0] == '-') ? true : false);
		for (int i = inputNumStr.size() - 1; i >= (isNegative ? 1 : 0); --i)
			reversedNumberAbsoluteValue.push_back(inputNumStr[i] - '0');
		// удаление незначащих нулей
		while ((reversedNumberAbsoluteValue.size() != 1) && (reversedNumberAbsoluteValue[reversedNumberAbsoluteValue.size() - 1] == 0))
			reversedNumberAbsoluteValue.pop_back();
		// проверка числа на равенство 0 для того, чтобы если чего убрать его отрицательность
		if ((reversedNumberAbsoluteValue.size() == 1) && (reversedNumberAbsoluteValue[0] == 0))
			isNegative = false;
	}
}

BigInt BigInt::GetSum(const BigInt& summand1, const BigInt& summand2) {
	// проверка разных случаев и выв=зов нужных приватных функций
	if ((!summand1.isNegative) && (!summand2.isNegative) || (summand1.isNegative) && (summand2.isNegative))
		return BigInt(GetVectorsSum(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue), summand1.isNegative);
	if (summand1.isNegative)
		if (BigInt::GetVectorsAbsoluteCompareResult(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue) == 1)
			return BigInt(GetVectorsDifference(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue), true);
		else if (BigInt::GetVectorsAbsoluteCompareResult(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue) == -1)
			return BigInt(GetVectorsDifference(summand2.reversedNumberAbsoluteValue, summand1.reversedNumberAbsoluteValue), false);
		else
			return BigInt("0");
	if (BigInt::GetVectorsAbsoluteCompareResult(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue) == 1)
		return BigInt(GetVectorsDifference(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue), false);
	else if (BigInt::GetVectorsAbsoluteCompareResult(summand1.reversedNumberAbsoluteValue, summand2.reversedNumberAbsoluteValue) == -1)
		return BigInt(GetVectorsDifference(summand2.reversedNumberAbsoluteValue, summand1.reversedNumberAbsoluteValue), true);
	else
		return BigInt("0");
}
BigInt BigInt::GetDifference(const BigInt& minuend, const BigInt& subtrahend) {
	// проверка разных случаев и выв=зов нужных приватных функций
	if (!subtrahend.isNegative) {
		if (minuend.isNegative)
			return BigInt(GetVectorsSum(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue), true);
		else {
			if (GetVectorsAbsoluteCompareResult(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue) == 1)
				return BigInt(GetVectorWithoutLeadingZeros(GetVectorsDifference(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue)), false);
			if (GetVectorsAbsoluteCompareResult(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue) == 0)
				return BigInt("0");
			return BigInt(GetVectorWithoutLeadingZeros(GetVectorsDifference(subtrahend.reversedNumberAbsoluteValue, minuend.reversedNumberAbsoluteValue)), true);
		}
	}
	else {
		if (!minuend.isNegative)
			return BigInt(GetVectorsSum(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue), false);
		else {
			if (GetVectorsAbsoluteCompareResult(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue) == -1)
				return BigInt(GetVectorWithoutLeadingZeros(GetVectorsDifference(subtrahend.reversedNumberAbsoluteValue, minuend.reversedNumberAbsoluteValue)), false);
			if (GetVectorsAbsoluteCompareResult(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue) == 0)
				return BigInt("0");
			return BigInt(GetVectorWithoutLeadingZeros(GetVectorsDifference(minuend.reversedNumberAbsoluteValue, subtrahend.reversedNumberAbsoluteValue)), true);
		}
	}
}
BigInt BigInt::GetProduct(const BigInt& multiplier1, const BigInt& multiplier2) {
	// проверка разных случаев и выв=зов нужных приватных функций
	if ((!multiplier1.isNegative) && (!multiplier2.isNegative) || (multiplier1.isNegative) && (multiplier2.isNegative))
		return BigInt(GetVectorWithoutLeadingZeros(GetVectorsProduct(multiplier1.reversedNumberAbsoluteValue, multiplier2.reversedNumberAbsoluteValue)), false);
	return BigInt(GetVectorWithoutLeadingZeros(GetVectorsProduct(multiplier1.reversedNumberAbsoluteValue, multiplier2.reversedNumberAbsoluteValue)), true);
}
BigInt BigInt::GetQuotient(const BigInt& dividend, const BigInt& divisor) {
	// проверка разных случаев и выв=зов нужных приватных функций
	if (dividend.reversedNumberAbsoluteValue.size() < divisor.reversedNumberAbsoluteValue.size())
		return BigInt("0");
	if ((!dividend.isNegative) && (!divisor.isNegative) || (dividend.isNegative) && (divisor.isNegative))
		return BigInt(GetVectorWithoutLeadingZeros(GetVectorQuotient(dividend.reversedNumberAbsoluteValue, divisor.reversedNumberAbsoluteValue)), false);
	return BigInt(GetVectorWithoutLeadingZeros(GetVectorQuotient(dividend.reversedNumberAbsoluteValue, divisor.reversedNumberAbsoluteValue)), true);
}

BigInt BigInt::operator+(const BigInt& summand) {
	return GetSum(*this, summand);
}
BigInt BigInt::operator-(const BigInt& subtrahend) {
	return GetDifference(*this, subtrahend);
}
BigInt BigInt::operator*(const BigInt& multiplier) {
	return GetProduct(*this, multiplier);
}
BigInt BigInt::operator/(const BigInt& divisor) {
	return GetQuotient(*this, divisor);
}
BigInt BigInt::operator%(const BigInt& divisor) {
	return *this - ((*this / divisor) * divisor);
}
BigInt BigInt::operator+=(const BigInt& summand) {
	*this = *this + summand;
	return *this;
}
BigInt BigInt::operator-=(const BigInt& subtrahend) {
	*this = *this - subtrahend;
	return *this;
}
BigInt BigInt::operator*=(const BigInt& multiplier) {
	*this = *this * multiplier;
	return *this;
}
BigInt BigInt::operator/=(const BigInt& divisor) {
	*this = *this / divisor;
	return *this;
}
BigInt BigInt::operator%=(const BigInt& divisor) {
	*this = *this % divisor;
	return *this;
}
BigInt& BigInt::operator++() {
	return *this = *this + 1;
}
BigInt& BigInt::operator--() {
	return *this = *this - 1;
}
BigInt BigInt::operator++(int) {
	BigInt temp = *this;
	++* this;
	return temp;
}
BigInt BigInt::operator--(int) {
	BigInt temp = *this;
	--* this;
	return temp;
}
BigInt BigInt::operator+() {
	return *this;
}
BigInt BigInt::operator-() {
	return *this * (-1);
}
bool BigInt::operator==(const BigInt& num) {
	return GetCompareResult(*this, num) == 0;
}
bool BigInt::operator!=(const BigInt& num) {
	return GetCompareResult(*this, num) != 0;
}
bool BigInt::operator>(const BigInt& num) {
	return GetCompareResult(*this, num) == 1;
}
bool BigInt::operator>=(const BigInt& num) {
	return GetCompareResult(*this, num) >= 0;
}
bool BigInt::operator<(const BigInt& num) {
	return GetCompareResult(*this, num) == -1;
}
bool BigInt::operator<=(const BigInt& num) {
	return GetCompareResult(*this, num) <= 0;
}
BigInt BigInt::operator=(const std::string& inputNum) {
	// очистка предыдущего числа для перезаписи
	reversedNumberAbsoluteValue.clear();
	if (inputNum.length() == 0) {
		reversedNumberAbsoluteValue.push_back(0);
		isNegative = false;
	}
	else {
		// перевод строки в BigInt
		isNegative = ((inputNum[0] == '-') ? true : false);
		for (int i = inputNum.size() - 1; i >= (isNegative ? 1 : 0); --i)
			reversedNumberAbsoluteValue.push_back(inputNum[i] - '0');
		// удаление незначащих нулей
		while ((reversedNumberAbsoluteValue.size() != 1) && (reversedNumberAbsoluteValue[reversedNumberAbsoluteValue.size() - 1] == 0))
			reversedNumberAbsoluteValue.pop_back();
		// проверка числа на равенство 0 для того, чтобы если чего убрать его отрицательность
		if ((reversedNumberAbsoluteValue.size() == 1) && (reversedNumberAbsoluteValue[0] == 0))
			isNegative = false;
	}
	return *this;
}
BigInt BigInt::operator=(const long long& inputNum) {
	std::string inputNumStr = std::to_string(inputNum);
	// очистка предыдущего числа для перезаписи
	reversedNumberAbsoluteValue.clear();
	if (inputNumStr.length() == 0) {
		reversedNumberAbsoluteValue.push_back(0);
		isNegative = false;
	}
	else {
		// перевод строки в BigInt
		isNegative = ((inputNumStr[0] == '-') ? true : false);
		for (int i = inputNumStr.size() - 1; i >= (isNegative ? 1 : 0); --i)
			reversedNumberAbsoluteValue.push_back(inputNumStr[i] - '0');
		// удаление незначащих нулей
		while ((reversedNumberAbsoluteValue.size() != 1) && (reversedNumberAbsoluteValue[reversedNumberAbsoluteValue.size() - 1] == 0))
			reversedNumberAbsoluteValue.pop_back();
		// проверка числа на равенство 0 для того, чтобы если чего убрать его отрицательность
		if ((reversedNumberAbsoluteValue.size() == 1) && (reversedNumberAbsoluteValue[0] == 0))
			isNegative = false;
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const BigInt& num) {
	if (num.isNegative)
		os << "-";
	for (int i = num.reversedNumberAbsoluteValue.size() - 1; i >= 0; --i)
		os << num.reversedNumberAbsoluteValue[i];
	return os;
}

int BigInt::GetAbsoluteCompareResult(const BigInt& bigInt1, const BigInt& bigInt2) {
	return GetVectorsAbsoluteCompareResult(bigInt1.reversedNumberAbsoluteValue, bigInt2.reversedNumberAbsoluteValue);
}
int BigInt::GetCompareResult(const BigInt& bigInt1, const BigInt& bigInt2) {
	// проверка разных случаев и выв=зов нужных приватных функций
	if ((!bigInt1.isNegative) && (!bigInt2.isNegative))
		return GetVectorsAbsoluteCompareResult(bigInt1.reversedNumberAbsoluteValue, bigInt2.reversedNumberAbsoluteValue);
	if ((bigInt1.isNegative) && (bigInt2.isNegative))
		return GetVectorsAbsoluteCompareResult(bigInt1.reversedNumberAbsoluteValue, bigInt2.reversedNumberAbsoluteValue) * (-1);
	if ((!bigInt1.isNegative) && (bigInt2.isNegative))
		return 1;
	else
		return -1;
}

int BigInt::GetVectorsAbsoluteCompareResult(std::vector<int> num1, std::vector<int> num2) {
	// убираем незначащие нули для корректности выполнения
	num1 = GetVectorWithoutLeadingZeros(num1);
	num2 = GetVectorWithoutLeadingZeros(num2);
	// сравниваем размеры чисел, а после, если размеры чисел равны, сравниваем цифры чисел с одинаковым разрядом
	if (num1.size() > num2.size())
		return 1;
	else if (num1.size() < num2.size())
		return -1;
	else {
		for (int i = num1.size() - 1; i >= 0; --i)
			if (num1[i] > num2[i])
				return 1;
			else if (num1[i] < num2[i])
				return -1;
		return 0;
	}
}
std::vector<int> BigInt::GetVectorsSum(std::vector<int> summand1, std::vector<int> summand2) {
	// убираем незначащие нули для корректности выполнения
	summand1 = GetVectorWithoutLeadingZeros(summand1);
	summand2 = GetVectorWithoutLeadingZeros(summand2);
	// vectorsSum - результат, isWasOverNine - хранение переполнения
	std::vector<int> vectorsSum;
	bool isWasOverNine = false;
	int i = 0;
	// пока i меньше размера числа, размер которого меньше, скоадываем цифры
	for (; i < (int)((summand1.size() < summand2.size()) ? summand1.size() : summand2.size()); ++i) {
		int iDigitsSum = summand1[i] + summand2[i] + (isWasOverNine ? 1 : 0);
		isWasOverNine = (iDigitsSum >= 10);
		vectorsSum.push_back(iDigitsSum % 10);
	}
	// если размеры чисел были равные, то при наличии переполнения isWasOverNine, добавляем еще 1 разряд
	if (summand1.size() == summand2.size()) {
		if (isWasOverNine)
			vectorsSum.push_back(1);
	}
	// если одно из чисел больше, то копируем оставшиеся разряды в результат сложения
	else if (summand1.size() > summand2.size()) {
		if (isWasOverNine)
			vectorsSum.push_back(summand1[i++] + 1);
		for (; i < (int)summand1.size(); ++i)
			vectorsSum.push_back(summand1[i]);
	}
	else {
		if (isWasOverNine)
			vectorsSum.push_back(summand2[i++] + 1);
		for (; i < (int)summand2.size(); ++i)
			vectorsSum.push_back(summand2[i]);
	}
	return GetVectorWithoutLeadingZeros(vectorsSum);
}
std::vector<int> BigInt::GetVectorsDifference(std::vector<int> minuend, std::vector<int> subtrahend) {
	// убираем незначащие нули для корректности выполнения
	minuend = GetVectorWithoutLeadingZeros(minuend);
	subtrahend = GetVectorWithoutLeadingZeros(subtrahend);
	// vectorsDifference - результат вычитания
	std::vector<int> vectorsDifference;
	// вычитаем поразрядно, при и забираем единицу у более старшего разряда при необходимости
	int i = 0;
	for (; i < (int)subtrahend.size(); ++i) {
		int iDigitsDifference = minuend[i] - subtrahend[i];
		if (iDigitsDifference < 0) {
			iDigitsDifference += 10;
			minuend[i + 1]--;
		}
		vectorsDifference.push_back(iDigitsDifference);
	}
	// копируем оставшиеся разряды
	for (; i < (int)minuend.size(); ++i)
		vectorsDifference.push_back(minuend[i]);
	return GetVectorWithoutLeadingZeros(vectorsDifference);
}
std::vector<int> BigInt::GetVectorsProduct(std::vector<int> multiplier1, std::vector<int> multiplier2) {
	// убираем незначащие нули для корректности выполнения
	multiplier1 = GetVectorWithoutLeadingZeros(multiplier1);
	multiplier2 = GetVectorWithoutLeadingZeros(multiplier2);
	// vectorsProduct - результат произведения, размер произведения - сумма размеров множителей + 1
	std::vector<int> vectorsProduct(multiplier1.size() + multiplier2.size() + 1);
	// в ячейку результата i + j складываем произведение разрядов
	for (int i = 0; i < (int)multiplier1.size(); ++i)
		for (int j = 0; j < (int)multiplier2.size(); ++j)
			vectorsProduct[i + j] += multiplier1[i] * multiplier2[j];
	// идем от начала результат к концу и перекидываем переполненные части текущих разрядов в более старшие разряды
	for (int i = 0; i < (int)vectorsProduct.size(); ++i) {
		if (vectorsProduct[i] > 9)
			vectorsProduct[i + 1] += vectorsProduct[i] / 10;
		vectorsProduct[i] %= 10;
	}
	return GetVectorWithoutLeadingZeros(vectorsProduct);
}
std::vector<int> BigInt::GetVectorQuotient(std::vector<int> dividend, std::vector<int> divisor) {
	// убираем незначащие нули для корректности выполнения
	dividend = GetVectorWithoutLeadingZeros(dividend);
	divisor = GetVectorWithoutLeadingZeros(divisor);
	// carry - текущий остаток, изначально равный 0, base - текущая система счисления, равная 10, созданый для удобства проведения операций над ними
	std::vector<int> carry;
	carry.push_back(0);
	std::vector<int> base;
	base.push_back(0);
	base.push_back(1);
	// dividendI - хранение текущего разряда делимого
	std::vector<int> dividendI;
	for (int i = dividend.size() - 1; i >= 0; --i) {
		// очищаем dividendI и кладем туда текущий разряд
		dividendI.clear();
		dividendI.push_back(dividend[i]);
		// задаем текущее делимое число как как сумму текущего разряда и остатка, помноженного на 10
		std::vector<int> current = GetVectorsSum(dividendI, GetVectorsProduct(carry, base));
		// divResult - результат целочисленного деления, ищется постепенным его увеличением на 1 и сравнением
		std::vector<int> divResult;
		divResult.push_back(0);
		while (GetVectorsAbsoluteCompareResult(GetVectorsProduct(divResult, divisor), current) <= 0)
			divResult[0]++;
		divResult[0]--;
		// кладем в текущий разряд делимого результат целочисленного деления
		dividend[i] = divResult[0];
		// обновлвем остаток разницей текущего делимого и произведения делителя на результат целочисленного деления
		carry.clear();
		carry = GetVectorsDifference(current, GetVectorsProduct(divisor, divResult));
	}
	return GetVectorWithoutLeadingZeros(dividend);
}
std::vector<int> BigInt::GetVectorWithoutLeadingZeros(std::vector<int> num) {
	while ((num.size() != 1) && (num[num.size() - 1] == 0))
		num.pop_back();
	return num;
}