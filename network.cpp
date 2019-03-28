#include "network.h"

bool Network::AddNode(Node n){
    this->nodeList.push_back(n);
    return true;
}

unsigned long int Network::Uniform(unsigned long int n){
    return static_cast<unsigned long int>(std::rand()) % n; // in (0, n - 1)
}

bool Network::AddLink(Node v, Node w){
    bool isLinked;
    isLinked = v.AddNeighbor(w);
    if(!isLinked){
        return false;
    }
    isLinked = w.AddNeighbor(v);
    if(!isLinked){
        return false;
    }
    return true;
}

void Network::SetNodeLists(unsigned long int numberOfNodes){
    std::vector<unsigned long int> rv;
    for (unsigned long int i = 0; i < numberOfNodes; i++) {
        unsigned long int n = rv[i];
        Node node = Node(n);
        // Add node to network
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

Network::Network(unsigned long int numberOfNodes, double degree){
    std::srand(unsigned(time(nullptr)));
    double N = static_cast<double>(numberOfNodes);
    ZipfGen zg = ZipfGen(N, degree);
    std::vector<unsigned long int> rv;
    rv = zg.RandomApproxMethod(numberOfNodes);
    SetNodeLists(numberOfNodes);
}


// I have to count to 100, give up and start again
// Andre Auto linking method
bool Network::RandomLinkAA(){
    SetAlgoList(this->nodeList.size());
    unsigned long int N = this->algoList.size();
    int counter = 0;
    while(N > 0){
        unsigned long int rand1 = Uniform(N);
        unsigned long int rand2 = Uniform(N);
        unsigned long int rnd1 = this->algoList[rand1];
        unsigned long int rnd2 = this->algoList[rand2];
        while((rand1 == rand2) && (nodeList[rnd1].IsConnected(nodeList[rnd2]))){
            counter++;
            rand1 = Uniform(N);
            rand2 = Uniform(N);
            rnd1 = this->algoList[rand1];
            rnd2 = this->algoList[rand2];
            if(counter >= 100){
                return false;
            }
        }
        AddLink(nodeList[rand1] , nodeList[rand2]);
        algoList[rand1] = algoList[N];
        algoList[rand2] = algoList[N-1];
        algoList.pop_back();
        algoList.pop_back();
        N -= 2;
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
    SetAlgoList(this->nodeList.size());
    std::sort(this->nodeList.rbegin(), this->nodeList.rend());
    unsigned long int N = this->algoList.size();
    while(N > 0){
        unsigned long int p1 = 0;
        unsigned long int p2 = GetNext(p1,0);
        unsigned long int val1 = this->algoList[p1];
        unsigned long int val2 = this->algoList[p2];
        while((val1 == val2) && (nodeList[val1].IsConnected(nodeList[val2]))){
            //Switch positions
            unsigned long int p3;
            p3 = GetNext(val2, p2);
            unsigned long int temp;
            temp = this->algoList[p2];
            this->algoList[p2] = this->algoList[p3];
            this->algoList[p3] = temp;
            val2 = this->algoList[p2];
        }
        AddLink(nodeList[val1] , nodeList[val2]);
        algoList.erase(algoList.begin());
        // Possible error point (cast from unsigned to signed)
        algoList.erase(algoList.begin() + static_cast<long int >(p2));
        N -= 2;
    }
    return true;
}
