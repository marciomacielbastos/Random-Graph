#include "network.h"

//It must receive a random distribution already setted up.
Network::Network(unsigned long int numberOfNodes, Random *rd){
    this->is_sorted = false;
    this->distribution = rd;
    set_list_of_nodes(numberOfNodes);
}

Network::Network(std::vector<unsigned long int> &degrees, unsigned int num_threads){
    unsigned long int size = degrees.size();
    this->is_sorted = false;
//    std::vector<unsigned long int> vector_sum_of_degrees(num_threads + 1, 0);

//    unsigned long int sum_of_degrees = get_sum_of_degrees(std::ref(degrees), std::ref(vector_sum_of_degrees), num_threads);

    { std::vector<Node> node_list(size, Node());
      this->list_of_nodes = node_list; }
//    { std::vector<unsigned long int> algorithm_list(sum_of_degrees, 0);
//      this->algorithm_list = algorithm_list; }

    std::thread t[num_threads];
    unsigned long int begin = 0;
    unsigned long int end = 0;
    for (unsigned int i = 0; i < num_threads; ++i) {
        if(i < size % num_threads){
            end += size / (num_threads + 1) + 1;
        }
        else {
            end += size / (num_threads + 1);
        }
        t[i] = (std::thread(&Network::set_list_of_nodes_t, this, std::ref(degrees), begin, end));
        begin = end;
    }
    set_list_of_nodes_t(std::ref(degrees), begin, degrees.size());
    for (unsigned int i = 0; i < num_threads; ++i){
        t[i].join();
    }
}

//Add a node to the network
bool Network::add_node(Node n){
    this->list_of_nodes.push_back(n);
    return true;
}

std::vector<std::pair<unsigned long int, unsigned long int>> Network::get_list_of_links(){
    std::vector<std::pair<unsigned long int, unsigned long int>> list;
    for (unsigned long int i = 0; i < this->list_of_nodes.size(); i++) {
        for (unsigned long int j = 0; j < this->list_of_nodes[i].get_adjacency_list_size() ; j++) {
            unsigned long int adjacent_id = this->list_of_nodes[i].get_adjacency_list()[j];
            if(i < adjacent_id){
                std::pair<unsigned long int, unsigned long int> pair (i, adjacent_id);
                list.push_back(pair);
            }
        }
    }
    return list;
}

std::map<unsigned long int, unsigned long int> Network::get_map_id_order(){
    sort_list_of_nodes();
    std::map<unsigned long int, unsigned long int> map_id_order;
    unsigned long int counter = 0;
    for (auto node : list_of_nodes){
        map_id_order.insert (std::pair<unsigned long int ,unsigned long int>(counter, node.get_id()));
        counter++;
    }
    return map_id_order;
}

//Return the list of nodes in the network
std::vector<Node> Network::get_list_of_nodes(){
    return this->list_of_nodes;
}

unsigned long int Network::get_next_value_of_algorithm_list(unsigned long int head, unsigned long int it){
    while(head == algorithm_list[it]){
        it++;
    }
    return it;
}

//Keep here for future parallelization
unsigned long int Network::get_sum_of_degrees(const std::vector<unsigned long int> &  degrees, std::vector<unsigned long int> &  vector_sum_of_degrees, unsigned long int num_threads){
    unsigned long int size = degrees.size();
    unsigned long int sum_of_degrees = 0;
    unsigned long int begin = 0;
    unsigned long int end = 0;
    unsigned long int remainder = size % (num_threads + 1);
    for (unsigned int i = 0; i < size; ++i) {
        if(i >= end){
            vector_sum_of_degrees[begin] = sum_of_degrees;
            begin++;
            if(remainder) {
                end += size / (num_threads + 1) + 1;
                remainder--;
            } else{
                end += size / (num_threads + 1);
            }
        }
        sum_of_degrees += degrees[i];
    }
    vector_sum_of_degrees[begin] = sum_of_degrees;
    return sum_of_degrees;
}



//Add a link to the network, return false if the nodes are already linked
bool Network::link(Node *v, Node *w){
    bool isLinked;
    isLinked = v->add_neighbor(*w);
    if(!isLinked){
        return false;
    }
    w->add_neighbor(*v);
    return true;
}

