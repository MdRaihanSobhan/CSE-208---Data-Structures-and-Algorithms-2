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
    
    pair<vector<int>, double> bellman_ford(int source, int destination);
    bool doesNegativeCycleExist(int source);
    
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





pair<vector<int>, double> Graph::bellman_ford(int source, int destination) {
    vector<int> parent(V, -1);
    vector<int> steps;
    parent[source] = source;

    vector<double> dist(V, INT_MAX);
    dist[source] = 0;

    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edge[j].getSrc();
            int v = edge[j].getDest();
            double weight = edge[j].getWeight();

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edge[i].getSrc();
        int v = edge[i].getDest();
        double weight = edge[i].getWeight();
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            return {{-1}, -1};
        }
    }

    for (int i = destination; i != source;) {
        steps.push_back(i);
        i = parent[i];
    }
    steps.push_back(source);
    reverse(steps.begin(), steps.end());

    return {steps, dist[destination]};
}

bool Graph:: doesNegativeCycleExist(int source){
    // using bellman_ford to check if negative cycle exists
    pair<vector<int>, double> SSSP_by_Bellman_Ford_pair;
    SSSP_by_Bellman_Ford_pair = bellman_ford(source, source);
    vector<int> SSSP_by_Bellman_Ford = SSSP_by_Bellman_Ford_pair.first;
    if(SSSP_by_Bellman_Ford[0]==-1){
        return true;
    }
    return false;

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
    
    // printing Bellman Ford for SSSP
    SSSP_by_Bellman_Ford_pair = graphVector.bellman_ford(src, dest);
    SSSP_by_Bellman_Ford = SSSP_by_Bellman_Ford_pair.first;
    double cost_by_Bellman_Ford = SSSP_by_Bellman_Ford_pair.second;

    if(SSSP_by_Bellman_Ford[0]==-1){
        cout<<"The graph contains a negative cycle."<<endl;
    }
    else{
        cout<<"The graph does not contain a negative cycle."<<endl;
        cout<<"Shortest path cost from "<<src<<" to "<<dest<<" by Bellman Ford's Algorithm : "<<cost_by_Bellman_Ford<<endl;

        cout<<"Steps of Shortest Path from "<<src<<" to "<<dest<<" by Bellman Ford: ";
        printSSSP(SSSP_by_Bellman_Ford);
    }



    return 0;
}
