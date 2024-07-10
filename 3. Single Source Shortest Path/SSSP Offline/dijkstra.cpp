#include <iostream>
#include <vector>
#include<list>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;

class Edges{
    int src;
    int dest;
    double weight;
public:
    void setEdges(int src, int dest, double weight){
        this->src=src;
        this->dest=dest;
        this->weight= weight;
    }
    int getSrc(){ return this->src;}
    int getDest(){return this->dest;}
    double getWeight(){return this->weight;}
};

class Graph
{
    int V, E;
    list< pair<int, double> > *adj;
    map<int, bool> visited;
    map<int, list<int> > adjUW;
    
    
public:
    Edges* edge;
    
    Graph(int V, int E);
    
    void addEdge(int u, int v, double w);
    
    pair<vector<int>, double> dijkstra(int source, int destination);    
};



Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    adj = new list<pair<int , double> > [V];
    this->edge= new Edges[E];
}

void Graph::addEdge(int u, int v, double w)
{
    adj[u].push_back(make_pair(v, w));
}

pair<vector<int>, double> Graph::dijkstra(int source, int destination) {
    int par = source;
    vector<double> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<int> steps;
    parent[source] = source;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    pq.push(make_pair(0, par));
    key[par] = 0;

    while (!pq.empty()) {
        int vtx = pq.top().second;
        pq.pop();
        for (auto it : adj[vtx]) {
            int v = it.first;
            double weight = it.second;

            if (key[v] > key[vtx] + weight) {
                key[v] = key[vtx] + weight;
                parent[v] = vtx;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    for (int i = destination; i != source;) {
        steps.push_back(i);
        i = parent[i];
    }
    steps.push_back(source);
    reverse(steps.begin(), steps.end());

    return {steps, key[destination]};
}


void printSSSP(vector<int> steps){
    for(int i=0; i<steps.size();i++){
        if(i!=steps.size()-1)
            cout<<steps[i]<<" -> ";
        else
            cout<<steps[i]<<endl;
    }
}

int main(){
    int nodes,edges;
    cout<<"Enter the number of nodes and edges"<<endl;
    cin>>nodes>>edges;
    int u,v;
    double w;
    vector<int> SSSP_by_Bellman_Ford, SSSP_by_Dijkstra;
    pair<vector<int>, double> SSSP_by_Bellman_Ford_pair, SSSP_by_Dijkstra_pair;
    Graph graphVector(nodes,edges);
    
    cout<<"Enter the <source, destination , weight> for each edge"<<endl;
    for(int i=0;i<edges;i++){
        cin>>u>>v>>w;
        graphVector.edge[i].setEdges(u,v,w);
        graphVector.addEdge(u, v, w);
    }
    
    cout<<"Enter the source and destination for Single Source Shortest Path"<<endl;
    int src, dest;
    cin>>src>>dest;

    // Printing Dijkstra for SSSP
    SSSP_by_Dijkstra_pair = graphVector.dijkstra(src, dest);
    double cost_by_Dijkstra = SSSP_by_Dijkstra_pair.second;
    SSSP_by_Dijkstra = SSSP_by_Dijkstra_pair.first;
    cout<<"Shortest path cost from "<<src<<" to "<<dest<<" by Dijkstra's Algorithm : "<<cost_by_Dijkstra<<endl;
    cout<<"Steps of Shortest Path from "<<src<<" to "<<dest<<" by Dijkstra: ";
    printSSSP(SSSP_by_Dijkstra);


    return 0;
}
