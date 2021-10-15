//
// Created by Anton on 22/09/2021.
//

#ifndef LAB2_LONGVALUE_H
#define LAB2_LONGVALUE_H

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Multiplication;

class LongValue
{
public:
	static Multiplication *multiplication;
	string digits;

	LongValue(string value = "")
	{
		digits = value;
	}

	LongValue operator*(LongValue &other);

	LongValue operator+(LongValue other);

	LongValue operator=(string value);

	LongValue operator=(int value);

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
		newValue += value + '0';
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
		newValue += num + '0';
	}

	LongValue CalculateValues(string longerValue, string shorterValue)
	{
		int remainder = 0;
		string newValue = "";
		string otherValue = "";
		int digitsDifference = longerValue.length() - shorterValue.length();
		for(int i = 0; i < digitsDifference; i++)
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
		reverse(newValue.begin(), newValue.end());
		LongValue value(newValue);
		return value;
	}
};

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

LongValue LongValue::operator*(LongValue &other)
{
	return multiplication->Multiply(*this, other);
}

LongValue LongValue::operator=(string value)
{
	digits = value;
	return *this;
}

LongValue LongValue::operator=(int value)
{
	digits = to_string(value);
	return *this;
}

LongValue LongValue::operator+(LongValue other)
{
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
			newValue += remainder + '0';
		}
		reverse(newValue.begin(), newValue.end());
		LongValue value(newValue);
		return value;
	}
}

class KaratsubaMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		int adigits = a.digits.length();
		int bdigits = b.digits.length();
		int n = adigits % 2 == 0 ? adigits : adigits + 1;
		int m = bdigits % 2 == 0 ? bdigits : bdigits + 1;

		LongValue l("45");
		return l;
	}
};

class NaiveMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{

	}

	LongValue Multiply(LongValue a, int b)
	{

	}
};


#endif //LAB2_LONGVALUE_H
