#include "rede.h"

Rede::Rede(unsigned long int  N, Random *rd){
    this->N = N;
    this->distribution = rd;
    this->degrees = this->distribution->random(N);
    for(unsigned long int i = 0; i < N; i++){
        std::vector<unsigned long int> foo;
        this->adj_matrix.push_back(foo);
    }
}

void Rede::reset(){
    this->degrees = this->distribution->random(N);
    {
        std::vector<std::vector<unsigned long int>> foo;
        this->adj_matrix.swap(foo);
    }
    for(unsigned long int i = 0; i < N; i++){
        std::vector<unsigned long int> bar;
        this->adj_matrix.push_back(bar);
    }
}

std::vector<unsigned long int> Rede::mount_algorithm_list(){
    std::vector<unsigned long int> algorithm_list;
    for(unsigned long int i = 0; i < N; i++){
        for(unsigned long int j = 0; j < this->degrees[i]; j++){
            algorithm_list.push_back(i);
        }
    }
    return algorithm_list;
}

bool Rede::is_connected(unsigned long v, unsigned long w){
    if(this->adj_matrix[v].size() <= this->adj_matrix[w].size()){
        for(unsigned long int i = 0; i < this->adj_matrix[v].size(); i++){
            if(this->adj_matrix[v][i] == w){
                return true;
            }
        }
    } else {
        for(unsigned long int i = 0; i < this->adj_matrix[w].size(); i++){
            if(this->adj_matrix[w][i] == v){
                return true;
            }
        }
    }
    return false;
}

void Rede::link(unsigned long v, unsigned long w){
    this->adj_matrix[v].push_back(w);
    this->adj_matrix[w].push_back(v);
}

bool Rede::random_link(){
    std::vector<unsigned long int> algorithm_list = mount_algorithm_list();
    int counter = 0;
    while(algorithm_list.size() > 1){
        unsigned long int rand1 =  distribution->discrete_uniform(0, algorithm_list.size());
        unsigned long int rand2 =  distribution->discrete_uniform(0, algorithm_list.size());
        unsigned long int rnd1 = algorithm_list[rand1];
        unsigned long int rnd2 = algorithm_list[rand2];
        while((rnd1 == rnd2) || (is_connected(rnd1, rnd2))){
            if(counter >= 100){
                return false;
            }
            rand1 =  distribution->discrete_uniform(algorithm_list.size());
            rand2 =  distribution->discrete_uniform(algorithm_list.size());
            rnd1 = algorithm_list[rand1];
            rnd2 = algorithm_list[rand2];
            counter++;
        }
        link(rnd1, rnd2);
        counter = 0;
        if(rand1 < rand2){
            if(rand2 == algorithm_list.size()-2){
                algorithm_list[rand1] = algorithm_list[algorithm_list.size()-1];
            } else{
                algorithm_list[rand1] = algorithm_list[algorithm_list.size()-2];
                algorithm_list[rand2] = algorithm_list[algorithm_list.size()-1];
            }
        }
        else if (rand2 < rand1){
            if(rand1 == algorithm_list.size()-2){
                algorithm_list[rand2] = algorithm_list[algorithm_list.size()-1];
            } else{
                algorithm_list[rand1] = algorithm_list[algorithm_list.size()-1];
                algorithm_list[rand2] = algorithm_list[algorithm_list.size()-2];

            }
        }
        algorithm_list.pop_back();
        algorithm_list.pop_back();
    }
    return true;
}
