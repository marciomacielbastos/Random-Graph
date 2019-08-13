#include "bfs_modified.h"
#include <iostream>

Bfs_modified::Bfs_modified(){

}

double Bfs_modified::bfs(unsigned long s, std::vector<std::vector<unsigned long int>> neighbors){
    double dsum = 0;
    double count = 0;
    double dist = 0;
    unsigned long int d1 = 0;
    unsigned long int d2 = 1;
    std::queue<unsigned long int> queue;
    queue.push(s);
    std::vector<bool> marked(neighbors.size(), false);
    marked[s] = true;
    while(!queue.empty()){
        if(d1 == 0){
            d1 = d2;
            d2 = 0;
            dist++;
        }
        unsigned long int v = queue.front();
        queue.pop();
        d1--;
        for(unsigned long int w : neighbors[v]){
            if(!marked[w]){
                d2++;
                dsum += dist;
                count++;
                marked[w] = true;
                queue.push(w);
            }
        }
    }
    //The mean distance is calculated over the size of the component
    return dsum/count;
}

std::vector<unsigned long int> Bfs_modified::bfs_component_return(unsigned long s, std::vector<std::vector<unsigned long int>> neighbors){
    std::vector<unsigned long int> nodes;
    std::queue<unsigned long int> queue;
    queue.push(s);
    std::vector<bool> marked(neighbors.size(), false);
    marked[s] = true;
    while(!queue.empty()){
        unsigned long int v = queue.front();
        queue.pop();
        for(unsigned long int w : neighbors[v]){
            if(!marked[w]){
                marked[w] = true;
                queue.push(w);
            }
        }
    }
    for (unsigned long int i=0; i < marked.size(); i++){
        if(marked[i]){
            nodes.push_back(i);
        }
    }
    return nodes;
}

double Bfs_modified::avg_geo_dist(unsigned long int clk, unsigned long s, std::vector<std::vector<unsigned long int>> neighbors){
    double avg = 0;
    double count = static_cast<double>(clk);
    std::vector<unsigned long int> list_of_nodes = bfs_component_return(s, neighbors);
    while(clk){
        unsigned long int i = Random::discrete_uniform(list_of_nodes.size());
        s = list_of_nodes[i];
        avg += bfs(s, neighbors);
        list_of_nodes.erase(list_of_nodes.begin() + i);
        clk--;
    }
    return avg/count;
}
