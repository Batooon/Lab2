//
// Created by Anton on 05/11/2021.
//

#include "SchonhageStrassenMultiplication.h"

LongValue SchonhageStrassenMultiplication::Multiply(LongValue a, LongValue b)
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
