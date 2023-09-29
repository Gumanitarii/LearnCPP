// Условие задания
/*
Хорошо, а теперь время испытаний! Давайте напишем упрощенную версию Блэкджека. Если вы еще не знакомы с блэкджеком, в статье в Википедии о блэкджеке (https://en.wikipedia.org/wiki/Blackjack) есть краткое изложение. 
Вот правила нашей версии блэкджека:
•	Дилер (dealer) получает одну карту (в реальной жизни дилер получает две, но одна лежит рубашкой вверх, поэтому на данном этапе это не имеет значения).
•	Игрок (player) получает две карты.
•	Игрок ходит первым.
•	Игрок может неоднократно «бить» (hit) или «стоять» (stand).
•	Если игрок «стоит», его ход окончен, и его счет рассчитывается на основе карт, которые ему были розданы.
•	Если игрок «бьет», он получает еще одну карту, и значение этой карты добавляется к его общему счету.
•	Туз обычно считается как 1 или 11 (в зависимости от того, что лучше для общего счета). Для простоты мы будем считать это число 11.
•	Если игрок набирает больше 21 балла, он немедленно вылетает и проигрывает.
•	Дилер ходит за игроком.
•	Дилер повторно тянет карты, пока не наберет 17 или более очков, после чего подсчет очков останавливается.
•	Если дилер набирает больше 21 балла, он вылетает, и игрок немедленно выигрывает.
•	В противном случае, если у игрока больше очков, чем у дилера, игрок выигрывает.
•	В противном случае игрок проигрывает (для простоты будем считать ничью победой дилера).
В нашей упрощенной версии блэкджека мы не собираемся отслеживать, какие именно карты были розданы игроку и дилеру. Мы будем отслеживать только сумму значений карт, которые были розданы игроку и дилеру. Это упрощает задачу.
Начните с кода, который вы написали в тесте №6. Создайте функцию с именем playBlackjack(). Эта функция должна:
•	Принимать в качестве параметра перетасованную колоду карт.
•	Реализовывать блэкджек, как описано выше (примечание: вы можете определить другие функции, которые помогут в этом).
•	Возвращает true, если игрок выиграл, и false, если он проиграл.
Также напишите функцию main() для одной игры в блэкджек.
*/

#include <iostream>
#include <string_view>
#include <array>
#include <algorithm> // std::shuffle
#include <chrono> // std::chrono::steady_clock::now().time_since_epoch().count()
#include <random> // std::mt19937

// Ранги в колоде карт
enum class CardRank
{
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	Jack,
	Queen,
	King,
	Ace,

	max_cardRanks
};

// Масти в колоде карт
enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,

	max_cardSuits
};

// Тип данного для сущности "Карта" (подразумевается игральная в колоде)
struct Card
{
	CardRank rank;
	CardSuit suit;
};

// Получить ранг Карты
std::string_view getCardRank(CardRank rank)
{
	switch(rank)
	{
		case CardRank::two: 	return "2";
		case CardRank::three: 	return "3";
		case CardRank::four:	return "4";
		case CardRank::five:	return "5";
		case CardRank::six:		return "6";
		case CardRank::seven:	return "7";
		case CardRank::eight:	return "8";
		case CardRank::nine:	return "9";
		case CardRank::ten:		return "T";
		case CardRank::Jack:	return "J";
		case CardRank::Queen: 	return "Q";
		case CardRank::King:	return "K";
		case CardRank::Ace:		return "A";
		default: 				return "Unknown card rank.";
	}
}

// Получить масть Карты
std::string_view getCardSuit(CardSuit suit)
{
	switch(suit)
	{
		case CardSuit::club:	return "C";
		case CardSuit::diamond:	return "D";
		case CardSuit::heart:	return "H";
		case CardSuit::spade:	return "S";
		default:				return "Unknown card suit.";
	}
}

// Вывод информации об отдельной Карте
void printCard(const Card& card)
{
	std::cout << getCardRank(card.rank) << getCardSuit(card.suit);
}

// Псевдоним для сущности "Колода карт"
using Deck = std::array<Card, 52>;

