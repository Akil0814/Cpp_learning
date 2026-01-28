#include "deck.h"

std::ostream& operator<<(std::ostream& os, const Card& card);

void Deck::add_card(std::unique_ptr<Card> new_card)
{
    card_list.push_back(std::move(new_card));
}

void Deck::show_deck()
{
    int i = 0;
    for (auto &iter : card_list)
    {
        i++;
        if(iter)
            std::cout << *iter << " ";
        if (i >= 13)
        {
            std::cout << std::endl;
            i = 0;
        }

    }
    std::cout<<std::endl;
}

void Deck::perfect_shuffle()
{
    const std::size_t num_of_card = card_list.size();

    if (num_of_card == 0)return;

    const std::size_t right_count = num_of_card / 2;
    const std::size_t left_count = (num_of_card + 1) / 2;


    std::vector<std::unique_ptr<Card>> tmp;
    tmp.reserve(num_of_card);

    for (std::size_t i = 0; i < right_count; ++i)
    {
        tmp.push_back(std::move(card_list[i]));              // left
        tmp.push_back(std::move(card_list[i + left_count])); // right
    }
    if (left_count > right_count)
    {
        tmp.push_back(std::move(card_list[left_count - 1]));
    }

    card_list = std::move(tmp);

}

bool Deck::operator==(const Deck& other) const
{
    if (card_list.size() != other.card_list.size())
        return false;

    for (size_t i = 0; i < card_list.size(); ++i)
    {
        if (!card_list[i] || !other.card_list[i])
            return false;
        if (*card_list[i] != *other.card_list[i])
            return false;
    }
    return true;
}

bool Deck::operator!=(const Deck& other) const
{
    return !(*this == other);
}
