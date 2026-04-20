#include <iostream>
#include <queue>

class RBTree
{
public:
    enum class NodeColor { Red, Black };

    struct Node
    {
        explicit Node(int v) : key(v) {}

        int key;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
        NodeColor color = NodeColor::Red;
    };

public:
    RBTree() = default;

    ~RBTree()
    {
        destroy(root);
    }

    void insert(int key)
    {
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr)
        {
            parent = current;
            if (key < current->key)
            {
                current = current->left;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                //ignore duplicate keys.
                return;
            }
        }

        Node* new_node = new Node(key);
        new_node->parent = parent;

        if (parent == nullptr)
        {
            root = new_node;
        }
        else if (key < parent->key)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }

        insert_fixup(new_node);
    }

    bool remove_node(int key)
    {

        return false;
    }

    void print_tree() const
    {
        if (root == nullptr)
        {
            std::cout << "(empty tree)\n";
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        int level = 0;
        while (!q.empty())
        {
            std::size_t level_size = q.size();
            std::cout << "Level " << level << ": ";

            for (std::size_t i = 0; i < level_size; ++i)
            {
                Node* node = q.front();
                q.pop();

                std::cout << node->key << "(" << color_to_char(node->color) << ",p=";
                if (node->parent)
                {
                    std::cout << node->parent->key;
                }
                else
                {
                    std::cout << "null";
                }
                std::cout << ") ";

                if (node->left)
                {
                    q.push(node->left);
                }
                if (node->right)
                {
                    q.push(node->right);
                }
            }

            std::cout << "\n";
            ++level;
        }
    }

private:
    static char color_to_char(NodeColor color)
    {
        return color == NodeColor::Red ? 'R' : 'B';
    }

    static NodeColor get_color(Node* node)
    {
        return node == nullptr ? NodeColor::Black : node->color;
    }

    void insert_fixup(Node* x)
    {
        while (x != root && get_color(x->parent) == NodeColor::Red)
        {
            Node* p = x->parent;
            Node* g = p->parent;
            if (g == nullptr)
            {
                break;
            }

            if (p == g->left)
            {
                Node* u = g->right;

                if (get_color(u) == NodeColor::Red)
                {
                    p->color = NodeColor::Black;
                    u->color = NodeColor::Black;
                    g->color = NodeColor::Red;
                    x = g;
                }
                else
                {
                    if (x == p->right)
                    {
                        x = p;
                        left_rotate(x);
                        p = x->parent;
                        g = p ? p->parent : nullptr;
                    }

                    if (p)
                    {
                        p->color = NodeColor::Black;
                    }
                    if (g)
                    {
                        g->color = NodeColor::Red;
                        right_rotate(g);
                    }
                }
            }
            else
            {
                Node* u = g->left;

                if (get_color(u) == NodeColor::Red)
                {
                    p->color = NodeColor::Black;
                    u->color = NodeColor::Black;
                    g->color = NodeColor::Red;
                    x = g;
                }
                else
                {
                    if (x == p->left)
                    {
                        x = p;
                        right_rotate(x);
                        p = x->parent;
                        g = p ? p->parent : nullptr;
                    }

                    if (p)
                    {
                        p->color = NodeColor::Black;
                    }
                    if (g)
                    {
                        g->color = NodeColor::Red;
                        left_rotate(g);
                    }
                }
            }
        }

        if (root)
        {
            root->color = NodeColor::Black;
        }
    }

    void left_rotate(Node* x)
    {
        if (x == nullptr || x->right == nullptr)
        {
            return;
        }

        Node* y = x->right;
        x->right = y->left;
        if (y->left)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node* x)
    {
        if (x == nullptr || x->left == nullptr)
        {
            return;
        }

        Node* y = x->left;
        x->left = y->right;
        if (y->right)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }

    void destroy(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

private:
    Node* root = nullptr;
};

int main()
{
    RBTree tree;

    int values[] = {33,22,50,44,55,60};
    std::cout<<"----------------------start--------------------"<<std::endl;

    for (int value : values)
    {
        tree.insert(value);
    }

    tree.print_tree();

    std::cout<<"---------------------delete 33--------------------"<<std::endl;


    return 0;
}
