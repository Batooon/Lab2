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

using namespace std;

class Multiplication;

class PrimeTest;

void RemoveLeadingZeros(string &value);

class LongValue
{
public:
	static Multiplication *multiplication;
	static Multiplication *basicMultiplication;
	static PrimeTest *primeTest;
	string digits;
	bool isPositive = true;

	explicit LongValue(string value = "0", bool isPositive = true) : digits(move(value)), isPositive(isPositive)
	{
	}

	LongValue(const LongValue &other)
	{
		digits = other.digits;
		isPositive = other.isPositive;
	}

	bool operator!=(const LongValue &other);

	bool operator==(LongValue other);

	bool operator>=(LongValue other);

	bool operator<(int value);

	LongValue operator%(LongValue other);

	LongValue operator/(int other);

	LongValue operator*(int other);

	LongValue operator*(const LongValue &other);

	LongValue operator+(LongValue other);

	LongValue operator-(LongValue other);

	LongValue &operator=(const string &value);

	LongValue &operator=(int value);

	LongValue &operator=(LongValue other);

	LongValue operator<<(size_t num);

	static void AdjustNumbers(string &a, string &b)
	{
		if(a.length() == b.length())
			return;
		auto longestValue = max(a.length(), b.length());
		auto shortestValue = min(a.length(), b.length());
		auto digitsDifference = longestValue - shortestValue;
		string zeros;
		if(digitsDifference > 0)
		{
			for(size_t i = 0; i < digitsDifference; i++)
			{
				zeros += "0";
			}
		}
		string newValue = zeros;
		if(a.length() < b.length())
		{
			newValue += a;
			a = newValue;
		}
		else
		{
			newValue += b;
			b = newValue;
		}
	}

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

	LongValue CalculateValues(string longerValue, const string &shorterValue, const bool positive = true)
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
		LongValue value(newValue, positive);
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
	l.digits = "";
	char c;
	while(is.get(c))
	{
		if(c == '\0' || c == '\n')
			break;
		if(c == '-')
		{
			l.isPositive = false;
			continue;
		}
		l.digits += c;
	}
	return is;
}

ostream &operator<<(ostream &os, LongValue &l)
{
	if(!l.isPositive)
		os << '-';
	os << l.digits;
	return os;
}

LongValue pow(LongValue x, LongValue power)
{
	LongValue temp;
	LongValue zero("0");
	LongValue two("2");

	if(power == zero)
		return LongValue("1");
	temp = pow(x, power / 2);
	if(power % two == zero)
		return temp * temp;
	else
	{
		LongValue temptest = temp * temp;
		LongValue temp1 = x * temptest;
		return temp1;
	}
}

class PrimeTest
{
public:
	virtual bool IsPrime(LongValue value) = 0;
};

class LehmerPrimeTest : public PrimeTest
{
public:
	bool IsPrime(LongValue value) override
	{
		LongValue zero("0");
		LongValue one("1");
		LongValue two("2");
		LongValue S("4");
		LongValue k("1");
		LongValue pn1;
		LongValue M;
		LongValue p2("2");
		LongValue test;
		pn1 = value - one;
		test = pow(p2, value);
		M = test - k;

		while(k != pn1)
		{
			LongValue test1 = ((S * S) - two);
			S = test1 % M;
			k = k + one;
		}
		return S == zero;
	}
};

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
	if(value[0] == '-')
	{
		isPositive = false;
		digits = value.substr(1);
	}
	else
	{
		digits = value;
	}
	return *this;
}

LongValue &LongValue::operator=(const int value)
{
	if(value < 0)
		isPositive = false;
	digits = to_string(abs(value));
	return *this;
}

