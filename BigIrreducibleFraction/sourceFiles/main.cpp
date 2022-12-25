#include <BigIrreducibleFraction.h>

int main() {
	BigIrreducibleFraction num1; // num1 = 0 / 1
	num1 = "-2/7"; // num1 = 2 / 7
	BigIrreducibleFraction num2(4, 9); // num2 = 4 / 9
	BigIrreducibleFraction result = num1 + num2; // result = 46 / 63
	result = num1 - num2; // result = - 10 / 63
	result = num1 * num2; // result = 8 / 63
	result = num1 / num2; // result = 9 / 14
	num1 += num2; // num1 = 46 / 63;
	num1 -= num2; // num1 = 2 / 7
	num1 *= num2; // num1 = 8 / 63
	num1 /= num2; // num1 = 2 / 7
	result = num1++; // result = 2 / 7, num1 = 9 / 7
	result = ++num1; // result = 16 / 7, num1 = 16 / 7
	result = num1--; // result = 16 / 7, num1 = 9 / 7
	result = --num1; // result = 2 / 7, num1 = 2 / 7
	result = +num1; // result = 2 / 7
	result = -num1; // result = - 2 / 7
	std::cout << "num1: " << num1 << ", num2: " << num2 << ", result: " << result;
	return 0;
}