// Andre Auto linking method
// I have to count to 100, give up and start again
bool Network::random_link_AA_algorithm(){
    set_algotithm_list();
    unsigned long int N = this->algorithm_list.size();
    int counter = 0;
    while(N > 1){
        unsigned long int rand1 =  distribution->DiscreteUniform(0, N);
        unsigned long int rand2 =  distribution->DiscreteUniform(0, N);
        unsigned long int rnd1 = this->algorithm_list[rand1];
        unsigned long int rnd2 = this->algorithm_list[rand2];
        while((rnd1 == rnd2) || (list_of_nodes[rnd1].is_connected(list_of_nodes[rnd2]))){
            if(counter >= 100){
                return false;
            }
            rand1 =  distribution->DiscreteUniform(N);
            rand2 =  distribution->DiscreteUniform(N);
            rnd1 = this->algorithm_list[rand1];
            rnd2 = this->algorithm_list[rand2];
            counter++;
        }
        link(&list_of_nodes[rnd1] , &list_of_nodes[rnd2]);
        algorithm_list[rand1] = algorithm_list[N-1];
        algorithm_list[rand2] = algorithm_list[N-2];
        if(algorithm_list.size() > 1) {
            algorithm_list.pop_back();
            N--;
        }
        if(algorithm_list.size() > 1) {
            algorithm_list.pop_back();
            N--;
        }
    }
    return true;
}

// Nuno linking method
bool Network::RandomLinkNuno(){
    sort_list_of_nodes();
    set_algotithm_list();
    unsigned long int N = this->algorithm_list.size();
//    Verify if the algoList size is even and reduce the degreen of the less connecter node by one
//    if(N % 2){
//        unsigned long int p = this->algoList[this->algoList.size() - 1];
//        nodeList[p].SetDegree(nodeList[p].GedDegree() - 1);
//        this->algoList.pop_back();
//    }
    while(N > 1){
        unsigned long int p1 = 0;
        unsigned long int p2 = 0;
        unsigned long int val1 = this->algorithm_list[p1];
        unsigned long int val2 = val1;
        int count = 100;
        while ((val1 == val2) || (list_of_nodes[val1].is_connected(list_of_nodes[val2]))){
            p2 =  distribution->DiscreteUniform(get_next_value_of_algorithm_list(p1,0), N);
            val2 = this->algorithm_list[p2];
            if(count <= 0){
                count--;
                return false;
            }
        }
        link(&list_of_nodes[val1] , &list_of_nodes[val2]);
        // Possible error point (cast from unsigned to signed)
        algorithm_list.erase(algorithm_list.begin() + static_cast<long int >(p2));
        algorithm_list.erase(algorithm_list.begin());
        N -= 2;
    }
    return true;
}


void Network::set_algotithm_list(){
    unsigned long int number_of_nodes = this->list_of_nodes.size();
    for (unsigned long int i = 0; i < number_of_nodes; i++) {
        // Create a list of degree-repeated node id
        std::vector<unsigned long int> links(this->list_of_nodes[i].ged_degree(), this->list_of_nodes[i].get_id());
        // Append the lists cited above to create the network through Andre Auto algorithm
        this->algorithm_list.insert(algorithm_list.end(), links.begin(), links.end());
    }
}

void Network::set_list_of_nodes(unsigned long number_of_nodes){
        std::vector<unsigned long> rv = this->distribution->random(number_of_nodes);
        for (auto x : rv) {
            Node node = Node(x);
            add_node(node);
        }
}

void Network::set_list_of_nodes_t(std::vector<unsigned long> &degrees, unsigned long begin, unsigned long end){
    for (unsigned long int i = begin; i < end; ++i) {
        this->list_of_nodes[i].set_id(i);
        this->list_of_nodes[i].set_degree(degrees[i]);
    }
}

void Network::sort_list_of_nodes(){
    if(this->is_sorted){
        return;
    } else{
        std::sort(this->list_of_nodes.rbegin(), this->list_of_nodes.rend());
        this->is_sorted = true;
    }
}
