//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_TOOMCOOKMULTIPLICATION_H
#define LAB2_TOOMCOOKMULTIPLICATION_H

#include "LongValue.h"
#include "Multiplication.h"

class ToomCookMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override;
};

#endif //LAB2_TOOMCOOKMULTIPLICATION_H
