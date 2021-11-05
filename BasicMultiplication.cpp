//
// Created by Anton on 05/11/2021.
//

#include "BasicMultiplication.h"
#include "LongValue1.h"

LongValue BasicMultiplication::Multiply(LongValue a, LongValue b)
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
