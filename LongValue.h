//
// Created by Anton on 22/09/2021.
//

#ifndef LAB2_LONGVALUE_H
#define LAB2_LONGVALUE_H

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <cstdlib>
#include "Multiplication.h"
#include "PrimeTest.h"

using namespace std;

class Multiplication;

class LongValue
{
public:
	static Multiplication *multiplication;
	static Multiplication *basicMultiplication;
	static PrimeTest *primeTest;
	string digits;
	bool isPositive = true;

	explicit LongValue(string value = "0", bool isPositive = true);

	LongValue(const LongValue &other);

	bool operator!=(const LongValue &other);

	bool operator==(const LongValue &other);

	bool operator>=(const LongValue &other);

	bool operator<(int value);

	LongValue operator%(const LongValue &other);

	LongValue operator/(int other) const;

	LongValue operator*(int other);

	LongValue operator*(const LongValue &other);

	LongValue operator+(LongValue other);

	LongValue operator-(LongValue other);

	LongValue &operator=(const string &value);

	LongValue &operator=(int value);

	LongValue &operator=(const LongValue &other);

	LongValue operator<<(size_t num);

	static void AdjustNumbers(string &a, string &b);

private:
	void AddValue(int &remainder, string &newValue, int &value);

	void SumValue(int &remainder, string &newValue, char value, char otherValue);

	LongValue CalculateValues(string longerValue, const string &shorterValue, const bool positive = true);
};

#endif //LAB2_LONGVALUE_H
