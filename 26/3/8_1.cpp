//quadratic hashing
#include <iostream>

class my_hash_table_quadratic
{
private:
    enum class state
    {
        empty_key,
        deleted_key,
        has_key
    };

    struct slot
    {
        std::pair<int, std::string> kv;
        state s = state::empty_key;
    };

    static constexpr int table_size = 29;
    slot table[table_size];

    int h(int key) const
    {
        return key % table_size;
    }

public:
    bool insert(int key, const std::string& value)
    {
        for (int i = 0; i < table_size; ++i)
        {
            int index = (h(key) + i * i) % table_size;

            if (table[index].s == state::empty_key ||
                table[index].s == state::deleted_key)
            {
                table[index].kv.first = key;
                table[index].kv.second = value;
                table[index].s = state::has_key;
                return true;
            }
        }

        return false;
    }

    bool remove(int key)
    {
        for (int i = 0; i < table_size; ++i)
        {
            int index = (h(key) + i * i) % table_size;

            if (table[index].s == state::has_key &&
                table[index].kv.first == key)
            {
                table[index].s = state::deleted_key;
                return true;
            }

            if (table[index].s == state::empty_key)
            {
                return false;
            }
        }

        return false;
    }

    void print() const
    {

        for (int i = 0; i < table_size; ++i)
        {
            std::cout << "[" << i << "] ";

            if (table[i].s == state::has_key)
            {
                std::cout << table[i].kv.first << " -> " << table[i].kv.second;
            }
            else if (table[i].s == state::deleted_key)
            {
                std::cout << "<deleted>";
            }
            else
            {
                std::cout << "<empty>";
            }

            std::cout << '\n';
        }
    }
};

int main()
{
    my_hash_table_quadratic table;

    table.insert(18, "Laguna Niguel");
    table.insert(41, "Mission Viejo");
    table.insert(22, "San Clemente");
    table.insert(44, "Irvine");

    table.remove(41);

    table.insert(58, "Lake Forest");
    table.insert(32, "San Diego");
    table.insert(49, "Anaheim");

    table.remove(58);

    table.insert(31, "Los Angeles");
    table.insert(17, "Orange");
    table.insert(72, "Palms Springs");
    table.insert(41, "Riverside");

    table.remove(72);

    table.insert(19, "Brea");
    table.insert(60, "Santa Ana");
    table.insert(35, "Tustin");
    table.insert(103, "Oceanside");
    table.insert(11, "La Jolla");
    table.insert(18, "Del Mar");
    table.insert(22, "Aliso Viejo");
    table.insert(49, "Laguna Beach");

    table.remove(41);

    table.insert(42, "Vista");
    table.insert(49, "San Diego");
    table.insert(99, "San Juan");
    table.insert(29, "Dana Point");
    table.insert(88, "El Segundo");
    table.insert(41, "San Clemente");
    table.insert(62, "Laguna Hills");

    table.print();

    return 0;
}
