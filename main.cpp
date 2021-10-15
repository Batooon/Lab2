#include "LongValue.h"

Multiplication *LongValue::multiplication = new KaratsubaMultiplication();

int main()
{
	LongValue a, b, c;
	a = 281, b = 3679, c = 45;

	c = a + b;
	cout << a << " " << b << " " << c;
	//a = c * b;
	//a.print();
	return 0;
}
