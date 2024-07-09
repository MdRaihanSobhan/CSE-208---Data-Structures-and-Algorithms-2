
#include <iostream>
#include <vector>
#include<list>
#include<queue>
using namespace std;

class Graph
{
    int V;
    int E;
    list< pair<int, int> > *adj;
    

public:
    Graph(int V, int E);
    
    void addedges(int u, int v, int w);
    
    int dijkstra(int source, int destination);
    int bellman_ford(int source, int destination);
};
/*
class Edges{
    int src;
    int dest;
    int weight;
public:
    void setEdges(int src, int dest, int weight){
        this->src=src;
        this->dest=dest;
        this->weight= weight;
    }
};
*/

Graph::Graph(int V, int E)
{
    this->V = V;
    this-> E= E;
    adj = new list<pair<int, int> > [V];
}

void Graph::addedges(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
}

int Graph::dijkstra(int source, int destination)
{
    double ans = 0;
    

    int par = source;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<int> steps;
    parent[source]=source;
    
    priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;
    
    pq.push(make_pair(0, par));
    key[par] = 0;

    while (!pq.empty())
    {
       
        int vtx = pq.top().second;
        
        pq.pop();
        for(auto it : adj[vtx]){
            
            int v = it.first;
            int weight = it.second;

            
            if (key[v] > key[vtx]+ weight)
            {
                key[v] = key[vtx] + weight;
                parent[v]= vtx;
                pq.push(make_pair(key[v], v));
                
            }
        }
        
    }
    ans=0;
    for(int i=0 ;i<V;i++){
        ans+=key[i];
        //cout<<key[i]<<" ";
    }
    // cout<<ans<<endl;
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
        cout<<steps[i]<<" ->";
        else
            cout<<steps[i];
    }
    cout<<endl;
    
    return  key[destination];
}



int Graph:: bellman_ford(int source, int destination){
    
    vector<int>edgs;
    vector<int> dist(V, INT_MAX);
    dist[source]=0;
    int adjMatrix[V][V];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            adjMatrix[i][j]=0;
        }
    }
    
    for(int i=0; i<V; i++){
        for(auto it : adj[i]){
            int j= it.first;
            int w= it.second;
            adjMatrix[i][j]=w;
        }
    }
    
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(1){
                int u= i;
                int v= j;
                int w= adjMatrix[i][j];
                if(dist[u]!=INT_MAX && dist[u]+w < dist[v]){
                    dist[v]=dist[u]+w;
                    cout<<dist[v]<<" ";
                }
            }
        }
    }
    cout<<endl;
    cout<<dist[destination]<<endl;
    return dist[destination];
    
}

int main()
{
    int nodes,edges;
    cin>>nodes>>edges;
    int u,v;
    int w;
    Graph graphVector(nodes, edges);
    
    for(int i=0;i<edges;i++){
        cin>>u>>v>>w;
        graphVector.addedges(u, v, w);
    }
    int src, dest;
    cin>>src>>dest;
    int cost= graphVector.dijkstra(src, dest);
    cout<<"Shortest path cost : "<<cost<<endl;
    int bellCost= graphVector.bellman_ford(src, dest);
    cout<<"Shortest path cost by Bellman_ford : "<<bellCost<<endl;
    
    return 0;
}

