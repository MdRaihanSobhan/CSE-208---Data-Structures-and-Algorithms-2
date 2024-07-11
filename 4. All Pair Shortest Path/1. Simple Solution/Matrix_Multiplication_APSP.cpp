
#include <iostream>
#include <vector>
#include<list>
#include<queue>
#include<map>
using namespace std;

int main(){
    int nodes,edges;
    cin>>nodes>>edges;
    int u,v;
    double w;
    double adjMatrix[nodes][nodes];
    double weights[nodes][nodes];
    
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            if(i==j){
                adjMatrix[i][j] = 0;
                weights[i][j]=0;
            }
            else{
                adjMatrix[i][j] = 1e9;
                weights[i][j]=1e9;
            }
                
        }
    }

    
    for(int i=0;i<edges;i++){
        cin>>u>>v>>w;
        u--; v--;
        weights[u][v]=w;
    }
    for(int l=0;l<nodes-2;l++){
        for(int i=0; i<nodes; i++){
            for(int j=0;j<nodes;j++){
                for(int k=0;k<nodes;k++){
                        adjMatrix[i][j] =
                        min(adjMatrix[i][j], adjMatrix[i][k] + weights[k][j]);
                }
            }

        }
    }
    cout<<"Shortest distance matrix"<<endl;
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            if (adjMatrix[i][j]== 1e9)
                cout<<"INF ";
            else
                cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    
    return 0;
}
