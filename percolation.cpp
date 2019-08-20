#include "percolation.h"

Percolation::Percolation(){

}

void Percolation::progress_bar(float progress){
    int bar_width = 70;
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

void Percolation::write_mean_cluster_size(const std::string& params, double pc, double mcs, bool append = false){
    std::ofstream myfile;
    std::string filename("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/Mean_cluster_size_");
    filename = filename + params + ".txt";

    if (append)
        myfile.open(filename, std::ios_base::app);
    else
        myfile.open(filename);

    myfile << pc << "," << mcs << std::endl;
    myfile.close();
}

void Percolation::write_biggest_component(const std::string& params, double pc, unsigned long int biggest, bool append = false){
    std::ofstream myfile;
    std::string filename("/home/marcio/Projects/Random-Graph/Random-Graph/Results/Mean/Biggest_component_");
    filename = filename + params + ".txt";

    if (append)
        myfile.open(filename, std::ios_base::app);
    else
        myfile.open(filename);

    myfile << pc << "," << biggest << std::endl;
    myfile.close();
}

/*************************************************************************/
/*                         To write <l> graphs                           */
/*************************************************************************/

UnionFind Percolation::mount_geodesical_stats(Rede rd){
    std::vector<std::pair<unsigned long int, unsigned long int>> list = rd.get_list_of_links();
    UnionFind uf = UnionFind(rd.get_number_of_nodes());
    while (list.size() > 0) {
        std::pair<unsigned long int, unsigned long int> pair = list[list.size() - 1];
        // Union the nodes of this link
        uf.union_(pair.first, pair.second);
        // Remove the link from the list of links
        list.pop_back();
    }
    return uf;
}

/*********************************************************************************/
/*                         To write percolation graphs                           */
/*********************************************************************************/

UnionFind Percolation::mount_component_stats(Rede rd, unsigned int freq_of_reg, const std::string& params){
    std::vector<std::pair<unsigned long int, unsigned long int>> list = rd.get_list_of_links();
    double total = static_cast<double>(list.size());
    UnionFind uf = UnionFind(rd.get_number_of_nodes());

    double progress = 0.0;
    progress_bar(progress);

    write_mean_cluster_size(params, 0, 1, false);
    write_biggest_component(params, 0, 1, false);

    double k = 1 / static_cast<double>(freq_of_reg);

    while (list.size() > 0) {
        progress += 1 / total;
        std::pair<unsigned long int, unsigned long int> pair = list[list.size() - 1];
        // Union the nodes of this link
        uf.union_(pair.first, pair.second);
        // Remove the link from the list of links
        list.pop_back();

        /**************************************************************************/
        /*                                                                        */
        /*                      Percolation data computation                      */
        /*                                                                        */
        /**************************************************************************/
        if((progress > k) || ((list.size() - 1) == 0)){
            double size = 0;
            double total_numb_of_clusters = 0;
            std::vector<unsigned long int> cls = uf.get_size_of_components();
            for(unsigned long int i = 0; i < cls.size(); i++){
                if(cls[i] > 0){
                    total_numb_of_clusters += (cls[i] + 1);
                    size += static_cast<double>(i) * (cls[i] + 1);
                }
            }
            write_mean_cluster_size(params, progress, (size / total_numb_of_clusters), true);
            write_biggest_component(params, progress, uf.get_st_biggest().second, true);
            k += 1 / static_cast<double>(freq_of_reg);
        }
        /***********************************************************************/

        progress_bar(progress);
    }
    return uf;
}




//

/******************************************************************/
/*                         Deprecated                             */
/******************************************************************/


//This method iterate through a network's links adding them step by step through the Union-Find algorithm.
//In each step the size of the biggest component is added to a vector.

//std::vector<std::vector<double>> Percolation::assembly(){
//    unsigned long int size = net.get_list_of_nodes().size();
//    std::vector<std::pair<unsigned long int, unsigned long int>> list = net.get_list_of_links();
//    UnionFind uf = UnionFind(size);
//    this->mean_component_sizes.push_back({1, 1, 0});
//    unsigned long int initial_number_of_links = list.size();
//    while (list.size() > 0) {
//        // Get random link of the network
//        unsigned long int position = Random::discrete_uniform(list.size());
//        std::pair<unsigned long int, unsigned long int> pair = list[position];
//        // Union the nodes of this link
//        uf.union_(pair.first, pair.second);
//        // Get the pair (number of nodes in the component, number of components with this number of nodes)
//        std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
//        // Mean value of the square of the number of nodes in each component
//        double Sc2 = 0;
//        double Tm = 0;
//        for (unsigned long int  i = 0;  i < size; i++) {
//            if(number_of_clusters_per_size[i]) {
//                Tm = (i+1);
//                Sc2 += static_cast<double>((i+1) * (i+1));
//            }
//        }
//        // Remove the link from the list of links
//        list.erase(list.begin() + static_cast<long int>(position));
//        double f = 1 - static_cast<double>(list.size())/initial_number_of_links;
//        this->mean_component_sizes.push_back({Sc2, Tm, f});
//    }
//    std::vector<unsigned long int> number_of_clusters_per_size = uf.get_size_of_components();
//    for(unsigned long int i=0; i < uf.get_max_comp(); i++){
//        std::cout<<i<<", "<<number_of_clusters_per_size[i]<<std::endl;
//    }
//    return this->mean_component_sizes;
//}
