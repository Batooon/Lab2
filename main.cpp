#include "LongValue.h"

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
