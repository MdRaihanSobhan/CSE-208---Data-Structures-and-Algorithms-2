The problem is to find all the strongly connected components (SCCs) in a directed graph. A strongly connected component is a subgraph in which there is a path between each pair of vertices.

Graph Representation: The firms and share-owning relationships are represented as a directed graph using adjacency lists.
Kosaraju's Algorithm:
First Pass: Perform a DFS on the original graph to fill a stack based on the finishing times of vertices.
Transpose the Graph: Reverse the directions of all edges to get the transposed graph.
Second Pass: Perform DFS on the transposed graph in the order defined by the stack to find SCCs.
Output: Each SCC is output as a line of firms. We sort the components for consistent ordering and convert back to 1-based indexing for the output.