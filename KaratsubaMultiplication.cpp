//
// Created by Anton on 05/11/2021.
//

#include "KaratsubaMultiplication.h"
#include "LongValue.h"

LongValue KaratsubaMultiplication::Multiply(LongValue a, LongValue b)
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
