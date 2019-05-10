#include "unionfind.h"

UnionFind::UnionFind(unsigned long int N){
    this->count = N;
    Components c;
    for(unsigned long int i=0; i < N; i++){
        this->id.push_back(i);
        this->components.insert(std::make_pair(i, Components(i)));
    }
    for(unsigned int i=0; i < N;i++){
        this->sizes.push_back(1);
    }
}

unsigned long int UnionFind::GetNumberOfComponents(){
    return count;
}

unsigned long int UnionFind::Find(unsigned long int v){
    while (v != this->id[v]) {
       v = this->id[v];
    }
    return v;
}

void UnionFind::Union(unsigned long int v, unsigned long int w){
    unsigned long int vRoot = this->Find(v);
    unsigned long int wRoot = this->Find(w);
    std::map<unsigned long int, Components>::iterator it1;
    std::map<unsigned long int, Components>::iterator it2;
    it1 = this->components.find(vRoot);
    it2 = this->components.find(wRoot);
    if(vRoot == wRoot) return;
    else if (this->sizes[vRoot] < this->sizes[wRoot]) {
        this->id[vRoot] = wRoot;
        this->sizes[wRoot] += this->sizes[vRoot];

        //Union the component sets
        it2->second.Union(it1->second);
        this->components.erase(it1->first);

    } else {
        this->id[wRoot] = vRoot;
        this->sizes[vRoot] += this->sizes[wRoot];

        //Union the component sets
        it1->second.Union(it2->second);
        this->components.erase(it2->first);
    }
    this->count--;
}

bool UnionFind::Connected(unsigned long int v, unsigned long int w){
    return (this->Find(v) == this->Find(w));
}
