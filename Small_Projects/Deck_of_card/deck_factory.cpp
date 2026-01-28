#include "deck_factory.h"

DeckFactory* DeckFactory::deck_factory = nullptr;

std::unique_ptr<Deck> DeckFactory::create_deck(int cards_count)
{
    std::unique_ptr<Deck> new_deck = std::make_unique<Deck>();

    for(int i = 0; i < cards_count; ++i)
    {
        Card::Suit suit = static_cast<Card::Suit>(i / 13);
        Card::Rank rank = static_cast<Card::Rank>(i % 13);

        auto new_card = std::make_unique<Card>(suit,rank);
        new_deck->add_card(std::move(new_card));
    }

	return new_deck;
}
