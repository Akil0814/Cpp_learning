#include "card.h"

Card::Suit Card::getSuit() const { return suit_; };
Card::Rank Card::getRank() const { return rank_; };

Card& Card::operator++()
{
    if (rank_ == Rank::King)
    {
        rank_ = Rank::Ace;
        suit_ = static_cast<Suit>((static_cast<int>(suit_) + 1) % 4);
    }
    else
        rank_ = static_cast<Rank>(static_cast<int>(rank_) + 1);

    return *this;
}

Card Card::operator++(int)
{
    Card tmp = *this;
    ++(*this);
    return tmp;
}

bool Card::operator==(const Card& other) const
{
    return suit_ == other.suit_ && rank_ == other.rank_;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    switch (card.getRank())
    {
        case Card::Rank::Ace:   os << "A";  break;
        case Card::Rank::King:  os << "K";  break;
        case Card::Rank::Queen: os << "Q";  break;
        case Card::Rank::Jack:  os << "J";  break;
        case Card::Rank::Ten:   os << "10"; break;
        case Card::Rank::Nine:  os << "9";  break;
        case Card::Rank::Eight: os << "8";  break;
        case Card::Rank::Seven: os << "7";  break;
        case Card::Rank::Six:   os << "6";  break;
        case Card::Rank::Five:  os << "5";  break;
        case Card::Rank::Four:  os << "4";  break;
        case Card::Rank::Three: os << "3";  break;
        case Card::Rank::Two:   os << "2";  break;
    }

    switch (card.getSuit())
    {
        case Card::Suit::Spades:   os << " Spades"; break;
        case Card::Suit::Hearts:   os << " Hearts"; break;
        case Card::Suit::Diamonds: os << " Diamonds"; break;
        case Card::Suit::Clubs:    os << " Clubs"; break;
    }

    return os;
}



