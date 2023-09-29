// Условие задания
/*
Напишите функцию для печати строки в стиле C посимвольно. Используйте указатель, чтобы пройти через каждый символ строки и вывести этот символ. 
Остановитесь, когда достигнете нулевого терминатора. Напишите функцию main, которая проверяет функцию со строковым литералом «Hello, world!».
*/

#include <iostream>

// Посимвольный вывод строки в стиле С типа const char*
void printCStyleString(const char* ptrToStr)
{
	while (*ptrToStr != '\0')
	{
		std::cout << *ptrToStr << '\n';
		++ptrToStr;
	}
}

int main()
{
	const char* helloWorld{ "Hello, world!" };

	printCStyleString(helloWorld);

	return 0;
}

