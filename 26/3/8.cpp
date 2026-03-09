#include<iostream>

class my_hash_table
{
private:
    enum class State
    {
        empty_key,
        deleted_key,
        has_key
    };

    struct slot
    {
        std::pair<int, std::string> kv;
        State  s = State::empty_key;
    };

public:

    bool insert(int key, const std::string& value)
    {
        int index=0;
        for(int i=0;i<31;i++)
        {
            index=(h(key)+i*h2(key))%31;
            if(table[index].s==State::empty_key||table[index].s==State::deleted_key)
            {
                table[index].kv.first=key;
                table[index].kv.second=value;
                table[index].s=State::has_key;
                return true;
            }
        }

        return false;
    }

    bool insert(int key, const std::string& value, bool quadratic_hashing)
    {
        int index=0;
        for(int i=0;i<31;i++)
        {
            index=(h(key)+i*h2(key))%31;
            if(table[index].s==State::empty_key||table[index].s==State::deleted_key)
            {
                table[index].kv.first=key;
                table[index].kv.second=value;
                table[index].s=State::has_key;
                return true;
            }
        }

        return false;
    }

    bool remove(int key)
    {
        int index=0;
        for(int i=0;i<31;i++)
        {
            index=(h(key)+i*h2(key))%31;
            if(table[index].s==State::has_key && table[index].kv.first==key)
            {
                table[index].s=State::deleted_key;
                return true;
            }
            else if(table[index].s==State::empty_key)
            {
                return false;
            }
        }

        return false;
    }

    void print() const
    {
        for(auto &iter: table)
        {
            if(iter.s==State::has_key)
            {
                std::cout<<iter.kv.first<<" "<<iter.kv.second<<std::endl;
            }
        }
    }

private:
    slot table[31];

    int h(int key) const
    {
        return key%31;
    }

    int h2(int key) const
    {
        return 13-(key%13);
    }

};

int main()
{
    my_hash_table table;

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
