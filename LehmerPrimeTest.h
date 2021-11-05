//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_LEHMERPRIMETEST_H
#define LAB2_LEHMERPRIMETEST_H

#include "LongValue.h"

class LehmerPrimeTest : public PrimeTest
{
public:
	bool IsPrime(LongValue value) override;
};

#endif //LAB2_LEHMERPRIMETEST_H
