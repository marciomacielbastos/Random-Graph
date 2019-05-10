#include "components.h"

Components::Components(){

}

Components::Components(unsigned long int id){
    this->id = id;
    this->elements.insert(id);
}

std::set<unsigned long int> Components::GetElements(){
    return this->elements;
}

void Components::Union(Components c){
    std::set<unsigned long int> e = c.GetElements();
    std::set<unsigned long int> new_elements;
    std::set_union(e.begin(), e.end(), this->elements.begin(), this->elements.end(), std::inserter(new_elements, new_elements.begin()));
    this->elements = new_elements;
//    this->elements.insert(e.begin(), e.end());
}

unsigned long int Components::GetId() const{
    return this->id;
}

bool Components::operator=(const Components & c) const{
    return this->GetId() == c.GetId();
}

bool Components::operator=(const unsigned long &id) const{
   return this->GetId() == id;
}

bool Components::operator<(const Components & c) const{
    return this->GetId() < c.GetId();
}

bool Components::operator<(const unsigned long int & id) const{
    return this->GetId() < id;
}
