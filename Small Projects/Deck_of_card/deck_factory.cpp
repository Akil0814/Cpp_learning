#include "deck_factory.h"

DeckFactory* DeckFactory::deck_factory = nullptr;

Deck* DeckFactory::create_deck(int cards_count);
{
    Deck* new_deck = new Deck();
    
    for(int i = 0; i < cards_count; ++i)
    {
    }

	return new_deck;
}
