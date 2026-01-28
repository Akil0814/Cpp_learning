#include <iostream>
#include <vector>
#include "card.h"
#include "deck.h"

int main()
{
    Card card(Suit::Hearts, Rank::Ace);
    std::cout << card << std::endl;


    return 0;
}