// Инициализация (создание и присвоение значений) Колоды карт из 52 Карт
Deck createDeck()
{
	Deck deck{};

	int cardIndex{ 0 };

	for (int i{ 0 }; i < static_cast<int>(CardSuit::max_cardSuits); ++i)
	{
		for (int j{ 0 }; j < static_cast<int>(CardRank::max_cardRanks); ++j)
		{
			deck[cardIndex].rank = static_cast<CardRank>(j);
			deck[cardIndex].suit = static_cast<CardSuit>(i);
			++cardIndex;
		}
	}

	return deck;
}

// Вывод информации о Колоде карт
void printDeck(const Deck& deck)
{
	for (const auto& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}

// Перетасовать Колоду карт (переместавить значения в массиве в случайном порядке)
void shuffleDeck(Deck& deck)
{
	static std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
	std::shuffle(deck.begin(), deck.end(), mt);
}

// Получить вес отдельной Карты
// Вес карт от 2 до 10 соответствует их рангу, от вальта до короля вес равен 10, вес туза равен 11
int getCardValue(const Card& card)
{
	switch(card.rank)
	{
		case CardRank::two: 	return 2; 
		case CardRank::three:	return 3;
		case CardRank::four:	return 4;
		case CardRank::five: 	return 5; 
		case CardRank::six:		return 6;
		case CardRank::seven:	return 7;
		case CardRank::eight: 	return 8; 
		case CardRank::nine:	return 9;
		case CardRank::ten:	
		case CardRank::Jack:
		case CardRank::Queen:
		case CardRank::King:	return 10;
		case CardRank::Ace:		return 11;
		default: 				return 0;	
	}
}

// Реализация действий хода игрока. Получить очки игрока
int getPlayerScore(int playerScore, int& index, const Deck& deck)
{
	char choice{ 'y' };	// Выбор игрока - взять из колоды очередную карту или закончить

	std::cout << "Your start score is " << playerScore << '\n';
	do
	{
		std::cout << "Do you want to get card?(y/n) ";
		std::cin >> choice;
		if (choice == 'n') break;

		playerScore += getCardValue(deck.at(index++));
		if (playerScore > 21)
		{
			std::cout << "Your final score is " << playerScore << '\n';
			return playerScore;
		} 

		std::cout << "Your current score is " << playerScore << '\n';		
	} while (choice == 'y');

	std::cout << "Your final score is " << playerScore << '\n';
	return playerScore;
}

// Реализация действий хода диллера. Получить очки диллера
int getDillerScore(int dillerScore, int& index, const Deck& deck)
{
	std::cout << "Diller's start score is " << dillerScore << '\n';
	do
	{
		dillerScore += getCardValue(deck.at(index++));
		if (dillerScore > 21)
		{
			std::cout << "Diller's final score is " << dillerScore << '\n';
			return dillerScore;
		}

		std::cout << "Diller's current score is " << dillerScore << '\n';		
	} while (dillerScore < 17);

	std::cout << "Diller's final score is " << dillerScore << '\n';
	return dillerScore;
}

// Реализация логики действий для одной игры в BlackJack
bool playBlackjack(const Deck& deck)
{ 
	int index{ 0 }; // Текущий номер карты по мере хода игры. Начинаем с первой карты в колоде
	
	// Дать одну карту Диллеру
	Card dillerCard1{ deck.at(index++) };

	// Дать две карты Игроку
	Card playerCard1{ deck.at(index++) };
	Card playerCard2{ deck.at(index++) };
	int playerScore{ getCardValue(playerCard1) + getCardValue(playerCard2) }; // предварительный результат игрока
	if ( playerScore > 21) // Закончить игру, если перебор
		return false;

	// Ход игрока
	playerScore = getPlayerScore(playerScore, index, deck);
	if (playerScore > 21) return false; // Закончить игру, если перебор

	// Ход диллера
	int dillerScore{ getCardValue(dillerCard1) };	// предварительный результат диллера
	dillerScore = getDillerScore(dillerScore, index, deck);
	if (dillerScore > 21) return true; // Закончить игру, если перебор
	
	// Сравнение очков игрока и деллера
	if (playerScore >= dillerScore)
		return true;
	else
		return false;
}

int main()
{
	// Создать упорядоченную колоду карт
	Deck deck{ createDeck() };
	printDeck(deck);

	// Перетасовать колоду карт
	shuffleDeck(deck);
	printDeck(deck);

	// Запустить одну игру и вывести результат
	if (playBlackjack(deck))
		std::cout << "The Player win!\n";
	else
		std::cout << "The Player lost.\n";

	return 0;
}

