//use for compil: g++ -std=c++17 -g *.cpp -o main.exe -pthread
//to get out put ./main.exe >> out.txt
/*
Deck_of_card/
├──card.h
├──deck.h
├──deck_factory.h
├──card.cpp
├── deck.cpp
├── deck_factory.cpp
├── main.cpp
├── out.txt
└── README.md
*/

#include <iostream>
#include <vector>
#include <memory>

#include "deck.h"
#include "deck_factory.h"
#include "card.h"



int main()
{
    std::cout << "Creating Deck..." << std::endl;

    std::unique_ptr<Deck> prototype_deck = DeckFactory::instance()->create_deck();
    std::unique_ptr<Deck> shuffle_deck = DeckFactory::instance()->create_deck();

    std::cout << "Showing Deck..." << std::endl;
    shuffle_deck->show_deck();

    int count = 0;
    std::cout << "Start Shuffling Deck..." << std::endl;

    do
    {
        count++;
        shuffle_deck->perfect_shuffle();
    } while ((*prototype_deck != *shuffle_deck));

    std::cout << "Finish Shuffling, it take:"<<count<<" to return the deck to its original" << std::endl;


    return 0;
}
