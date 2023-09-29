// Условие задания 
/*
Представьте, что вы пишете игру, в которой игрок может держать в руках три типа предметов: зелья здоровья (health potions), факелы (torches) и стрелы (arrows). 
Создайте перечисление для идентификации различных типов предметов и std::array для хранения количества каждого предмета, который несет игрок (перечислители используются как индексы массива). 
Игрок должен начать с 2 зельями здоровья, 5 факелами и 10 стрелами.  
Напишите функцию countTotalItems(), которая возвращает общее количество предметов, имеющихся у игрока. Пусть ваша функция main() выведет выходные данные countTotalItems(), а также количество факелов. 
*/

#include <array>
#include <iostream>
#include <numeric>

namespace Items
{
	enum Items
	{
		healthPotion,
		torch,
		arrow,

		maxItems
	};
}

int countTotalItems(const std::array<int, Items::maxItems>& items)
{
	return std::reduce(items.begin(), items.end());
}

int main()
{
	std::array<int, Items::maxItems> startItems{ 2, 5, 10 };

	for (int item : startItems)
		std::cout << item << ' ';
	std::cout << '\n';

	std::cout << "The player has a total of " << countTotalItems(startItems) << " items.\n";
	std::cout << "The player has " << startItems[Items::torch] << " torches.\n";

	return 0;
}


