#ifndef BFS_MODIFIED_H
#define BFS_MODIFIED_H
#include <binary_adjmatrix.h>
#include <distance_matrix.h>
#include <linked_list.h>
#include <network.h>
#include <random.h>
#include <vector>
#include <queue>

class Bfs_modified{
private:
    double average_path;

public:
    Bfs_modified();
    double bfs(unsigned long int root, std::vector<std::vector<unsigned long int>> neighbors);
    std::vector<unsigned long int> bfs_component_return(unsigned long s, std::vector<std::vector<unsigned long int>> neighbors);
    double avg_geo_dist(unsigned long int clk, unsigned long s, std::vector<std::vector<unsigned long int>> neighbors);
};

#endif // BFS_MODIFIED_H
