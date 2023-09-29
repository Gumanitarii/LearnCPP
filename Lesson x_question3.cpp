// Условие задания
/*
Напишите собственную функцию для обмена значениями двух целочисленных переменных. 
Напишите функцию main(), чтобы проверить ее.
*/

#include <iostream>

// Поменять значения параметров местами
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int a { 5 };
	int b { 10 };

	std::cout << "Values before swaping: a = " << a << ", b = " << b << '\n';

	swap(a, b);

	std::cout << "Values after the swaping: a = " << a << ", b = " << b << '\n';

	return 0;
}

