//
// Created by Anton on 05/11/2021.
//

#include "ToomCookMultiplication.h"
#include "LongValue.h"

LongValue ToomCookMultiplication::Multiply(LongValue a, LongValue b)
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
