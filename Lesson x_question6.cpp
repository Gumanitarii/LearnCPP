// Условие задания
/*
Давайте представим, что мы пишем карточную игру. 
а) Колода карт состоит из 52 уникальных карт (cards) (13 рангов (ranks) карт 4 мастей (suits)). 
  Создайте перечисления для рангов карт (2, 3, 4, 5, 6, 7, 8, 9, 10, Валет (Jack), Дама (Queen), Король (King), Туз (Ace)) и мастей (трефы (clubs), бубны (diamonds), червы (hearts), пики (spades)). 
  Эти перечислители не будут использоваться для индексации массивов. 
б) Каждая карта будет представлена структурой Card, содержащей ранг и масть. Создайте структуру.
в) Создайте функцию printCard(), которая принимает константную ссылку на карту в качестве параметра и печатает ранг и масть карты в виде двухбуквенного кода (например, пиковый валет (jack of spades) будет напечатан как JS). 
г) В колоде карт 52 карты. Создайте массив (используя std::array), представляющий колоду карт, и инициализируйте его каждой картой. Сделайте это в функции с именем createDeck и вызовите createDeck из main. createDeck должен вернуть колоду карт обратно в main.
д) Напишите функцию с именем printDeck(), которая принимает колоду в качестве константного ссылочного параметра и выводит карты из колоды. Используйте цикл for на основе диапазона. 
  Когда вы сможете распечатать Deck с колодой, созданной вами в предыдущей задаче, выходные данные должны быть:
  2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AC 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AD 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AH 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS AS
  Если вы использовали другие символы, это тоже нормально.
е) Напишите функцию shuffleDeck для перетасовки колоды карт с помощью std::shuffle. Обновите свою основную функцию, чтобы перетасовать колоду и распечатать перетасованную колоду. 
ж) Напишите функцию с именем getCardValue(), которая возвращает значение карты. (например, 2 имеет вес 2, десятка, валет, дама или король имеют вес 10. Предположим, что туз имеет вес 11).
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

int main()
{
	Deck deck{ createDeck() };
	printDeck(deck);

	shuffleDeck(deck);
	printDeck(deck);

	return 0;
}

