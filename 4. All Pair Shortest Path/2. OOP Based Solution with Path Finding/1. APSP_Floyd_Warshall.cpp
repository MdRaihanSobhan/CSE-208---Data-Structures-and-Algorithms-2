#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;


class Graph {
    int V, E;

public:
    vector<vector<double>> adjMatrix;
    vector<vector<int>> successor;

    Graph(int V, int E);

    void addEdge(int u, int v, double w);
    vector<vector<double>> floydWarshall();
    void setSuccessors(vector<vector<double>> adjMatrix);
    vector<int> makePath(int u, int v); 
    void printPath(vector<int>& path); 
};

Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;

    adjMatrix.resize(V, vector<double>(V, numeric_limits<double>::max()));
    successor.resize(V, vector<int>(V, -1));
    for (int i = 0; i < V; ++i) {
        adjMatrix[i][i] = 0.0;
    }
}

void Graph::addEdge(int u, int v, double w) {
    adjMatrix[u][v] = w;
}

vector<vector<double>> Graph::floydWarshall() {
    vector<vector<double>> distanceMatrix = this->adjMatrix;
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if(distanceMatrix[i][k] == numeric_limits<double>::max())
                continue;
            for (int j = 0; j < V; ++j) {
                if(distanceMatrix[k][j] == numeric_limits<double>::max())
                    continue;
                if (distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]) {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    successor[i][j] = successor[i][k];
                }
            }
        }
    }
    return distanceMatrix;
}

void Graph::setSuccessors(vector<vector<double>> adjMatrix) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjMatrix[i][j] == numeric_limits<double>::max())
                successor[i][j] = -1;
            else
                successor[i][j] = j;
        }
    }
}

vector<int> Graph::makePath(int u, int v){
    if (successor[u][v] == -1)
            return {};
        vector<int> path = { u };
        while (u != v) {
            u = successor[u][v];
            path.push_back(u);
        }
        return path;
}

void printPath(vector<int>& path)
{
    unsigned long n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << path[i]+1 << " -> ";
    cout << path[n - 1]+1 << endl;
}

int main() {
    int nodes, edges;
    cout<<"Enter the number of nodes and edges"<<endl; 
    cin >> nodes >> edges;
    int u, v;
    double w;
    Graph graphInstance(nodes, edges);
    vector<vector<double>> distanceMatrix;

    cout << "Enter the <source, destination, weight> for each edge using 1 based indexing" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        u--; v--; // 0 based indexing
        graphInstance.addEdge(u, v, w);
    }
    graphInstance.setSuccessors(graphInstance.adjMatrix);

    distanceMatrix = graphInstance.floydWarshall();

    cout << "Shortest distance matrix" << endl;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (distanceMatrix[i][j] == numeric_limits<double>::max())
                cout << "INF ";
            else
                cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    vector<int> path; 
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (i != j) {
                path = graphInstance.makePath(i, j);
                cout << "Path from " << i+1 << " to " << j+1 << ": ";
                printPath(path);
            }
        }
    }

    return 0;
}
