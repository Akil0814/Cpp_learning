#include <iostream>
#include <vector>
#include "card.cpp"
#include "deck.h"

int main()
{
    Card card(Card::Suit::Hearts, Card::Rank::Ace);
    std::cout << card << std::endl;


    return 0;
}
