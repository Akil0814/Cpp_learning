#include <iostream>

class RBTree
{
public:
    enum class NodeColor { Red , Black };


    struct Node
    {
        Node(int v):key(v){}

        int key;
        Node* parent=nullptr;
        Node* left=nullptr;
        Node* right=nullptr;

        NodeColor color=NodeColor::Red;
    };

public:
    void inster(int key)
    {
        if(root==nullptr)
        {
            root=new Node(key);
            root->color=NodeColor::Black;
            return;
        }

        Node* new_node = find_place_insetr(key);
        cheek_tree_blance(new_node);
    }

    bool remove_node(int key)
    {
        return true;
    }

    void print_tree()
    {

    }

private:

    Node* find_place_insetr(int key)
    {
        Node* current=root;
        while(current!=nullptr)
        {
            if(current->key>key)
                current=current->left;
            else
                current=current->right;
        }
        current=current->parent;


        Node* new_node=new Node(key);
        if(current->key > key)
            current->left=new_node;

        else
            current->right=new_node;

        new_node->parent=current;
        new_node->color=NodeColor::Red;

        return new_node
    }

    void cheek_tree_blance(Node* x)
    {
        Node* p=nullptr;
        Node* g=nullptr;
        Node* u=nullptr;
        if(x==nullptr)
            return;

        if(x->parent!=nullptr)
            p = x -> parent;

        if(p->color==NodeColor::Black)
            return;

        if(p->parent!=nullptr)
            g=p->parent;

        if(g->left==p)
            u=g->right;
        else
            u=g->left;


        if(u==nullptr || u->color==NodeColor::Black)
        {

        }
        else
            recolor()


    }

    void recolor(Node* x)
    {

    }

    void LL(Node* x,Node* p,Node* g,Node* u)
    {
        if(g->parent==nullptr)
        {
            root=p;
            p->right=p;

            return;
        }

        p->parent=g->parent;
        p->right=g;
        g->parent=p;
    }

    void RR(Node* x,Node* p,Node* g,Node* u)
    {
        if(g->parent==nullptr)
        {
            root=p;
            p->left=p;

            return;
        }

        p->parent=g->parent;
        p->left=g;
        g->parent=p;

    }

    void RL(Node* x,Node* p,Node* g,Node* u)
    {
        RR(x,p,g,u);
    }

    void LR(Node* x,Node* p,Node* g,Node* u)
    {
        LL(x,p,g,u);
    }

    void right_rotation(Node* x,Node* p,Node* g,Node* u)
    {

    }

    void left_rotation(Node* x,Node* p,Node* g,Node* u)
    {

    }

    void change_color(Node* x)
    {
        x->color==NodeColor::Black ? x->color=NodeColor::Red :x->color=NodeColor::Black;
    }

    void set_color(Node* x, NodeColor target)
    {
        x->color=target;
    }

private:
    Node* root=nullptr;
};


int main()
{

    return 0;
}
