#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// finding strongly connected components (SCCs)
// Kosaraju's Algorithm: O(V+E)

// Perform DFS on the original graph and fill the stack based on finishing times, i.e., the topological order
void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true; // Mark the current vertex as visited

    for (int u : adj[v]) { // Visit all the adjacent vertices
        if (!visited[u]) { // If the adjacent vertex is not visited, perform DFS
            dfs1(u, adj, visited, Stack); // Recursive DFS call
        }
    }
    Stack.push(v); // Push the current vertex to the stack
}

// Perform DFS on the transposed graph to find the strongly connected components
void dfs2(int v, vector<vector<int>>& rev_adj, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : rev_adj[v]) {
        if (!visited[u]) {
            dfs2(u, rev_adj, visited, component);
        }
    }
}

void findSCCs(int n, vector<vector<int>>& adj) {
    stack<int> Stack;
    vector<bool> visited(n, false);

    // Step 1: Perform DFS and fill the stack
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i, adj, visited, Stack);
        }
    }

    // Step 2: Transpose the graph
    vector<vector<int>> rev_adj(n);
    for (int v = 0; v < n; ++v) {
        for (int u : adj[v]) {
            rev_adj[u].push_back(v);
        }
    }

    // Step 3: Perform DFS according to the stack order on the transposed graph
    fill(visited.begin(), visited.end(), false);
    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();
        if (!visited[v]) {
            vector<int> component;
            dfs2(v, rev_adj, visited, component);
            if (component.size() > 1) { // Output only if the component has more than one vertex
                sort(component.begin(), component.end());
                for (int x : component) {
                    cout << x + 1 << " ";  // Converting back to 1-based index
                }
                cout << "\n";
            }
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<vector<int>> adj(n);
    for (int i = 0; i < s; ++i) {
        int f1, f2;
        cin >> f1 >> f2;
        adj[f1 - 1].push_back(f2 - 1);  // Converting to 0-based index
    }

    findSCCs(n, adj);
    return 0;
}

/*
Explanation
The problem is to find all the strongly connected components (SCCs) in a directed graph. A strongly connected component is a subgraph in which there is a path between each pair of vertices.

Graph Representation: The firms and share-owning relationships are represented as a directed graph using adjacency lists.
Kosaraju's Algorithm:
First Pass: Perform a DFS on the original graph to fill a stack based on the finishing times of vertices.
Transpose the Graph: Reverse the directions of all edges to get the transposed graph.
Second Pass: Perform DFS on the transposed graph in the order defined by the stack to find SCCs.
Output: Each SCC is output as a line of firms. We sort the components for consistent ordering and convert back to 1-based indexing for the output.
*/