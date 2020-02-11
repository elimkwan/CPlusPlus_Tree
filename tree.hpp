#ifndef tree
#define tree
#include <vector>
#include <iostream>
#include "./tests/catch.hpp"

using namespace std;

struct Rectangle
{
    float x1, y1, x2, y2;
    Rectangle(float paramx1, float paramy1, float paramx2, float paramy2) : x1(paramx1), y1(paramy1), x2(paramx2), y2(paramy2) {}
};

struct Node
{
    Rectangle data;
    Node* parent;
    vector<Node*> children;
    Node(Rectangle paramdata, Node* paramparent, vector<Node*> paramchildren, bool paramland): data(paramdata), parent(paramparent), children(paramchildren), land(paramland){}
    bool land;
};

class Tree
{
    public:
        Node* root;
        int count;

        Tree(){
            root = 0x0;
            count = 0;
        }

        int insert(Node*, Rectangle);
        Node* set_root();
        int get_count();

    private:
        Node* create_new_node(Rectangle, Node*);
        bool contain_rect(Rectangle, Rectangle, Node* = NULL);
        bool check_valid(Rectangle);
        void swap(Node*, Node*);
};


#endif