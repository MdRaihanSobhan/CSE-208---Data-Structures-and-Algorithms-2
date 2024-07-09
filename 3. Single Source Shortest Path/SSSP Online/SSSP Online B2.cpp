// Bellman_Ford Algorithm

#include <iostream>
#include <vector>
#include<list>
#include<queue>
#include <math.h>
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
    
public:
    Edges* edge;
    Graph(int V, int E);
    double bellman_ford(int source, int destination);
};



Graph::Graph(int V, int E)
{
    this->V = V;
    this->E= E;
    adj = new list<pair<int, double> > [V];
    this->edge= new Edges[E];
}

double Graph:: bellman_ford(int source, int destination){
    
    
    vector<int> parent(V, -1);
    vector<int> steps;
    parent[source]=source;
    
    vector<double> dist(V, INT_MAX);
    dist[source]=0;
    
    for(int i=1; i<V; i++){
        for(int j=0; j<E; j++){
            int u = edge[j].getSrc();
            int v= edge[j].getDest();
            double weight= edge[j].getWeight();
            
            if(dist[u]!= INT_MAX && dist[u]+weight< dist[v]){
                dist[v]= dist[u]+weight;
                parent[v]= u;
            }
            
        }
    }
    
    for(int i=0; i<E; i++){
        int u = edge[i].getSrc();
        int v = edge[i].getDest();
        double weight= edge[i].getWeight();
        if(dist[u]!= INT_MAX && dist[u]+weight< dist[v]){
            return -1;
        }
        
    }
    
    cout<<"Most reliable path score: "<<pow(2.718281828,0-dist[destination])<<endl;
    
    
    for(int i=destination; i!=source;){
        // cout<<i<<" ";
        steps.push_back(i);
        i= parent[i];
    }
    steps.push_back(source);
    // cout<<endl;
    reverse(steps.begin(),steps.end());
    
    
    for(int i=0;i<steps.size();i++){
        if(i!=steps.size()-1)
        cout<<steps[i]<<" -> ";
        else
            cout<<steps[i];
    }
    cout<<endl;
    
    return pow(2.718281828,0-dist[destination]);
    
}

int main(){
    int nodes,edges;
    cin>>nodes>>edges;
    int u,v;
    double w;
    Graph graphVector(nodes,edges);
    
    for(int i=0;i<edges;i++){
        cin>>u>>v>>w;
        
        graphVector.edge[i].setEdges(u,v,-log(w));
    }
    int src, dest;
    cin>>src>>dest;
    
    graphVector.bellman_ford(src, dest);
    // cout<<"Shortest path cost : "<<cost<<endl;
    
    return 0;
}
