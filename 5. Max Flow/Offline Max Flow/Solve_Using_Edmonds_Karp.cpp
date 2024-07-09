#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
#define limit 100
int capacityVector[limit][limit];
int graphVector[limit][limit];
vector<int> adj[limit];
int parent[limit];
int newPath[limit];

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

int bfs(int begin, int end)//breadth first search
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
    int nodes;
    
    vector<string> teams;
    cin>>nodes;

    int matches = nodes*(nodes-1)/2;
    
    int source, sink;
    
    string teamName;
    
    int givenMatrix[nodes][nodes];
    int winsVector[nodes];
    int leftVector[nodes];
    
    for(int i=0;i<nodes;i++){
        int wins, loses, left;
        
        cin>>teamName>>wins>>loses>>left;
        teams.push_back(teamName);
        winsVector[i]= wins;
        leftVector[i]= left;
        for(int j=0;j<nodes;j++){
            int temp;
            cin>>temp;
            givenMatrix[i][j]= temp;
        }
    }
    
    source = nodes+matches;
    sink = source+1;
    
    for(int testing = 0 ; testing<nodes; testing++ ){
        
        int currentNode= 0;
        int tempFlow=0;
        for(int i=0; i<nodes; i++){
            if(i==testing) continue;
            for(int j=i+1;j<nodes; j++){
                if(j==testing) continue;
                
                int from = source;
                int to = currentNode;
                int capacity = givenMatrix[i][j];
                
                addEdge(from,to,capacity);
                
                
                tempFlow+=capacity;
                
                from = currentNode;
                to = matches + i;
                capacity = INT_MAX;
                
                addEdge(from,to,capacity);
                
                to = matches + j;
                
                addEdge(from,to,capacity);
                currentNode++;
                
            }
            
            int from= matches+i;
            int to = sink;
            int capacity= winsVector[testing]+ leftVector[testing]- winsVector[i];
            
            addEdge(from,to,capacity);
            
        }

        
        int maxFlow = EdmondsKarp(source, sink);
        
        if(maxFlow!=tempFlow){
            cout<<endl<<teams[testing] << " is Eliminated"<<endl;
            cout<<"They can win at most "<<winsVector[testing]<<" + "<<leftVector[testing]<<" = " <<winsVector[testing]+leftVector[testing]<<" matches"<<endl;
        }
        
      // cout<<"Max Flow is:"<<maxFlow<<endl;
       // cout<<"TempFLow is : "<<tempFlow<<endl;
        
        
        renewGlobals();
        
    }
}
