//
//  main.cpp
//  1905095_MaxFlow_Online
//
//  Created by Md. Raihan Sobhan on 22/6/22.
//

#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
#define limit 1000
int capacityVector[limit][limit];
int graphVector[limit][limit];
vector<int> adj[limit];
int parent[limit];
int newPath[limit];
vector<int> culprits;
void addEdge(int from, int to, int capacity){
    capacityVector[from][to] = capacity;
    adj[from].push_back(to);
    adj[to].push_back(from);
}
void renewGlobals(){
    for(int i=0;i<limit; i++){
        adj[i].clear();
        parent[i]=0;
        newPath[i]=0;
        for(int j=0;j<limit;j++){
            capacityVector[i][j]=0;
            graphVector[i][j]= 0;
        }
    }
}

int bfs(int begin, int end)
{
    for(int i=0; i<sizeof(parent); i++){
        parent[i]=-1;
    }
    for(int i=0;i<sizeof(newPath); i++){
        newPath[i]=0;
    }
   queue<int> q;
   q.push(begin);
    parent[begin] = -1;
    newPath[begin] = limit;
   while(q.empty()==false)
   {
      int newNode = q.front();
      q.pop();
      for(int i=0; i<adj[newNode].size(); i++)
      {
         int v = adj[newNode][i];
         if(parent[v] == -1)
         {
            int temp = capacityVector[newNode][v] - graphVector[newNode][v];
            if(temp>0)
            {
                // ekhane node ta record kora lagbe
                culprits.push_back(v);
                parent[v] = newNode;
                newPath[v] = min(newPath[newNode], temp);
               if(v == end)
               {
                  return newPath[end];
               }
               q.push(v);
            }
         }
      }
   }
   return 0;
}




int EdmondsKarp(int source, int sink)
{
       int maxFlow = 0;
       while(true)
       {
           int current = sink;
           int flo = bfs(source, sink);
           maxFlow += flo;
           if(flo==0){
               break;
           }
           while(current != source){
               int previous = parent[current];
               graphVector[previous][current] += flo;
               graphVector[current][previous] -= flo;
               current = previous;
           }
       }
    return maxFlow;
}
int main()
{
    int t;
    
    cin>>t;
    while (t--) {
        
        int N, M;
        int from, to, capacity;
        vector<string> sizes;
        string st1,st2;
        cin>>N>>M;
        int source=0;
        for(int i=1; i<=M;i++){
            from = source;
            to= i;
            capacity=1;
            addEdge(from, to, capacity);
            
            cin>>st1>>st2;
            if(st1=="XXL"){
                from = source;
                to= 1;
                capacity=1;
                addEdge(from, to, capacity);
                
            }
        }
        
        
        
        for(int i=0;i<M;i++){
            cin>>st1>>st2;
            
            
            
        }
    }
}
