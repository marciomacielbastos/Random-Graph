#ifndef BFS_MODIFIED_H
#define BFS_MODIFIED_H
#include <distance_matrix.h>
#include <linked_list.h>
#include <network.h>
#include <vector>

class Bfs_modified{
private:
    Distance_matrix distance_matrix;
    Linked_list ll;
    std::vector<std::vector<unsigned long int>> lon;

public:
    Bfs_modified();
    Bfs_modified(Network net);
    void mount_dist_matrix();
};

#endif // BFS_MODIFIED_H
