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
    std::string filename("/home/marcio/pCloudDrive//Physics/Thesis/Andre/Results/Mean/Mean_cluster_size_");
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
    std::string filename("/home/marcio/pCloudDrive//Physics/Thesis/Andre/Results/Mean/Biggest_component_");
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

void Percolation::molloy_reed(bool &is_already_added, double &molloy_reed_k, double &molloy_reed_k2, const unsigned long int degree, double &m){
//    if(!is_already_added){
//        is_already_added = true;
//        molloy_reed_k *= m;
//        molloy_reed_k2 *= m;
//        m++;
//        molloy_reed_k += static_cast<double>(degree);
//        molloy_reed_k /= m;
//        molloy_reed_k2 += (static_cast<double>(degree) * static_cast<double>(degree));
//        molloy_reed_k2 /=m;
//    }

}

std::vector<std::vector<double>> Percolation::mount_component(Rede rd, unsigned long int freq_of_reg){
    /* "freq_of_reg" represents how manny ticks do you want on your percolation record, if your network
       is too big its better to reduce this A LOT! (you will execute as many file writing as this value) */
    std::vector<std::pair<unsigned long int, unsigned long int>> list = rd.get_list_of_links();

    double total = static_cast<double>(list.size());
    UnionFind uf = UnionFind(rd.get_number_of_nodes());

    std::vector<std::vector<double>> output(std::min(freq_of_reg, static_cast<unsigned long int>(total)) + 1, {0, 1});
    std::vector<unsigned long int> degrees(rd.get_number_of_nodes(), 0);

//    std::vector<bool> list_of_nodes (rd.get_number_of_nodes(), false);

    double sum_of_squared_k = 0;
    double Nl = 0;
    double molloy_reed_coef = 0;
    double pc = -1;
    unsigned long int biggest_in_pc;
    double A;
    double B;
    double progress = 0.0;

    progress_bar(progress);

    double k = 1 / static_cast<double>(std::min(freq_of_reg, static_cast<unsigned long int>(total)));

    unsigned int i = 1;
    //Feed the algorithm with edges until there ain't no edges in the list
    while (list.size() > 0) {
        progress += 1 / total;
        std::pair<unsigned long int, unsigned long int> pair = list[list.size() - 1];
        // Union the nodes of this link
        uf.union_(pair.first, pair.second);
        Nl += 1;
        sum_of_squared_k += static_cast<double>(2 * (degrees[pair.first] + degrees[pair.second] + 1));
        A += 2 *(degrees[pair.first] + degrees[pair.second] + 2);
        B += 2;
        degrees[pair.first]++;
        degrees[pair.second]++;
//        molloy_reed_coef = sum_of_squared_k / (2 * Nl);
        molloy_reed_coef = A / B;

        // Check if the fraction of nodes added reach the Molloy-Reed criterion limit [<k²>/<k> = 2]
        // DO NOT COMPARE FLOAT NUMBERS AS USUAL!!!!
        if(std::abs(molloy_reed_coef - 2) <= 0.05){
            pc = progress;
            biggest_in_pc = uf.get_st_biggest().second;
        }

        // Remove the link from the list of links
        list.pop_back();

        /**************************************************************************/
        /*                                                                        */
        /*                      Percolation data computation                      */
        /*                                                                        */
        /**************************************************************************/
        if((progress >= k) || ((list.size()) == 0)){
            output[i][0] = k;
            output[i][1] = uf.get_st_biggest().second;
            k += 1 / static_cast<double>(std::min(freq_of_reg, static_cast<unsigned long int>(total)));
            i++;
        }
        /***********************************************************************/
        progress_bar(progress);
    }
    //Add the critical fraction of added nodes and biggest component in [<k²>/<k> = 2] to output
    output.push_back({pc, biggest_in_pc});
    std::cout<<std::endl;
    return output;
}
