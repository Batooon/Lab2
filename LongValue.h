//
// Created by Anton on 22/09/2021.
//

#ifndef LAB2_LONGVALUE_H
#define LAB2_LONGVALUE_H

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Multiplication;

void RemoveLeadingZeros(string &value);

class LongValue
{
public:
	static Multiplication *multiplication;
	string digits;

	explicit LongValue(string value = "")
	{
		digits = move(value);
	}

	LongValue(const LongValue &other)
	{
		digits = other.digits;
	}

	LongValue operator*(LongValue const &other);

	LongValue operator+(LongValue other);

	LongValue operator-(LongValue other);

	LongValue &operator=(const string &value);

	LongValue &operator=(const int value);

	LongValue operator<<(size_t num);

private:
	void AddValue(int &remainder, string &newValue, int &value)
	{
		if(remainder != 0)
		{
			value += remainder;
			remainder = 0;
		}
		if(value >= 10)
		{
			value %= 10;
			remainder += 1;
		}
		newValue += to_string(value);
	}

	void SumValue(int &remainder, string &newValue, char value, char otherValue)
	{
		int num = otherValue - '0' + value - '0';
		if(remainder != 0)
		{
			num += remainder;
			remainder = 0;
		}
		if(num >= 10)
		{
			num %= 10;
			remainder += 1;
		}
		newValue += to_string(num);
	}

	LongValue CalculateValues(string longerValue, const string &shorterValue)
	{
		int remainder = 0;
		string newValue = "";
		string otherValue = "";
		size_t digitsDifference = longerValue.length() - shorterValue.length();
		for(size_t i = 0; i < digitsDifference; i++)
		{
			otherValue += "0";
		}
		otherValue += shorterValue;
		for(int i = longerValue.length() - 1; i >= digitsDifference; i--)
		{
			SumValue(remainder, newValue, longerValue[i], otherValue[i]);
		}
		for(int i = digitsDifference - 1; i >= 0; i--)
		{
			int value = longerValue[i] - '0';
			AddValue(remainder, newValue, value);
		}
		if(remainder != 0)
			newValue += to_string(remainder);
		reverse(newValue.begin(), newValue.end());
		RemoveLeadingZeros(newValue);
		LongValue value(newValue);
		return value;
	}
};

void RemoveLeadingZeros(string &value)
{
	if(value[0] != '0')
		return;
	if(value.length() == 1)
		return;
	value.erase(value.begin());
	RemoveLeadingZeros(value);
}

void RemoveLeadingZeros(LongValue &value)
{
	if(value.digits.length() == 1)
		return;
	if(value.digits[0] != '0')
		return;
	value.digits.erase(value.digits.begin());
	RemoveLeadingZeros(value);
}

istream &operator>>(istream &is, LongValue &l)
{
	is >> l.digits;
	return is;
}

ostream &operator<<(ostream &os, LongValue &l)
{
	os << l.digits;
	return os;
}

class Multiplication
{
public:
	virtual LongValue Multiply(LongValue a, LongValue b) = 0;
};

LongValue LongValue::operator*(LongValue const &other)
{
	return multiplication->Multiply(*this, other);
}

LongValue &LongValue::operator=(const string &value)
{
	digits = value;
	return *this;
}

LongValue &LongValue::operator=(const int value)
{
	digits = to_string(value);
	return *this;
}

LongValue LongValue::operator+(LongValue other)
{
	if(other.digits == "0")
		return *this;
	if(this->digits == "0")
		return other;
	if(digits.length() == 1 && other.digits.length() == 1)
	{
		string newValue = to_string((digits[0] - '0') + (other.digits[0] - '0'));
		LongValue result(newValue);
		return result;
	}
	if(digits.length() > other.digits.length())
	{
		return CalculateValues(digits, other.digits);
	}
	else if(other.digits.length() > digits.length())
	{
		return CalculateValues(other.digits, digits);
	}
	else
	{
		int remainder = 0;
		string newValue = "";
		for(int i = digits.length() - 1; i >= 0; i--)
		{
			SumValue(remainder, newValue, digits[i], other.digits[i]);
		}
		if(remainder != 0)
		{
			newValue += to_string(remainder);
		}
		reverse(newValue.begin(), newValue.end());
		RemoveLeadingZeros(newValue);
		LongValue value(newValue);
		return value;
	}
}

