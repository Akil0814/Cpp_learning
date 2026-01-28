#pragma once
#include <vector>
#include <memory>

#include "card.h"

class Deck
{
public:
    Deck()=default;
    ~Deck()=default;

    bool operator==(const Deck& other) const;
    bool operator!=(const Deck& other) const;

    void add_card(std::unique_ptr<Card> new_card);

    void show_deck();

    void perfect_shuffle();

private:
    std::vector<std::unique_ptr<Card>> card_list;
};
