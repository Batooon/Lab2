#include "LongValue.h"

Multiplication *LongValue::multiplication = new KaratsubaMultiplication();

int main()
{
	LongValue a, b, c;
	a = 281, b = 3679, c = 45;

	c = a + b;
	cout << a << " " << b << " " << c << endl;
	a = 3;
	b = 5;
	c = a * b;
	cout << c;
	return 0;
}
