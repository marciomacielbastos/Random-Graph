#include "percolation.h"

Percolation::Percolation(){

}

Percolation::Percolation(unsigned int freq_of_reg){
    std::vector<std::pair<double, double>> mean_cluster_size(freq_of_reg, std::pair<double, double>(0, 1));
    std::vector<std::pair<double, double>> biggest_component(freq_of_reg, std::pair<double, double>(0, 1));
    this->mean_cluster_size = mean_cluster_size;
    this->biggest_component = biggest_component;
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
    std::cout << "] " << int(progress * 100.0) << " %  \r";
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

void Percolation::write_component_stats(const std::string &filename){
    write_biggest_component(filename, this->biggest_component[0].first, this->biggest_component[0].second);
    write_mean_cluster_size(filename, this->mean_cluster_size[0].first, this->mean_cluster_size[0].second);
    for(unsigned int i=1; i < this->biggest_component.size(); i++){
        write_biggest_component(filename, this->biggest_component[i].first, this->biggest_component[i].second, true);
        write_mean_cluster_size(filename, this->mean_cluster_size[i].first, this->mean_cluster_size[i].second, true);
    }
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
    /* "freq_of_reg" represents how manny ticks do you want on your percolation record, if your network
       is too big its better to reduce this A LOT! (you will execute as many file outputs as this value) */

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

std::vector<std::vector<std::vector<double>>> Percolation::mount_component(Rede rd, unsigned int freq_of_reg){
    /* "freq_of_reg" represents how manny ticks do you want on your percolation record, if your network
       is too big its better to reduce this A LOT! (you will execute as many file outputs as this value) */
    std::vector<std::pair<unsigned long int, unsigned long int>> list = rd.get_list_of_links();

    std::vector<std::vector<std::vector<double>>> output;
    std::vector<std::vector<double>> mean_cluster_size(freq_of_reg + 1, {0, 1});
    std::vector<std::vector<double>> biggest_component(freq_of_reg + 1, {0, 1});
    output.push_back(mean_cluster_size);
    output.push_back(biggest_component);

    double total = static_cast<double>(list.size());
    UnionFind uf = UnionFind(rd.get_number_of_nodes());

    double progress = 0.0;
    progress_bar(progress);

    double k = 1 / static_cast<double>(freq_of_reg);
    unsigned int i = 1;
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
            output[0][i][0] = progress;
            output[0][i][1] = size / total_numb_of_clusters;
            output[1][i][0] = progress;
            output[1][i][1] = uf.get_st_biggest().second;
            k += 1 / static_cast<double>(freq_of_reg);
            i++;
        }
        /***********************************************************************/
        progress_bar(progress);
    }
    std::cout<<std::endl;
    return output;
}

//void Percolation::mount_component_mean(Rede rd, unsigned int freq_of_reg){
//    std::vector<std::vector<std::pair<double, double>>> input = mount_component(rd, freq_of_reg);
//    for(unsigned int i = 1; i < freq_of_reg; i++){
//        this->mean_cluster_size[i].first += input[0][i].first;
//        this->biggest_component[i].first += input[1][i].first;
//        this->mean_cluster_size[i].second += input[0][i].second;
//        this->biggest_component[i].second += input[1][i].second;
//        int a = 0;
//    }
//    int a = 0;
//}


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
