#pragma once
#include "deck.h"
#include "card.h"


class DeckFactory
{
public:
	static DeckFactory* instance()//实现单例模式
	{
		if (!deck_factory)
			deck_factory = new DeckFactory();

		return deck_factory;
	}

	Deck* create_deck(int cards_count=52);


private:
	DeckFactory() = default;

private:

	static DeckFactory* deck_factory;


};
