#include <iostream>

class Card
{
public:

    enum class Suit { Clubs,Diamonds,Hearts,Spades };
    enum class Rank { Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

public:
    Card(Suit suit, Rank rank) : suit_(suit), rank_(rank){}
    ~Card() = default;

    Suit getSuit() const ;
    Rank getRank() const;

private:
    Suit suit_;
    Rank rank_;

};