LongValue LongValue::operator+(LongValue other)
{
	if(other.digits == "0")
		return *this;
	if(this->digits == "0")
		return other;
	if(!other.isPositive && this->isPositive)
	{
		LongValue newOther = other;
		newOther.isPositive = true;
		return *this - newOther;
	}
	if(!this->isPositive && other.isPositive)
	{
		LongValue newThis = *this;
		newThis.isPositive = true;
		return other - newThis;
	}
	bool positive = true;
	if(!this->isPositive && !other.isPositive)
		positive = false;
	if(digits.length() == 1 && other.digits.length() == 1)
	{
		string newValue = to_string((digits[0] - '0') + (other.digits[0] - '0'));
		LongValue result(newValue, positive);
		return result;
	}
	if(digits.length() > other.digits.length())
	{
		return CalculateValues(digits, other.digits, positive);
	}
	else if(other.digits.length() > digits.length())
	{
		return CalculateValues(other.digits, digits, positive);
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
		LongValue value(newValue, positive);
		return value;
	}
}

LongValue LongValue::operator-(LongValue other)
{
	LongValue *res;
	if(isPositive && !other.isPositive)
	{
		LongValue newOther = other;
		newOther.isPositive = true;
		return *this + newOther;
	}

	if(!isPositive && other.isPositive)
	{
		LongValue newThis = *this;
		newThis.isPositive = true;
		res = new LongValue(newThis + other);
		res->isPositive = false;
		return *res;
	}

	if(!isPositive && !other.isPositive)
	{
		LongValue newOther = other;
		newOther.isPositive = true;
		LongValue newThis = *this;
		newThis.isPositive = true;
		res = new LongValue(newOther - newThis);
		return *res;
	}

	if(other.digits.length() > this->digits.length())
	{
		res = new LongValue(other - *this);
		res->isPositive = false;
		return *res;
	}
	if(other.digits.length() == 1 && this->digits.length() == 1)
	{
		int a = this->digits[0] - '0';
		int b = other.digits[0] - '0';
		string result;
		if(a >= b)
		{
			result = to_string(a - b);
		}
		else
		{
			result = to_string(b - a);
		}
		res = new LongValue(result, a >= b);
		return *res;
	}
	if(other.digits.length() == this->digits.length())
	{
		for(size_t i = 0; i < this->digits.length(); i++)
		{
			if(this->digits[i] < other.digits[i])
			{
				res = new LongValue(other - *this);
				res->isPositive = false;
				return *res;
			}
			else if(this->digits[i] > other.digits[i])
				break;
		}
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
	res = new LongValue(result);
	return *res;
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

LongValue LongValue::operator*(const int other)
{
	return LongValue::basicMultiplication->Multiply(*this, LongValue(to_string(other)));
}

LongValue DivideValue(const LongValue longvalue, const int other, bool addZero = false)
{
	if(longvalue.digits.length() == 1 && longvalue.digits[0] == '0')
		return longvalue;
	string newValue;
	int nDigits = 1;
	int firstDigits = longvalue.digits[0] - '0';
	int remainder, value;

	if(longvalue.digits.length() == 1)
	{
		value = (longvalue.digits[0] - '0') / other;
		newValue = to_string(value);
		return LongValue(newValue, longvalue.isPositive);
	}

	if(firstDigits < other && firstDigits != 0)
	{
		nDigits = 2;
		string convertDigits = longvalue.digits.substr(0, nDigits);
		firstDigits = stoi(convertDigits);
		if(addZero)
		{
			newValue += "0";
		}
	}

	value = firstDigits / other;
	newValue += to_string(value);
	remainder = firstDigits - other * value;

	if(longvalue.digits.length() == nDigits)
		return LongValue(newValue, longvalue.isPositive);

	string nextNumber = longvalue.digits.substr(nDigits, 1);
	addZero = stoi(nextNumber) < other && remainder == 0 && longvalue.digits.length() - nDigits > 1;

	string divideValue = remainder == 0 ? longvalue.digits.substr(nDigits) : to_string(remainder) +
	                                                                         longvalue.digits.substr(nDigits);

	LongValue recValue(divideValue, longvalue.isPositive);
	LongValue subRes = DivideValue(recValue, other, addZero);
	newValue += subRes.digits;

	LongValue res(newValue, longvalue.isPositive);
	return res;
}

LongValue LongValue::operator/(const int other)
{
	return DivideValue(*this, other);
}

LongValue LongValue::operator%(LongValue other)
{
	LongValue a = *this;
	RemoveLeadingZeros(a);

	if((a - other) < 0)
		return *this;

	while(a >= other)
	{
		a = a - other;
	}
	return a;
}

bool LongValue::operator<(int value)
{
	//Так як іншого порівняння окрім нуля ніде не виникає, можна полегшити собі життя і обробити лише цей випадок
	if(digits.length() == 1 && digits[0] - '0' == 0)
		return false;
	return !isPositive;
}

bool LongValue::operator>=(LongValue other)
{
	if(digits.length() > other.digits.length())
		return true;
	if(digits.length() < other.digits.length())
		return false;
	LongValue res = *this - other;
	return res.isPositive;
}

bool LongValue::operator==(LongValue other)
{
	LongValue res = *this - other;
	bool temp1 = res.digits.length() == 1;
	bool temp2 = res.digits[0] == '0';
	bool result = temp1 && temp2;
	return result;
}

bool LongValue::operator!=(const LongValue &other)
{
	bool result = !(*this == other);
	return result;
}

LongValue &LongValue::operator=(LongValue other)
{
	digits = other.digits;
	isPositive = other.isPositive;
	return *this;
}

class BasicMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		auto resValue = new LongValue("0");
		if(!a.isPositive && b.isPositive || a.isPositive && !b.isPositive)
			resValue->isPositive = false;
		if(a.digits.length() > 1 || b.digits.length() > 1)
		{
			string res;
			int remainder = 0;
			int bDigits = stoi(b.digits);
			for(int i = a.digits.length() - 1; i >= 0; i--)
			{
				int value = (a.digits[i] - '0') * bDigits + remainder;
				if(value >= 10)
				{
					if(i == 0)
					{
						string temp = to_string(value);
						reverse(temp.begin(), temp.end());
						res += temp;
						break;
					}
					remainder = value / 10;
					value %= 10;
					res += to_string(value);
				}
				else
				{
					res += to_string(value);
					remainder = 0;
				}
			}
			reverse(res.begin(), res.end());
			resValue->digits = res;
			RemoveLeadingZeros(*resValue);
			return *resValue;
		}
		resValue->digits = to_string((a.digits[0] - '0') * (b.digits[0] - '0'));
		return *resValue;
	}
};

class ToomCookMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		bool positive = true;
		if(!a.isPositive && b.isPositive || a.isPositive && !b.isPositive)
			positive = false;
		if(a.digits.length() >= 1 && b.digits.length() == 1)
			return LongValue::basicMultiplication->Multiply(a, b);
		if(a.digits.length() == 1 && b.digits.length() >= 1)
			return LongValue::basicMultiplication->Multiply(b, a);
		int k = 3;
		LongValue a0, a1, a2, b0, b1, b2;
		LongValue::AdjustNumbers(a.digits, b.digits);
		int remainder = a.digits.length() % k;
		if(remainder != 0)
		{
			a.digits.insert(0, k - remainder, '0');
			b.digits.insert(0, k - remainder, '0');
		}
		int divideDigits = int(a.digits.length() / k);
		for(size_t i = 0; i < divideDigits; i++)
		{
			size_t index1 = i + divideDigits;
			size_t index2 = i + 2 * divideDigits;
			a0.digits += a.digits[index2];
			a1.digits += a.digits[index1];
			a2.digits += a.digits[i];
			b0.digits += b.digits[index2];
			b1.digits += b.digits[index1];
			b2.digits += b.digits[i];
		}
		RemoveLeadingZeros(a0);
		RemoveLeadingZeros(a1);
		RemoveLeadingZeros(a2);
		RemoveLeadingZeros(b0);
		RemoveLeadingZeros(b1);
		RemoveLeadingZeros(b2);
		LongValue p, p0, p1, pn1, pn2, pinf, q, q0, q1, qn1, qn2, qinf;
		p = a0 + a2;
		p0 = a0;
		p1 = p + a1;
		pn1 = p - a1;
		pn2 = (pn1 + a2) * 2 - a0;
		pinf = a2;
		q = b0 + b2;
		q0 = b0;
		q1 = q + b1;
		qn1 = q - b1;
		qn2 = (qn1 + b2) * 2 - b0;
		qinf = b2;

		LongValue r0, r1, rn1, rn2, rinf;
		r0 = p0 * q0;
		r1 = p1 * q1;
		rn1 = pn1 * qn1;
		rn2 = pn2 * qn2;
		rinf = pinf * qinf;

		LongValue r, r4, r3, r11, r2;
		r = r0;
		r4 = rinf;
		r3 = (rn2 - r1) / 3;
		r11 = (r1 - rn1) / 2;
		r2 = rn1 - r0;
		LongValue test = r2 - r3;
		LongValue test2 = test / 2;
		r3 = test2 + rinf * 2;
		r2 = r2 + r11 - r4;
		r11 = r11 - r3;
		LongValue res = r + (r11 << divideDigits) + (r2 << (divideDigits * 2)) + (r3 << (divideDigits * 3)) +
		                (r4 << (divideDigits * 4));
		res.isPositive = positive;
		return res;
	}
};

class KaratsubaMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		size_t aDigits = a.digits.length();
		size_t bDigits = b.digits.length();
		if(aDigits == 1 && bDigits == 1)
		{
			return LongValue::basicMultiplication->Multiply(a, b);
		}
		auto longestValue = max(aDigits, bDigits);
		int n = longestValue % 2 == 0 ? longestValue / 2 : floor(longestValue / 2.0);
		LongValue a1, a0, b1, b0;
		string a1Value = "", b1Value = "", a0Value = "", b0Value = "";
		LongValue::AdjustNumbers(a.digits, b.digits);
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

class SchonhageStrassenMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override
	{
		LongValue::AdjustNumbers(a.digits, b.digits);
		int aDigits = a.digits.length();
		int bDigits = b.digits.length();
		if(aDigits == 1 && bDigits == 1)
			return LongValue::basicMultiplication->Multiply(a, b);

		bool positive = a.isPositive && b.isPositive || !a.isPositive && !b.isPositive;
		LongValue ten("10");

		int length = aDigits + bDigits - 1;

		auto *linearConvolution = new LongValue[length];

		LongValue temp = a;

		for(size_t i = 0; i < aDigits; i++, b.digits.erase(b.digits.length() - 1))
		{
			a = temp;
			for(size_t j = 0; j < bDigits; j++, a.digits.erase(a.digits.length() - 1))
			{
				int av, bv;
				av = a.digits[a.digits.length() - 1] - '0';
				bv = b.digits[b.digits.length() - 1] - '0';
				LongValue aValue, bValue;
				aValue = av;
				bValue = bv;
				linearConvolution[i + j] = linearConvolution[i + j] + (aValue * bValue);
			}
		}

		LongValue remainder;
		LongValue result;
		int digit = 0;
		for(int i = 0; i < length; i++)
		{
			linearConvolution[i] = linearConvolution[i] + remainder;
			result = result + ((linearConvolution[i] % ten) << digit++);
			LongValue copy = linearConvolution[i];
			if(copy.digits.length() > 1)
				remainder = copy.digits.erase(copy.digits.length() - 1);
			else
				remainder = 0;
		}
		result = result + (remainder << digit);
		result.isPositive = positive;
		delete[] linearConvolution;
		return result;
	}
};


#endif //LAB2_LONGVALUE_H
