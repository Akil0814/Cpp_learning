#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace std;

class SkipList
{
private:

    struct Node
    {
        int key;
        string value;
        vector<Node*> forward;

        Node(int key_value, const string& text_value, int level_count)
            : key(key_value), value(text_value), forward(level_count, nullptr) {}
    };

    static constexpr int max_level = 6;

    Node* head;
    int current_level;

    mt19937 random_engine;
    bernoulli_distribution coin_distribution;

    bool next_flip()
    {
        bool flip_result = coin_distribution(random_engine);
        cout << (flip_result ? "true" : "false") << " ";
        return flip_result;
    }

    int random_level()
    {
        int node_level = 1;
        cout << "Coin flips: ";
        while (node_level < max_level && next_flip()) {
            node_level++;
        }
        cout << "\n";
        return node_level;
    }

public:
    explicit SkipList(uint32_t seed = 20260316)
        : head(nullptr), current_level(1), random_engine(seed), coin_distribution(0.5)
        {
        head = new Node(numeric_limits<int>::min(), "", max_level);
        }

    ~SkipList()
    {
        Node* current_node = head;
        while (current_node) {
            Node* next_node = current_node->forward[0];
            delete current_node;
            current_node = next_node;
        }
    }

    bool search(int key, string& out_value) const
    {
        Node* current_node = head;

        for (int level_index = current_level - 1; level_index >= 0; --level_index)
        {
            while (current_node->forward[level_index] && current_node->forward[level_index]->key < key)
            {
                current_node = current_node->forward[level_index];
            }
        }

        current_node = current_node->forward[0];
        if (current_node && current_node->key == key)
        {
            out_value = current_node->value;
            return true;
        }
        return false;
    }

    void insert(int key, const string& value)
    {
        vector<Node*> update_nodes(max_level, nullptr);
        Node* current_node = head;

        for (int level_index = current_level - 1; level_index >= 0; --level_index)
        {
            while (current_node->forward[level_index] && current_node->forward[level_index]->key < key)
            {
                current_node = current_node->forward[level_index];
            }
            update_nodes[level_index] = current_node;
        }

        current_node = current_node->forward[0];

        if (current_node && current_node->key == key)
        {
            current_node->value = value;
            cout << "Updated key " << key << " -> " << value << "\n";
            return;
        }

        int node_level = random_level();

        if (node_level > current_level)
        {
            for (int level_index = current_level; level_index < node_level; ++level_index)
            {
                update_nodes[level_index] = head;
            }
            current_level = node_level;
        }

        Node* new_node = new Node(key, value, node_level);
        for (int level_index = 0; level_index < node_level; ++level_index)
        {
            new_node->forward[level_index] = update_nodes[level_index]->forward[level_index];
            update_nodes[level_index]->forward[level_index] = new_node;
        }

        cout << "Inserted " << key << " -> " << value
             << " at level " << node_level << "\n";
    }

    bool erase(int key) {
        vector<Node*> update_nodes(max_level, nullptr);
        Node* current_node = head;

        for (int level_index = current_level - 1; level_index >= 0; --level_index)
        {
            while (current_node->forward[level_index] && current_node->forward[level_index]->key < key)
            {
                current_node = current_node->forward[level_index];
            }
            update_nodes[level_index] = current_node;
        }

        current_node = current_node->forward[0];

        if (!current_node || current_node->key != key)
        {
            cout << "Delete " << key << ": not found\n";
            return false;
        }

        for (int level_index = 0; level_index < current_level; ++level_index)
        {
            if (update_nodes[level_index]->forward[level_index] != current_node)
                break;

            update_nodes[level_index]->forward[level_index] = current_node->forward[level_index];
        }

        delete current_node;

        while (current_level > 1 && head->forward[current_level - 1] == nullptr)
        {
            current_level--;
        }

        cout << "Deleted key " << key << "\n";
        return true;
    }

    void print_levels() const {
        cout << "\n===== Skip List Levels =====\n";
        for (int level_index = current_level - 1; level_index >= 0; --level_index)
        {
            cout << "Level " << (level_index + 1) << ": ";
            Node* current_node = head->forward[level_index];
            while (current_node) {
                cout << current_node->key << " ";
                current_node = current_node->forward[level_index];
            }
            cout << "\n";
        }
    }

    void print_dictionary() const {
        cout << "\n===== Dictionary Keys and Values =====\n";
        Node* current_node = head->forward[0];
        while (current_node)
        {
            cout << current_node->key << " " << current_node->value << "\n";
            current_node = current_node->forward[0];
        }
    }
};

int main()
{
    SkipList dictionary(20260316);

    dictionary.insert(28, "Laguna Niguel");
    dictionary.insert(41, "Mission Viejo");
    dictionary.insert(22, "San Clemente");
    dictionary.insert(44, "Irvine");
    dictionary.erase(41);
    dictionary.erase(42);
    dictionary.insert(58, "Lake Forest");
    dictionary.insert(32, "San Diego");
    dictionary.insert(49, "Anaheim");
    dictionary.erase(58);
    dictionary.insert(31, "Los Angeles");
    dictionary.insert(17, "Orange");
    dictionary.insert(72, "Palms Springs");
    dictionary.insert(41, "Riverside");
    dictionary.erase(72);
    dictionary.insert(19, "Brea");
    dictionary.insert(60, "Santa Ana");
    dictionary.insert(35, "Tustin");
    dictionary.insert(103, "Oceanside");
    dictionary.insert(11, "La Jolla");
    dictionary.insert(28, "Del Mar");
    dictionary.insert(22, "Aliso Viejo");
    dictionary.insert(49, "Laguna Beach");
    dictionary.erase(41);
    dictionary.insert(42, "Vista");
    dictionary.insert(49, "San Diego");
    dictionary.insert(99, "San Juan");
    dictionary.insert(29, "Dana Point");
    dictionary.insert(88, "El Segundo");
    dictionary.insert(41, "San Clemente");
    dictionary.insert(62, "Laguna Hills");

    cout << "\n===== Search Tests =====\n";
    string found_value;
    bool found_existing = dictionary.search(42, found_value);
    cout << "Search 42: " << (found_existing ? "found -> " + found_value : "not found") << "\n";

    bool found_missing = dictionary.search(58, found_value);
    cout << "Search 58: " << (found_missing ? "found -> " + found_value : "not found") << "\n";

    dictionary.print_levels();
    dictionary.print_dictionary();

    return 0;
}
