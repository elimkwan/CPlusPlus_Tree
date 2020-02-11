#include "tree.hpp"

int Tree::insert(Node* active_node, Rectangle r) {

    if (!check_valid(r)){
        return 0;
    }

    //when active node contain the incoming rect, check if children of active node contain the incoming rect
    if ((contain_rect(active_node->data, r, active_node) && !active_node->children.empty())){
        //case 1: one of the children of the active node contain the incoming rect: call insert function again, changing active node to that specific child address
        //case 2: one of the children of the active node is contained by the incoming rect: add incoming rect as one of the child of that children, and swap their data 
        //case 3: none of the children of the active node contain the incoming rect && incoming rect also doesnt contain any of the children: add incoming rect as child of active node
        int children_no = active_node->children.size();
        for (int i = 0; i < children_no; i++){
            Node* child_addr = active_node->children[i];
            //case 1
            if (contain_rect(child_addr-> data,r, child_addr)){
                insert(child_addr, r);
                return 1;
            }
            //case 2
            if (contain_rect(r, child_addr->data)){
                //if incoming shape contain children, add as children of children, then swap
                child_addr->children.push_back(create_new_node(r, child_addr));
                Node* new_addr = child_addr-> children.back();
                //cout<< "insert as child " << new_addr << " and its parent is " << child_addr << endl; //DEBUG
                swap(child_addr, new_addr);
                //cout<< "swappping data of " << child_addr<< " and " << new_addr << endl; //DEBUG
                return 1;
            }
        }
        //case 3
        active_node->children.push_back(create_new_node(r, active_node));
        //Node* addr = active_node->children.back(); //DEBUG
        //cout<< "insert as child " << addr << " and its parent is " << active_node << endl; //DEBUG
        return 1;
    
    //when active node contain the incoming rect but doesnt have any children: add incoming rect as children of active node
    } else if (contain_rect(active_node->data, r, active_node)){
        active_node->children.push_back(create_new_node(r, active_node));
        //Node* addr = active_node->children.back(); //DEBUG
        //cout<< "insert as child " << addr << " and its parent is " << active_node << endl; //DEBUG
        return 1;
    }

    cout << "Error: Fail to insert rectangle" << endl;
    return 0;
}

Node* Tree::set_root(){
    Rectangle r (0.0, 0.0, 0.0, 0.0);
    Node* leaf = create_new_node(r, NULL);
    Tree::root = leaf;
    //cout<< "create root at address " << leaf <<endl; //DEBUG
    return leaf;
}

int Tree::get_count(){
    return Tree::count;
}

Node* Tree::create_new_node(Rectangle r, Node* parent){
    vector<Node*> children;
    bool land = true;
    Tree::count += 1;
    if (parent == NULL || parent -> land){
        land = false;
        Tree::count -= 1;
    }
    Node* new_node = new Node(r, parent, children, land);
    return new_node;
}

bool Tree::contain_rect(Rectangle a, Rectangle b, Node* outer_r_addr){
    if (outer_r_addr == Tree::root){
        return true;
    }
    return(a.x1 < b.x1 && a.y1 < b.y1 && a.x2 > b.x2 && a.y2 > b.y2);
}

bool Tree::check_valid(Rectangle r){
    //check for valid max min pt 
    if (!(r.y2 > r.y1 && r.x2 > r.x1)){
        return false;
    }
    return true;
}

void Tree::swap(Node* addr1, Node* addr2){
    //Before swapping: addr1 is the parent with smaller shape and addr2 is the children with bigger shape
    //After swapping: addr1 is parent with bigger shape and addr2 is the children with smaller shape
    Rectangle r1 = addr1 -> data;
    Rectangle r2 = addr2-> data;

    //swap the data and classification of land of addr1 and addr2
    addr1 -> data = r2; //bigger shape
    addr1 -> land = !(addr2 -> land);
    addr2 -> data = r1; //smaller shape
    addr2 -> land = !(addr1 -> land);

    //check if the inital parent(addr1) have other children, if yes:
    //case 1: the new parent contain that child: add a child to addr 1 and update the parent of that child to addr 1
    //case 2: the new parent doesnt contain that child: do nothing
    Node* initial_parent = addr1 -> parent;
    if (initial_parent != NULL && initial_parent ->children.size() > 1){
        int size = initial_parent ->children.size();
        vector<Node*> addr1_parent_new_children; 
        for (int i =0; i<size; i++){
            Node* active_child = addr1 -> parent ->children[i];
            Node* active_child_parent = addr1 -> parent ->children[i]-> parent;
            addr1_parent_new_children.push_back(active_child);
            if (active_child != addr1 && contain_rect(r2, active_child -> data)){ //if child is not addr1 and the new parent contain it
                //case 1
                addr1 -> children.push_back(active_child);//add a child to addr 1
                active_child_parent = addr1; //update child's parent from addr2 to addr1
                addr1_parent_new_children.pop_back(); //remove that child from the children list of addr 1 parents

                //update land count
                bool land = true;
                if (active_child_parent == NULL || active_child_parent -> land){
                    land = false;
                    Tree::count -= 1;
                } else {
                    Tree::count += 1;
                }
                active_child -> land = land;
                //cout << "updated " <<  active_child << "parent to " << addr1 <<endl;//DEBUG

            }
        }
        addr1 -> parent -> children = addr1_parent_new_children;
        
    }

}