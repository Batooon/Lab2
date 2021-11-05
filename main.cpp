#include "LongValue.h"
#include "BasicMultiplication.h"
#include "PrimeTest.h"
#include "LehmerPrimeTest.h"
#include "SchonhageStrassenMultiplication.h"
#include "Multiplication.h"
#include "KaratsubaMultiplication.h"
#include "ToomCookMultiplication.h"

Multiplication *LongValue::multiplication = new SchonhageStrassenMultiplication();
Multiplication *LongValue::basicMultiplication = new BasicMultiplication();
PrimeTest *LongValue::primeTest = new LehmerPrimeTest();


int main()
{
	LongValue a, b, c;

	a = "78945623123486743";
	b = "7894561599517564564";
	c = a * b;
	cout << c << endl;
	return 0;
}
