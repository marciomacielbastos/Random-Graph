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
    this->elements.insert(e.begin(), e.end());
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
