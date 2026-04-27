#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    char ch;
    int freq;
    int order;
    Node* left;
    Node* right;

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        if (a->freq != b->freq) {
            return a->freq > b->freq;
        }
        return a->order > b->order;
    }
};

string displayCharacter(char ch) {
    switch (ch) {
    case ' ':
        return "[space]";
    case '\n':
        return "[newline]";
    case '\t':
        return "[tab]";
    case '\'':
        return "'\\''";
    default:
        if (isprint(static_cast<unsigned char>(ch))) {
            return string("'") + ch + "'";
        }

        ostringstream out;
        out << "[ascii " << static_cast<int>(static_cast<unsigned char>(ch)) << "]";
        return out.str();
    }
}

Node* makeNode(vector<unique_ptr<Node>>& storage, char ch, int freq, int order, Node* left, Node* right) {
    storage.push_back(make_unique<Node>(Node{ch, freq, order, left, right}));
    return storage.back().get();
}

void buildCodes(const Node* node, const string& path, unordered_map<char, string>& codes) {
    if (node == nullptr) {
        return;
    }

    if (node->isLeaf()) {
        codes[node->ch] = path.empty() ? "0" : path;
        return;
    }

    buildCodes(node->left, path + "0", codes);
    buildCodes(node->right, path + "1", codes);
}

string encodeText(const string& text, const unordered_map<char, string>& codes) {
    string encoded;
    for (char ch : text) {
        encoded += codes.at(ch);
    }
    return encoded;
}

string decodeText(const string& encoded, const Node* root) {
    if (root == nullptr) {
        return "";
    }

    if (root->isLeaf()) {
        return string(encoded.size(), root->ch);
    }

    string decoded;
    const Node* current = root;

    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;
        if (current->isLeaf()) {
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

void printWrappedBits(const string& bits, size_t width) {
    for (size_t i = 0; i < bits.size(); i += width) {
        cout << bits.substr(i, width) << '\n';
    }
}

int main() {
    const string gettysburgAddress =
        "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.\n"
        "Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this.\n"
        "But, in a larger sense, we cannot dedicate -- we cannot consecrate -- we cannot hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.";

    unordered_map<char, int> frequencies;
    for (char ch : gettysburgAddress) {
        ++frequencies[ch];
    }

    vector<pair<char, int>> frequencyTable(frequencies.begin(), frequencies.end());
    sort(frequencyTable.begin(), frequencyTable.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return static_cast<unsigned char>(a.first) < static_cast<unsigned char>(b.first);
    });

    vector<unique_ptr<Node>> storage;
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    int nextOrder = 0;

    for (const auto& [ch, freq] : frequencyTable) {
        pq.push(makeNode(storage, ch, freq, nextOrder++, nullptr, nullptr));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = makeNode(storage, '\0', left->freq + right->freq, nextOrder++, left, right);
        pq.push(parent);
    }

    Node* root = pq.top();

    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    vector<pair<char, string>> codeTable(codes.begin(), codes.end());
    sort(codeTable.begin(), codeTable.end(), [](const auto& a, const auto& b) {
        return static_cast<unsigned char>(a.first) < static_cast<unsigned char>(b.first);
    });

    const string encoded = encodeText(gettysburgAddress, codes);
    const string decoded = decodeText(encoded, root);

    cout << "Frequency Table and Huffman Codes\n";
    cout << "---------------------------------\n";
    cout << left << setw(12) << "Character" << setw(12) << "Frequency" << "Code\n";
    for (const auto& [ch, code] : codeTable) {
        cout << left << setw(12) << displayCharacter(ch)
             << setw(12) << frequencies[ch]
             << code << '\n';
    }

    cout << "\nEncoded Gettysburg Address\n";
    cout << "--------------------------\n";
    printWrappedBits(encoded, 80);

    cout << "\nDecoded Gettysburg Address\n";
    cout << "--------------------------\n";
    cout << decoded << '\n';

    const size_t originalBits = gettysburgAddress.size() * 8;
    const size_t compressedBits = encoded.size();
    const double compressedFraction = static_cast<double>(compressedBits) / static_cast<double>(originalBits);
    const double savingPercent = (1.0 - compressedFraction) * 100.0;
    const double compressionRatio = static_cast<double>(originalBits) / static_cast<double>(compressedBits);

    cout << "\nCompression Statistics\n";
    cout << "----------------------\n";
    cout << "Original bits   : " << originalBits << '\n';
    cout << "Compressed bits : " << compressedBits << '\n';
    cout << fixed << setprecision(4);
    cout << "Compression ratio (original/compressed) : " << compressionRatio << ":1\n";
    cout << "Compressed size fraction                : " << compressedFraction << '\n';
    cout << "Space saved                             : " << savingPercent << "%\n";

    return 0;
}
