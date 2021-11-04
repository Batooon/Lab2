#include "LongValue.h"

Multiplication *LongValue::multiplication = new ToomCookMultiplication();
Multiplication *LongValue::basicMultiplication = new BasicMultiplication();


int main()
{
	LongValue a, b, c;

	a = "1234567890123456789012425725346346246432";
	b = "987654321987654321098435643745375463426432";
	c = a * b;
	cout << c << endl;
	return 0;
}
