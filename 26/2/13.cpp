#include<iostream>
#include<vector>
#include <queue>
#include <stack>
#include <initializer_list>

class BinaryTree
{
private:
    struct Node
    {
        int value{};
        int left=-1;
        int right=-1;
        int parent=-1;
    };
public:
    BinaryTree() = default;

    BinaryTree(std::initializer_list<int> init)
    {
        _tree.reserve(init.size());
        for(auto it=init.begin();it!=init.end(); ++it)
        {
            insert(*it);
        }
    }

    void insert(int v)
    {
        if(_root==-1)
        {
            new_node(v,-1);
            return;
        }

        int cur= _root;
        int parent= -1;

        while(cur!= -1)
        {
            parent=cur;
            if(v<_tree[cur].value)
                parent=_tree[cur].left;

            else
                parent=_tree[cur].right;
        }

        int pos=new_node(v,parent);
        if(v<_tree[parent].value)
            _tree[parent].left=pos;
        else
            _tree[parent].right=pos;
    }

    std::vector<int> inorder()const
    {
        if(_root==-1)
            return {};

        std::vector<int> out;
        std::stack<int> st;
        int cur = _root;

        while (cur != -1 || !st.empty())
        {
            while (cur != -1) {
                st.push(cur);
                cur = _tree[cur].left;
            }
            cur = st.top(); st.pop();
            out.push_back(_tree[cur].value);
            cur = _tree[cur].right;
        }
        return out;
    }

    std::vector<int> preorder()const
    {
        if(_root==-1)
            return {};
        std::vector<int> out;


        return out;

    }

    std::vector<int> postorder()const
    {
        if(_root==-1)
            return {};
        std::vector<int> out;


        return out;
    }

    std::vector<int> bfs()const
    {
        if(_root==-1)
            return {};
         std::vector<int> out;


        return out;
    }

private:

    int new_node(int val, int parent)
    {
        _tree.push_back(Node{val,-1,-1,parent});

        return _tree.size()-1;
    }

private:
    int _root = -1;

    std::vector<Node> _tree;
};


int main()
{


    return 0;
}
