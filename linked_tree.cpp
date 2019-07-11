 #include "linked_tree.h"

Linked_tree::Linked_tree(){

}

Linked_tree::Linked_tree(unsigned long size){
    std::vector<Linked_node> position(size);
    this->position = position;
}

//Link v on w
void Linked_tree::add(unsigned long v, unsigned long w){
    if(number_of_nodes == 0){
        set_root(get_position(w));
    }
    get_position(w)->set_next(get_position(v));
    get_position(v)->set_prev(get_position(w));
    number_of_nodes++;
}

Linked_node * Linked_tree::get_position(unsigned long id){
    return &this->position[id];
}

void Linked_tree::set_root(Linked_node *root){
    this->root = root;
    this->root->set_prev(this->root);
}
