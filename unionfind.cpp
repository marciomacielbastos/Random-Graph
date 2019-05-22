#include "unionfind.h"

UnionFind::UnionFind(unsigned long int N){
    this->count = N;
    Components c;
    for(unsigned long int i=0; i < N; i++){
        this->id.push_back(i);
//        this->components.insert(std::make_pair(i, Components(i)));
    }
    for(unsigned int i=0; i < N;i++){
        this->sizes.push_back(1);
        this->number_of_clusters_per_size.push_back(0);
    }
    this->number_of_clusters_per_size[0] = N;
}

unsigned long int UnionFind::get_number_of_components(){
    return count;
}

unsigned long int UnionFind::find(unsigned long int v){
    while (v != this->id[v]) {
       v = this->id[v];
    }
    return v;
}

void UnionFind::union_(unsigned long int v, unsigned long int w){
    unsigned long int vRoot = this->find(v);
    unsigned long int wRoot = this->find(w);
    unsigned long int vsize, wsize;
//    std::map<unsigned long int, Components>::iterator it1;
//    std::map<unsigned long int, Components>::iterator it2;
//    it1 = this->components.find(vRoot);
//    it2 = this->components.find(wRoot);
    if(vRoot == wRoot) return;
    else if (this->sizes[vRoot] < this->sizes[wRoot]) {
        this->id[vRoot] = wRoot;
        vsize = this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[vsize-1]--;
        this->number_of_clusters_per_size[wsize-1]--;
        this->sizes[wRoot] += this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[wsize-1]++;
        //Union the component sets
//        it2->second.Union(it1->second);
//        this->components.erase(it1->first);

    } else {
        this->id[wRoot] = vRoot;
        vsize = this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[vsize-1]--;
        this->number_of_clusters_per_size[wsize-1]--;
        this->sizes[vRoot] += this->sizes[wRoot];
        vsize = this->sizes[vRoot];
        this->number_of_clusters_per_size[vsize-1]++;
        //Union the component sets
//        it1->second.Union(it2->second);
//        this->components.erase(it2->first);
    }
    this->count--;
}

bool UnionFind::is_connected(unsigned long int v, unsigned long int w){
    return (this->find(v) == this->find(w));
}

std::vector<unsigned long int> UnionFind::get_size_of_components(){
    return this->number_of_clusters_per_size;
}

//std::vector<unsigned long int> UnionFind::GetComponentsSize(){
//    std::vector<unsigned long int> list;
//    for (auto it = components.begin(); it != components.end(); it++) {
//        list.push_back(it->second.GetElements().size());
//    }
//    std::sort(list.begin(), list.end());
//    return list;
//}


//std::map<unsigned long int, Components> UnionFind::GetComponents(){
//    return this->components;
//}

//std::vector<unsigned long int> UnionFind::GetComponentsSize(){
//    std::vector<unsigned long int> list;
//    for (auto it = components.begin(); it != components.end(); it++) {
//        list.push_back(it->second.GetElements().size());
//    }
//    std::sort(list.begin(), list.end());
//    return list;
//}

//std::map<unsigned long int, unsigned long int> UnionFind::GetSizeQuantity(){
//    std::vector<unsigned long int> list = GetComponentsSize();
//    std::map<unsigned long int, unsigned long int> numSize;
//    unsigned long int i_nodes = list[0];
//    unsigned long int number_of_components_with_i_nodes = 0;
//    while (list.size()) {
//        if(list[0] == i_nodes){
//            number_of_components_with_i_nodes++;
//            list.erase(list.begin());
//        } else {
//           numSize.insert(std::pair<unsigned long int, unsigned long int>(i_nodes, number_of_components_with_i_nodes));
//           i_nodes = list[0];
//           number_of_components_with_i_nodes = 1;
//           list.erase(list.begin());
//        }
//    }
//    numSize.insert(std::pair<unsigned long int, unsigned long int>(i_nodes, number_of_components_with_i_nodes));
//    return numSize;
//}
