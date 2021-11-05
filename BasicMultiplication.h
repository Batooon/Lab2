//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_BASICMULTIPLICATION_H
#define LAB2_BASICMULTIPLICATION_H

#include "LongValue.h"
#include "Multiplication.h"

class BasicMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override;
};

#endif //LAB2_BASICMULTIPLICATION_H
