# Breadth First Search Algorithm
 
Problem: Many GPS Navigation systems uses to BFS (Breadth First Search) go from one point to another on the map to the shortest route algorithm. In this project, an algorithm that performs this operation on the graph will be designed.

Process steps:

1. Read the links to the graph with N node, M linked and the values of the links.

2. Read the Start and Arrival nodes.

3. There can be multiple paths between the Startup node and the Arrival node. All the ways of individual BFS method.

4. Display information about nodes and internodes connection values for the shortest of the paths that you find
print.

5. If there is no connection between the specified nodes, a message should be given stating that the outbound is not possible.

6. Print the list of nodes connected directly to each other on the map.

7. Print the node with the most neighbor to the screen.

8. Print the two farthest points and distances to each other on the map.

EXAMPLE INTRODUCTION DATA: Ignore Input.txt//parts

5 7//number of nodes and connections

0 3//start and end nodes

//links and weights are mixed below.

0 1 3

1 3 3

4 2 2

1 4 1

0 4 1

1 2 1

4 3 1


The inputs were read from the text file n, m, nodes and distances between them were read. Source destination and distance information was kept in Edge. Graph structure was created and converted into an adjaceny list.
Based on the number of neighbours for each node, the number of nodes that are most neighbours was found. Using the BFS function, the minimum distance is calculated from the source node to the destination node, and the path and distance between these nodes are printed on the screen.

