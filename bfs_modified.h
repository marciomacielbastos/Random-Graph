#ifndef BFS_MODIFIED_H
#define BFS_MODIFIED_H
#include <binary_adjmatrix.h>
#include <distance_matrix.h>
#include <linked_list.h>
#include <network.h>
#include <vector>

class Bfs_modified{
private:
    double average_path;
//    Distance_matrix distance_matrix;
    Binary_adjmatrix binary_adjmatrix;
    Linked_list linked_lists;
    std::vector<std::vector<unsigned long int>> neighbors;


public:
    Bfs_modified();
    Bfs_modified(Network net);
    double avg_geo_dist();

};

#endif // BFS_MODIFIED_H
