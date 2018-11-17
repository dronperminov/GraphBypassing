# GraphBypassing
Algorithms for the implementation of the traversal of the graph in depth and in width

## Input format
[graph_type] [start_vertex] [search_type]

[edge 1]

[edge 2]

...

[edge n]


* [graph_type] - type of graph: d - oriented graph, u - unoriented graph
* [start_vertex] - identifier of first vertex for search
* [search_type] - type of search: d - in depth, b - in width
* [edge] - edge of graph, two vertexes, for example: edge A->B is A B

## Output format
[start_vertex]

[vertex 1]

[vertex 2]

...

[vertex k]

## Example

![](https://pp.userapi.com/c850728/v850728996/45812/n3yJwHcAU0s.jpg)

### Input:
d A d

A B

B D

C D

D A

A C

C B

### Output
A

B

D

C

### Explanations
'd' - oriented graph

'A' - go by graph from vertex A

'd' - DFS, search in depth