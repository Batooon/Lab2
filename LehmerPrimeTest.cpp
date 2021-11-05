//
// Created by Anton on 05/11/2021.
//

#include "LehmerPrimeTest.h"

bool LehmerPrimeTest::IsPrime(LongValue value)
{
	LongValue one("1");
	for(size_t i = 0; i < 10; i++)
	{
		LongValue a = GetRandom(value);

		LongValue p = (value - one) / 2;

		LongValue pw = pow(a, p);
		LongValue md = pw % value;

		LongValue res = value - md;
		if(md != one && res != one)
			return false;
	}
	return true;

	/*LongValue zero("0");
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
	return S == zero;*/
}
