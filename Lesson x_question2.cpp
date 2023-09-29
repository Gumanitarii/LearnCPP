// Условие задания
/*
Напишите следующую программу: Создайте структуру, содержащую имя (first name) и оценку (grade) учащегося (по шкале от 0 до 100). 
Спросите пользователя, сколько учеников он хочет принять. Создайте std::vector для хранения всех учеников. Затем запросите у пользователя имя и оценку для каждого. 
После того как пользователь ввел все пары имен и оценок, отсортируйте список по оценкам (сначала самая высокая). Затем выведите все имена и оценки в отсортированном порядке.  
*/

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// тип, описывающий сущность "Студент"
struct Student
{
	std::string name{};	// имя студента
	int grade{};		// оценка студента по шкале от 0 до 100
};

// Для использования в std::sort - Сортировка контейнера сущностей по оценкам по убыванию
bool graterGrade(const Student& a, const Student& b)
{
	return (a.grade > b.grade);
}

int main()
{
	// Контейнер для хранения 5 сущностей "Студент"
	std::vector<Student> students(5);

	// Заполнение контейнера данными, полученными от пользователя
	for (auto& student : students)
	{
		std::cin >> student.name;
		std::cin >> student.grade;
	}

	std::sort(students.begin(), students.end(), graterGrade);

	// Вывод содержимого контейнера на консоль
	for (auto& student : students)
	{
		std::cout << student.name << " got a grade of " << student.grade << '\n';
	}

	return 0;
}

