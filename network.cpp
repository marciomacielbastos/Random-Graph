#include "network.h"

bool Network::AddNode(Node n){
    this->nodeList.push_back(n);
    return true;
}


bool Network::AddLink(Node *v, Node *w){
    bool isLinked;
    isLinked = v->AddNeighbor(*w);
    if(!isLinked){
        return false;
    }
    w->AddNeighbor(*v);
    this->linkCounter++;
    return true;
}

void Network::SetNodeLists(unsigned long numberOfNodes){
    std::vector<unsigned long> rv = this->distribution->Rand(numberOfNodes);
    for (auto x : rv) {
        Node node = Node(x);
        AddNode(node);
    }
}

void Network::SetAlgoList(unsigned long numberOfNodes){
    for (unsigned long int i = 0; i < numberOfNodes; i++) {
        // Create a list of degree-repeated node id
        std::vector<unsigned long int> links(nodeList[i].GedDegree(), nodeList[i].GetId());
        // Append the lists cited above to create the network through Andre Auto algorithm
        this->algoList.insert(algoList.end(), links.begin(), links.end());
    }
}

//It must receive a random distribution already setted up.
Network::Network(unsigned long int numberOfNodes, Random *rd){
    this->distribution = rd;
    SetNodeLists(numberOfNodes);
}

// Andre Auto linking method
// I have to count to 100, give up and start again
bool Network::RandomLinkAA(){
    SetAlgoList(this->nodeList.size());
    unsigned long int N = this->algoList.size();
    int counter = 0;
    while(N > 1){
        unsigned long int rand1 =  distribution->DiscreteUniform(0, N);
        unsigned long int rand2 =  distribution->DiscreteUniform(0, N);
        unsigned long int rnd1 = this->algoList[rand1];
        unsigned long int rnd2 = this->algoList[rand2];
        while((rnd1 == rnd2) || (nodeList[rnd1].IsConnected(nodeList[rnd2]))){
            counter++;
            rand1 =  distribution->DiscreteUniform(N);
            rand2 =  distribution->DiscreteUniform(N);
            rnd1 = this->algoList[rand1];
            rnd2 = this->algoList[rand2];
            if(counter >= 100){
                return false;
            }
        }
        AddLink(&nodeList[rnd1] , &nodeList[rnd2]);
        algoList[rand1] = algoList[N-1];
        algoList[rand2] = algoList[N-2];
        if(algoList.size() > 1) {
            algoList.pop_back();
            N--;
        }
        if(algoList.size() > 1) {
            algoList.pop_back();
            N--;
        }
    }
    return true;
}

unsigned long int Network::GetNext(unsigned long int head, unsigned long int it){
    while(head == algoList[it]){
        it++;
    }
    return it;
}

// Nuno linking method
bool Network::RandomLinkNuno(){
    std::sort(this->nodeList.rbegin(), this->nodeList.rend());
    SetAlgoList(this->nodeList.size());
    unsigned long int N = this->algoList.size();
//    Verify if the algoList size is even and reduce the degreen of the less connecter node by one
//    if(N % 2){
//        unsigned long int p = this->algoList[this->algoList.size() - 1];
//        nodeList[p].SetDegree(nodeList[p].GedDegree() - 1);
//        this->algoList.pop_back();
//    }
    while(N > 1){
        unsigned long int p1 = 0;
        unsigned long int p2 = 0;
        unsigned long int val1 = this->algoList[p1];
        unsigned long int val2 = val1;
        int count = 100;
        while ((val1 == val2) || (nodeList[val1].IsConnected(nodeList[val2]))){
            p2 =  distribution->DiscreteUniform(GetNext(p1,0), N);
            val2 = this->algoList[p2];
            if(count <= 0){
                count--;
                return false;
            }
        }
        AddLink(&nodeList[val1] , &nodeList[val2]);
        // Possible error point (cast from unsigned to signed)
        algoList.erase(algoList.begin() + static_cast<long int >(p2));
        algoList.erase(algoList.begin());
        N -= 2;
    }
    return true;
}

std::vector<Node> Network::GetNodeList(){
    return this->nodeList;
}

long int Network::RandomPop(unsigned long int node){
    unsigned long int adj_id = this->nodeList[node].GetAdjacencySize();
    if(adj_id > 0){
        long int new_node = this->nodeList[node].RemoveLink(Random::DiscreteUniform(adj_id));
        this->nodeList[static_cast<unsigned long int>(new_node)].RemoveLink(nodeList[static_cast<unsigned long int>(new_node)].GetPosition(adj_id));
        this->linkCounter--;
        return new_node;
    }
    else {
        return -1;
    }
}

unsigned long int Network::GetLinkCounter(){
    return this->linkCounter;
}
