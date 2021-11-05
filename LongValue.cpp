//
// Created by Anton on 05/11/2021.
//

#include "LongValue.h"

LongValue::LongValue(string value, bool isPositive) : digits(move(value)), isPositive(isPositive)
{
}

LongValue::LongValue(const LongValue &other)
{
	digits = other.digits;
	isPositive = other.isPositive;
}

LongValue GetRandom(LongValue &border)
{
	string newValue;
	bool generatingValue = true;
	int a;
	while(generatingValue)
	{
		newValue = "";
		for(size_t i = 0; i < border.digits.length(); i++)
		{
			if(i == 0)
			{
				a = rand() % (border.digits[i] - '0');
			}
			else
			{
				do
				{
					a = rand() % 10;
				}
				while(a == 0);
			}
			newValue += to_string(a);
		}
		reverse(newValue.begin(), newValue.end());
		LongValue potentialRes(newValue);
		if(border > potentialRes)
		{
			generatingValue = false;
		}
	}

	while(newValue.length() > 1 && (newValue[newValue.length() - 1] - '0') == 0)
		newValue.erase(newValue.length() - 1);

	if(newValue[0] - '0' < 2 && newValue.length() == 1)
	{
		newValue[0] = '2';
		return LongValue(newValue);
	}

	return LongValue(newValue);
}

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
		LongValue temp1 = x * temp * temp;
		return temp1;
	}
}

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
		string newValue;
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
	string zeros;
	for(int i = 0; i < digitsDifference; i++)
	{
		zeros += "0";
	}
	other.digits = zeros + other.digits;
	string result;
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
	return basicMultiplication->Multiply(*this, LongValue(to_string(other)));
}

LongValue DivideValue(const LongValue &longvalue, const int other, bool addZero)
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

LongValue LongValue::operator/(const int other) const
{
	return DivideValue(*this, other);
}

LongValue LongValue::operator%(const LongValue &other)
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

bool LongValue::operator>(const LongValue &other)
{
	if(digits[digits.length() - 1] - '0' < 0 && other.digits[other.digits.length() - 1] - '0' >= 0)
		return false;
	if(digits[digits.length() - 1] >= 0 && other.digits[other.digits.length() - 1] - '0' < 0)
		return true;
	if(digits.length() > other.digits.length())
		return true;
	if(digits.length() < other.digits.length())
		return false;
	LongValue res = *this - other;
	if(res != LongValue("0"))
		return res.isPositive;
	else
		return false;
	/*int i=digits.length()-1;
	bool greater=false;
	while(i>=0&&!greater)
	{
		if(digits[i]-'0'>other.digits[i]-'0')
			greater=true;
		if(digits[i]-'0'<other.digits[i]-'0')
			i=-1;
		i-=1;
	}
	return greater;*/
}

bool LongValue::operator>=(const LongValue &other)
{
	if(digits.length() > other.digits.length())
		return true;
	if(digits.length() < other.digits.length())
		return false;
	LongValue res = *this - other;
	return res.isPositive;
}

bool LongValue::operator==(const LongValue &other)
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

LongValue &LongValue::operator=(const LongValue &other)
{
	digits = other.digits;
	isPositive = other.isPositive;
	return *this;
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

LongValue LongValue::CalculateValues(string longerValue, const string &shorterValue, const bool positive)
{
	int remainder = 0;
	string newValue;
	string otherValue;
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

void LongValue::SumValue(int &remainder, string &newValue, char value, char otherValue)
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

void LongValue::AddValue(int &remainder, string &newValue, int &value)
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

void LongValue::AdjustNumbers(string &a, string &b)
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
