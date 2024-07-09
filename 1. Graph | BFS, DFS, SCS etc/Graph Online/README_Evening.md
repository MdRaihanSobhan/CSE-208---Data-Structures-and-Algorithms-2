To solve the "Digit Jump" problem, we need to use a Breadth-First Search (BFS) approach because BFS ensures that we find the shortest path in an unweighted graph, which is applicable here due to equal "jump cost" for each move.

Graph Representation: Treat the sequence as a graph where each position is a node. Edges exist between adjacent nodes (i-1 and i+1) and between nodes with the same value.
BFS Initialization: Start BFS from the first digit and maintain a queue to explore each position.
Tracking Visits: Use a visited array to ensure we don't revisit nodes, preventing infinite loops.
Queue Operations: For each position, enqueue its adjacent positions and all positions with the same digit if they haven't been visited yet.

Explanation:
Initialization:
We create a visited array to track which positions have been visited.
We use an unordered map digit_positions to store all positions of each digit in the string.
BFS Setup:
We start BFS from the first position with 0 jumps.
For each position, we explore its adjacent positions (i-1 and i+1) and all other positions with the same digit.
Queue Operations:
If moving to an adjacent position or a same-digit position reaches the last position, we return the number of jumps taken so far plus one.
If not, we enqueue the new position and mark it as visited.
After processing all same-digit positions for a digit, we clear the list to prevent redundant checks.
