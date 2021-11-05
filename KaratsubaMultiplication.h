//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_KARATSUBAMULTIPLICATION_H
#define LAB2_KARATSUBAMULTIPLICATION_H

#include "LongValue.h"
#include "Multiplication.h"

class KaratsubaMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override;
};

#endif //LAB2_KARATSUBAMULTIPLICATION_H
