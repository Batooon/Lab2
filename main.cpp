#include "LongValue.h"

Multiplication *LongValue::multiplication = new KaratsubaMultiplication();


int main()
{
	LongValue a, b, c;

	a = "4368948378334566345674";
	b = "5564590345634458436435";
	c = a * b;
	cout << c << endl;
	return 0;
}
