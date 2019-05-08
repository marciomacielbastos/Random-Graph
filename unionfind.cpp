#include "unionfind.h"

UnionFind::UnionFind(unsigned long int N){
    this->count = N;
    for(unsigned int i=0; i < N; i++){
        this->id.push_back(i);
    }
    for(unsigned int i=0; i < N;i++){
        this->sizes.push_back(1);
    }
}

unsigned long int UnionFind::GetCount(){
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
    if(vRoot == wRoot) return;
    else if (this->sizes[vRoot] < this->sizes[wRoot]) {
        this->id[vRoot] = wRoot;
        this->sizes[wRoot] += this->sizes[vRoot];
    } else {
        this->id[wRoot] = vRoot;
        this->sizes[vRoot] += this->sizes[wRoot];
    }
    this->count--;
}

bool UnionFind::Connected(unsigned long int v, unsigned long int w){
    return (this->Find(v) == this->Find(w));
}
