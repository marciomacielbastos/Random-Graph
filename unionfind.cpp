#include "unionfind.h"

UnionFind::UnionFind(){

}

UnionFind::UnionFind(unsigned long int N){
    std::pair<unsigned long int, unsigned long int> st_biggest (0, 0);
    std::pair<unsigned long int, unsigned long int> nd_biggest (0, 0);
    this->st_biggest =  st_biggest;
    this->nd_biggest = nd_biggest;
    this->count = N;
    for(unsigned long int i=0; i < N; i++){
        this->root.push_back(i);
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
    while (v != this->root[v]) {
       v = this->root[v];
    }
    return v;
}

void UnionFind::union_(unsigned long int v, unsigned long int w){
    unsigned long int vRoot = this->find(v);
    unsigned long int wRoot = this->find(w);
    unsigned long int vsize, wsize;
    if(vRoot == wRoot) return;
    else if (this->sizes[vRoot] <= this->sizes[wRoot]) {
        this->root[vRoot] = wRoot;
        vsize = this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[vsize-1]--;
        this->number_of_clusters_per_size[wsize-1]--;
        this->sizes[wRoot] += this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[wsize-1]++;
        if(wsize > this->st_biggest.second){
            if(this->st_biggest.first != wRoot){
                this->nd_biggest.first = this->st_biggest.first;
                this->nd_biggest.second = this->st_biggest.second;
                this->st_biggest.first = wRoot;
                this->st_biggest.second = wsize;
            }
            else{
                this->st_biggest.second = wsize;
            }
        }
        else if (wsize > this->nd_biggest.second) {
            this->nd_biggest.first = wRoot;
            this->nd_biggest.second = wsize;
        }

    } else {
        this->root[wRoot] = vRoot;
        vsize = this->sizes[vRoot];
        wsize = this->sizes[wRoot];
        this->number_of_clusters_per_size[vsize-1]--;
        this->number_of_clusters_per_size[wsize-1]--;
        this->sizes[vRoot] += this->sizes[wRoot];
        vsize = this->sizes[vRoot];
        this->number_of_clusters_per_size[vsize-1]++;
        if(vsize > this->st_biggest.second){
            if(this->st_biggest.first != vRoot){
                this->nd_biggest.first = this->st_biggest.first;
                this->nd_biggest.second = this->st_biggest.second;
                this->st_biggest.first = vRoot;
                this->st_biggest.second = vsize;
            }
            else {
                this->st_biggest.second = vsize;
            }
        }
        else if (vsize > this->nd_biggest.second) {
            this->nd_biggest.first = vRoot;
            this->nd_biggest.second = vsize;
        }
    }
    this->count--;
}

bool UnionFind::is_connected(unsigned long int v, unsigned long int w){
    return (this->find(v) == this->find(w));
}

std::vector<unsigned long int> UnionFind::get_size_of_components(){
    return this->number_of_clusters_per_size;
}

unsigned long int UnionFind::get_max_comp(){
    return st_biggest.second;
}

std::pair<unsigned long int, unsigned long int> UnionFind::get_nd_biggest(){
    return this->nd_biggest;
}

std::pair<unsigned long int, unsigned long int> UnionFind::get_st_biggest(){
    return this->st_biggest;
}

/***************************************************************/
/*                         Working                             */
/***************************************************************/


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
