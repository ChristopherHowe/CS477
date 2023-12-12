import networkx as nx
import matplotlib.pyplot as plt

def depthFirstSearch(graph:nx.Graph, func):
    t = 0
    vertSet = graph.nodes()
    for vertex in vertSet:
        graph.nodes[vertex]['color']='white'
        graph.nodes[vertex]['pi']=''

    for vertex in vertSet:
        if graph.nodes[vertex]['color'] == 'white':
            t = dfs_visit(vertex, graph, t, func)

def dfs_visit(vertex, graph: nx.Graph, t, func):
    func(vertex, graph)
    graph.nodes[vertex]['color'] = 'grey'
    t += 1
    graph.nodes[vertex]['d'] = t
    for v in graph.adj[vertex]:
        if graph.nodes[v]['color'] == 'white':
            graph.nodes[vertex]['pi']=vertex
            t = dfs_visit(v, graph, t, func)
    graph.nodes[vertex]['color'] = 'black'
    t += 1
    graph.nodes[vertex]['f'] = t
    return t

def isBipartite(graph: nx.Graph):
    is_bipartite = True
    
    def bipartiteHelper(vertex, graph: nx.Graph):
        nonlocal is_bipartite
        neighborsState = None
        for neighbor in graph.adj[vertex]: 
            if graph.nodes[neighbor]['color'] != 'white': # check if neighbor has been explored
                if neighborsState != graph.nodes[neighbor]['set'] and neighborsState != None:
                    is_bipartite = False
                else:
                    neighborsState = graph.nodes[neighbor]['set']            
        
        if neighborsState != None:
            graph.nodes[vertex]['set'] = not neighborsState
        else:
            graph.nodes[vertex]['set'] = True
        
    depthFirstSearch(graph, bipartiteHelper)
    return is_bipartite

def main():
    bipartite = nx.Graph()  # Create a graph
    bipartite.add_nodes_from(['x1', 'x2', 'x3', 'y1', 'y2','y3']) # Add nodes
    bipartite.add_edges_from([('x1', 'y1'), ('x1', 'y2'), ('x2', 'y1'), ('x2', 'y2'), ('x2', 'y3'),('x3','y2'),('x3','y3'),]) # Add edges
    nx.draw(bipartite, with_labels=True, font_weight='bold') # Visualize the graph
    plt.show()

    print(f"This graph is {isBipartite(bipartite)}")

    not_bipartite = nx.Graph()  # Create a graph
    not_bipartite.add_nodes_from(['a','b','c','d'])
    not_bipartite.add_edges_from([('a','b'),('a','c'),('b','c'),('c','d'),('b','d')])
    nx.draw(not_bipartite, with_labels=True, font_weight='bold') # Visualize the graph
    plt.show()

    print(f"This graph is {isBipartite(not_bipartite)}")

main()
