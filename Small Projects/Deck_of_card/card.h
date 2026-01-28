#include <iostream>

enum class Suit { Clubs,Diamonds,Hearts,Spades };
enum class Rank { Ace=1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card
{
public:
    Card(Suit suit, Rank rank) : suit_(suit), rank_(rank){}
    ~Card() = default;

    Suit getSuit() const { return suit_; }
    Rank getRank() const { return rank_; }



private:
    Suit suit_;
    Rank rank_;

};

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    switch (card.getRank())
    {
        case Rank::Ace:   os << "A";  break;
        case Rank::King:  os << "K";  break;
        case Rank::Queen: os << "Q";  break;
        case Rank::Jack:  os << "J";  break;
        case Rank::Ten:   os << "10"; break;
        case Rank::Nine:  os << "9";  break;
        case Rank::Eight: os << "8";  break;
        case Rank::Seven: os << "7";  break;
        case Rank::Six:   os << "6";  break;
        case Rank::Five:  os << "5";  break;
        case Rank::Four:  os << "4";  break;
        case Rank::Three: os << "3";  break;
        case Rank::Two:   os << "2";  break;
    }

    switch (card.getSuit())
    {
        case Suit::Spades:   os << " Spades"; break;
        case Suit::Hearts:   os << " Hearts"; break;
        case Suit::Diamonds: os << " Diamonds"; break;
        case Suit::Clubs:    os << " Clubs"; break;
    }

    return os;
}




