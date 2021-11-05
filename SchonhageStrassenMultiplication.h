//
// Created by Anton on 05/11/2021.
//

#ifndef LAB2_SCHONHAGESTRASSENMULTIPLICATION_H
#define LAB2_SCHONHAGESTRASSENMULTIPLICATION_H

#include "LongValue.h"
#include "Multiplication.h"

class SchonhageStrassenMultiplication : public Multiplication
{
public:
	LongValue Multiply(LongValue a, LongValue b) override;
};


#endif //LAB2_SCHONHAGESTRASSENMULTIPLICATION_H
