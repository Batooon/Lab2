//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_MULTIPLICATION_H
#define LAB2_MULTIPLICATION_H

#include "LongValue.h"

class LongValue;

class Multiplication
{
public:
	virtual LongValue Multiply(LongValue a, LongValue b) = 0;
};


#endif //LAB2_MULTIPLICATION_H
