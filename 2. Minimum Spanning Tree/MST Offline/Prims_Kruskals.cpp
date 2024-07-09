
#include <iostream>
#include <vector>
#include<list>
#include<queue>
using namespace std;



class Graph
{
    int V;
    list< pair<int, int> > *adj;

public:
    Graph(int V);
    
    void addedges(int u, int v, double w);
    
    int primsAlgo();
};


Graph::Graph(int V)
{
    this->V = V;
    adj = new list<pair<int, int> > [V];
}

void Graph::addedges(int u, int v, double w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

int Graph::primsAlgo()
{
    double ans =0;
    

    int par = 0;
    vector<double> key(V, INT_MAX-0.00001);
    priority_queue< pair<double, int>, vector <pair<double, int>> , greater<pair<double, int>> > pq;
    
    vector<int> parent(V, -1);
    vector<bool> MSTvector(V, false);
    pq.push(make_pair(0.0, par));
    key[par] = 0;

    while (!pq.empty())
    {
       
        int vtx = pq.top().second;
        
        pq.pop();
        
       
        if(MSTvector[vtx] == true){
            continue;
        }
    
        MSTvector[vtx] = true;
        
        for(auto it : adj[vtx]){
            
            int v = it.first;
            int weight = it.second;

            
            if (MSTvector[v] == false && key[v] > weight)
            {
                key[v] = weight;
                // MSTvector[v]= true;
                pq.push(make_pair(key[v], v));
                parent[v] = vtx;
            }
        }
        
    }
    ans=0;
    for(int i=1 ;i<V;i++){
        ans+=key[i];
       // cout<<key[i]<<" ";
    }
    //cout<<ans<<endl;
    cout<<"Cost of the minimum spanning tree : "<<ans<<endl;
    
    cout<<"List of edges selected by Prim's : { ";
    for (int i = 1; i < V; ++i)
        printf("(%d, %d), ", parent[i], i);
    cout<<"}"<<endl;
    return  ans;
}




class KruskalsGraph{
private:
    int v;
    pair<int,int > edges;
    vector<pair<pair<int ,int>,int>> MST;
    vector<pair<pair<int ,int>,int>> graphVector;
    int *par;


public:

    void addEdge(int u , int v, double w){
        graphVector.push_back(make_pair(pair<int,int>(u,v),w));
    }
    KruskalsGraph(int v){
        par = new int [v];

        for(int i = 0; i<v ; i++){
            par [i] =i;
        }
        graphVector.clear();
        MST.clear();

    }
    
    void union_set(int u, int v){
        par [v] = par [u];
    }
    
    int find_set(int i ){
        if(par[i] == i) return i;
        else return find_set(par[i]);
    }
    
    void KruskalsAlgo();
    void printMSTbyKruskal();
};



void KruskalsGraph ::  printMSTbyKruskal() {
    double cost = 0;
    for (int i = 0; i < MST.size(); i++) {
        cost+=MST[i].second;
    }
    // cout<<"Cost of the minimum spanning tree: "<<cost<<endl;
    
    cout<<"List of edges selected by kruskal's:";
    int sizeMST = MST.size();
    cout<<"{";
    for(int i =0; i<sizeMST; i++){
        cout<<"("<<MST[i].first.first<<",";
        cout<<MST[i].first.second<<")";
        
        if(i<sizeMST-1) cout<<",";
    }
    cout<<"}";
    cout<<endl;
}

bool sortbysec(pair<pair<int,int>,int> a,
                       pair<pair<int,int>,int> b)
{
    return (a.second < b.second);
}

void KruskalsGraph :: KruskalsAlgo(){
    int u ,v;
    sort(graphVector.begin(),graphVector.end(), sortbysec);
    int gVsize= graphVector.size();
    for(int i = 0; i<gVsize; i++){
        u = find_set(graphVector[i].first.first);
        v = find_set(graphVector[i].first.second);

        if(u!=v){
            MST.push_back(graphVector[i]);
            union_set(v,u);
        }
    }
}





int main()
{
    
    freopen("mst.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
     
    int nodes,edges;
    cin>>nodes>>edges;
    int u,v;
    double w;
    Graph graphVector(nodes);
    KruskalsGraph kruskalsGraphVector(nodes);
    for(int i=0;i<edges;i++){
        cin>>u>>v>>w;
        graphVector.addedges(u, v, w);
        kruskalsGraphVector.addEdge(u, v, w);
    }
    
    int netWeight= graphVector.primsAlgo();
   // cout<<"Cost of the minimum spanning tree : "<<netWeight<<endl;
    
    kruskalsGraphVector.KruskalsAlgo();
    kruskalsGraphVector.printMSTbyKruskal();
    
    
    return 0;
}