LongValue LongValue::operator-(LongValue other)
{
	if(other.digits.length() > this->digits.length())
		return static_cast<LongValue>(nullptr);
	if(other.digits.length() == 1 && this->digits.length() == 1)
	{
		int a = this->digits[0] - '0';
		int b = other.digits[0] - '0';
		if(a >= b)
		{
			string result = to_string(a - b);
			LongValue res(result);
			return res;
		}
		else
			return static_cast<LongValue>(nullptr);
	}
	size_t digitsDifference = this->digits.length() - other.digits.length();
	string zeros = "";
	for(int i = 0; i < digitsDifference; i++)
	{
		zeros += "0";
	}
	other.digits = zeros + other.digits;
	string result = "";
	int value, remainder = this->digits[other.digits.length() - 1] - '0';
	for(int i = other.digits.length() - 1; i >= 0; i--)
	{
		if(remainder < other.digits[i] - '0')
		{
			value = remainder + 10;
			remainder = this->digits[i - 1] - 1 - '0';
			result += to_string(value - (other.digits[i] - '0'));
		}
		else
		{
			result += to_string(remainder - (other.digits[i] - '0'));
			remainder = this->digits[i - 1] - '0';
		}
	}
	reverse(result.begin(), result.end());
	RemoveLeadingZeros(result);
	LongValue res(result);
	return res;
}

LongValue LongValue::operator<<(size_t num)
{
	LongValue copy = *this;
	for(size_t i = 0; i < num; i++)
	{
		copy.digits += "0";
	}
	return copy;
}

class KaratsubaMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		size_t aDigits = a.digits.length();
		size_t bDigits = b.digits.length();
		if(aDigits == 1 && bDigits == 1)
		{
			LongValue res;
			res = (a.digits[0] - '0') * (b.digits[0] - '0');
			return res;
		}
		int longestValue = max(aDigits, bDigits);
		int shortestValue = min(aDigits, bDigits);
		int n = longestValue % 2 == 0 ? longestValue / 2 : floor(longestValue / 2.0);
		LongValue a1, a0, b1, b0;
		string a1Value = "", b1Value = "", a0Value = "", b0Value = "";
		int digitsDifference = longestValue - shortestValue;
		if(digitsDifference != 0)
		{
			string zeros = "";
			if(aDigits > bDigits)
			{
				for(size_t i = 0; i < digitsDifference; i++)
				{
					zeros += "0";
				}
				b.digits = zeros + b.digits;
			}
			else
			{
				for(size_t i = 0; i < digitsDifference; i++)
				{
					zeros += "0";
				}
				a.digits = zeros + a.digits;
			}
		}
		size_t border = longestValue % 2 == 0 ? n : n + 1;
		for(size_t i = 0; i < border; i++)
		{
			a1Value += a.digits[i];
			b1Value += b.digits[i];
		}
		for(size_t i = border; i < longestValue; i++)
		{
			a0Value += a.digits[i];
			b0Value += b.digits[i];
		}

		a1 = a1Value;
		b1 = b1Value;
		a0 = a0Value;
		b0 = b0Value;

		LongValue ab1 = a1 * b1;
		RemoveLeadingZeros(ab1);
		LongValue ab0 = a0 * b0;
		RemoveLeadingZeros(ab0);
		LongValue ab1Moved = ab1 << (2 * n);
		RemoveLeadingZeros(ab1Moved);
		LongValue ab = (a1 + a0) * (b1 + b0);
		RemoveLeadingZeros(ab);
		LongValue ab01 = ab - ab1 - ab0;
		RemoveLeadingZeros(ab01);
		LongValue ab001 = ab01 << n;
		RemoveLeadingZeros(ab001);

		LongValue res;
		res = ab1Moved + ab001 + ab0;
		RemoveLeadingZeros(res);

		return res;
	}
};


#endif //LAB2_LONGVALUE_H
