'''
You can find a tutorial of this code, below.
http://brooksandrew.github.io/simpleblog/articles/intro-to-graph-optimization-solving-cpp/#motivating-graph-optimization
'''
import itertools
import copy
import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt

debug = False
show_graph = True
stats = True
edgelist = pd.read_csv('edgelist_sleeping_giant.csv')# call the edgelist of cvs file
# edgelist.head(10)
nodelist = pd.read_csv('nodelist_sleeping_giant.csv')# call the nodelist of cvs file
# nodelist.head(5)

################################################## Contain edges and nodes
g = nx.Graph()# make a graph using networkX
# print(g)\
# elrow => edgelist row
for i, elrow in edgelist.iterrows():# Iterate over DataFrame rows as (index, Series) pairs.
    g.add_edge(elrow[0], elrow[1], **elrow[2:].to_dict())# make an edge of the graph we make

if debug:
    print(elrow[0])# The edge from
    print(elrow[1])# The edge to
    print(elrow[2:].to_dict())# {'estimate': 0, 'distance': 0.12, 'color': 'yellowgreen', 'trail': 'gy2'}

for i, nlrow in nodelist.iterrows():
    nx.set_node_attributes(g, {nlrow['id']:  nlrow[1:].to_dict()})# make an node of the graph we make

if debug:
    print(nlrow)
#######################################################################

'''
Your graph edges are represented by a list of tuples of length 3.
The first two elements are the node names linked by the edge.
The ghird is the dictionary of edge attributes.
'''

if debug:
    print(list(g.edges(data=True))[0:5])
    print(list(g.nodes(data=True))[0:10])
    print('# of edges: {}'.format(g.number_of_edges()))
    print('# of nodes: {}'.format(g.number_of_nodes()))
    

######## mANIPULATE COLORS AND LAYOUT, Make nodes as a set
# Define node positions data structure (dict) for plotting
node_positions = {node[0]: (node[1]['X'], -node[1]['Y']) for node in g.nodes(data=True)}

# Preview of node_positions with a bit of hack (there is no head/slice method for dictionaries)
if debug:
    dict(list(node_positions.items())[0:5])

####### Make a color of each edge, we store these into 'edge_colors' of a dictionary
edge_colors = [e[2]['color'] for e in list(g.edges(data=True))]

if debug:
    print("edge_colors[0:10]: {}".format(edge_colors[0:10]))# it stores each color of each node

############# Make a plot
plt.figure(figsize = (8, 6))
nx.draw(g, pos = node_positions, edge_color = edge_colors, node_size = 10, node_color = 'black')
plt.title('Graph Representation of Sleeping Giant Train Map', size = 15)
plt.show()
#########################################################################
#########################################################################

'''
Now we are going to implement the CPP algorithm of this graph we built
'''
nodes_odd_degree = [v for v, d in g.degree() if d % 2 == 1]# contains nodes having odd degree
# Above list contains nodes which have odd degrees
if debug:
    print("nodes_odd_degree[0:5]: {}".format(nodes_odd_degree[0:5]))
    print("Number of nodes of odd degree: {}".format(len(nodes_odd_degree)))
    print("Number of total nodes: {}".format(len(g.nodes())))

############################################################################
##### Step 2.1: Compute Node Pairs ###########
##### We are gointg to compute all possible pairs of the odd degree nodes. 
##### In this case, we assume that our graph is  undirected.

# Compute all pairs of odd noes. in a list of tuples
# # of pairs = n choose r = n Combination r = nCr
# Make a list which contains combinations of odd_nodes
odd_node_pairs = list(itertools.combinations(nodes_odd_degree, 2))

if debug:
    print("odd_node_pairs[0:10]: {}".format(odd_node_pairs[0:10]))
    print('Number of pairs: {}'.format(len(odd_node_pairs)))


############################################################################
############################################################################
############################################################################
##### Step 2.2: Compute shortest paths between Node Pairs

def get_shortest_paths_distances(graph, pairs, edge_weight_name):
    """Compute shortest distance between each pair of nodes in a graph. Return a dictionary keyed on node pairs (tuples)."""
    distances = {}
    for pair in pairs:# pairs => list, pair => element
        distances[pair] = nx.dijkstra_path_length(graph, pair[0], pair[1], weight = edge_weight_name)
    return distances

# Compute shortest paths, return a dictionary with node pairs keys and a single value equal to shortest path distance.
odd_node_pairs_shortest_paths = get_shortest_paths_distances(g, odd_node_pairs, 'distance') # dictionary
# print(odd_node_pairs_shortest_paths)
if debug:
    print("Preview of the distances of odd_degrees_pairs: {}".format(dict(list(odd_node_pairs_shortest_paths.items())[0:10])))

############################################################################
################### Step 2.3: Create Complete Graph ########################
############################################################################

def create_complete_graph(pair_weights, flip_weights = True):
    """
    Create a completely connected graph using a list of vertex pairs and the shortest path distances between them
    Parameters: 
        pair_weights: A dictionary from the output of get_shortest_paths_distances, tuple can not be changed
        flip_weights: Boolean. Should we negate the edge attribute in pair_weights?
    """
    g = nx.Graph()# define a new graph for making complete one.
    for k, v in pair_weights.items():# get a key and a value from 'pair_weights'
        wt_i = - v if flip_weights else v   
        g.add_edge(k[0], k[1], **{'distance': v, 'weight': wt_i})# (node1, node2, information)
    return g
# Generate the complete graph
g_odd_complete = create_complete_graph(odd_node_pairs_shortest_paths, flip_weights=True)

# Counts
if debug:
    print('Number of nodes: {}'.format(len(g_odd_complete.nodes())))
    print('Number of edges: {}'.format(len(g_odd_complete.edges())))

    plt.figure(figsize=(8, 6))# figure size
    pos_random = nx.random_layout(g_odd_complete)
    nx.draw_networkx_nodes(g_odd_complete, node_positions, node_size = 20, node_color = 'red')# node_position => a dictionary
    nx.draw_networkx_edges(g_odd_complete, node_positions, alpha = 0.1)
    plt.axis('off')
    plt.title('Complete Graph of Odd-degree Nodes')
    plt.show()
############################################################################################################
''' Step 2.4: Compute Minimum Weight Matching: In this step, we are going to find 
the odd degree node pairs whose combined sum is as small as possible
the code implemented in the NetworkX function max_weight_matching is based on Galil, Zvi (1986) [2] which employs an O(n3) time algorithm.
'''
############################################################################################################

# Compute min weight matchins
# Note: max_weight_matching uses the 'weight' attribute by default as the attribute to maximize.
odd_matching_dupes = nx.algorithms.max_weight_matching(g_odd_complete, True)# it is a dictionary
# In this case, it has 36 edges in this matching. But we only need 18 edge-pair. 
print(odd_matching_dupes)
if debug:
    # print("minsoo")
    print("Number of edges in matching: {}".format(len(odd_matching_dupes)))

odd_matching = list(pd.unique([tuple(sorted([k, v])) for k, v in odd_matching_dupes]))# Removing duplicates yields the unique 18 edge-pairs, this is because the graph is un-directed
if debug:
    print(odd_matching)
    print(len(odd_matching))

if show_graph:
    plt.figure(figsize=(8, 6))
    # Plot the complete graph of odd-degree nodes
    nx.draw(g_odd_complete, pos=node_positions, node_size=20, alpha=0.05)
    # Create a new graph to overlay on g_odd_complete with just the edges from the min weight matching
    g_odd_complete_min_edges = nx.Graph(odd_matching)
    nx.draw(g_odd_complete_min_edges, pos=node_positions, node_size=20, edge_color='blue', node_color='red')

    plt.title('Min Weight Matching on Complete Graph')
    plt.show()

if show_graph:
    # To illustrate how this fits in with the original graph, you plot the same min weight pairs (blue liens)
    # over the trail map instead of the complete graph. 
    plt.figure(figsize=(8, 6))

    # Plot the original trail map graph
    nx.draw(g, pos=node_positions, node_size=20, alpha=0.1, node_color='black')

    # Plot graph to overlay with just the edges from the min weight matching
    nx.draw(g_odd_complete_min_edges, pos=node_positions, node_size=20, alpha=1, node_color='red', edge_color='blue')

    plt.title('Min Weight Matching on Orginal Graph')
    plt.show()

''' Step 2.5: Augment the Original Graph
: Now, we are going to add additional edges we've got from the Complete Graph.
'''
def add_augmenting_path_to_graph(graph, min_weight_pairs):
    """
    Add the min weight matching edges to the original graph
    Parametes:
        graph: NeetworkX graph (original graph from trailmap)
        min_weight_pairs: list[tuples] of node pairs from min weight matching
    Returns:
        augmented NetworkX graph
    """
    # We need to make the augmented graph a MultiGraph so we can add parallel edges
    graph_aug = nx.MultiGraph(graph.copy())
    for pair in min_weight_pairs:# that means this for loop add the minimum weight pairs to edges
        graph_aug.add_edge(pair[0],
                           pair[1],
                           **{'distance': nx.dijkstra_path_length(graph, pair[0], pair[1]), 'trail': 'augmented'}# 'trail': 'augmented' means the edge is an additional one.
                           )
    return graph_aug

g_aug = add_augmenting_path_to_graph(g, odd_matching)

if debug:
    print('Number of edges in original graph: {}'.format(len(g.edges())))
    print('Number of edges in augmented graph: {}'.format(len(g_aug.edges())))

    print("Count the even degree: {}".format(pd.value_counts([e[1] for e in g_aug.degree()])))





'''##########################################################################################################################
#############################################################################################################################
#############################################################################################################################
Step 3: Compute Eulerian Circuit
: Finally, we have a graph with even degree the hard optimization work is over.
We can use the NetworkX eulerian_circuit function. However there are some limitations
'''

naive_euler_circuit = list(nx.eulerian_circuit(g_aug, source = 'b_end_east'))# source -> starting node
if debug:
    print(naive_euler_circuit[0:10])
# [(node1, node2), (node2, node3), (node3, node4), ...]
def create_eulerian_circuit(graph_augmented, graph_original, starting_node=None):
    """Create the eulerian path using only edges from the original graph."""
    euler_circuit = []
    naive_circuit = list(nx.eulerian_circuit(graph_augmented, source = starting_node))# make a default eulerian citcuit

    for edge in naive_circuit:
        edge_data = graph_augmented.get_edge_data(edge[0], edge[1])# save the attribute dictionary associated with edge (u, v)

        if edge_data[0]['trail'] != 'augmented':
            # If `edge` exists in original graph, grab the edge attributes and add to eulerian circuit.
            edge_att = graph_original[edge[0]][edge[1]]# original graph [node1, node2]
            euler_circuit.append((edge[0], edge[1], edge_att))# if there is a better path

        else:# if that edge has an augmented trail, 
            aug_path = nx.shortest_path(graph_original, edge[0], edge[1], weight = 'distance')# compute shortest paths in the graph from source to target
            aug_path_pairs = list(zip(aug_path[:-1], aug_path[1:]))

            print('Filling in edges for augmented edge: {}'.format(edge))
            print('Augmenting path: {}'.format(' => '.join(aug_path)))
            print('Augmenting path pairs: {}\n'.format(aug_path_pairs))
            
            # If `edge` does not exist in original graph, find the shortest path between its nodes and 
            # add the edge attributes for each link in the shortest path.
            for edge_aug in aug_path_pairs:
                edge_aug_att = graph_original[edge_aug[0]][edge_aug[1]]
                euler_circuit.append((edge_aug[0], edge_aug[1], edge_aug_att))

    return euler_circuit

euler_circuit = create_eulerian_circuit(g_aug, g, 'b_end_east')
print('Length of Eulerian circuit: {}'.format(len(euler_circuit)))

'''Let's peak into your solution to see how reasonable it looks'''
if stats:
    # Computing some stats
    total_mileage_of_circuit = sum([edge[2]['distance'] for edge in euler_circuit])
    total_mileage_on_orig_trail_map = sum(nx.get_edge_attributes(g, 'distance').values())
    _vcn = pd.value_counts(pd.value_counts([(e[0]) for e in euler_circuit]), sort=False)
    node_visits = pd.DataFrame({'n_visits': _vcn.index, 'n_nodes': _vcn.values})
    _vce = pd.value_counts(pd.value_counts([sorted(e)[0] + sorted(e)[1] for e in nx.MultiDiGraph(euler_circuit).edges()]))
    edge_visits = pd.DataFrame({'n_visits': _vce.index, 'n_edges': _vce.values})

    # Printing stats
    print('Mileage of circuit: {0:.2f}'.format(total_mileage_of_circuit))
    print('Mileage on original trail map: {0:.2f}'.format(total_mileage_on_orig_trail_map))
    print('Mileage retracing edges: {0:.2f}'.format(total_mileage_of_circuit-total_mileage_on_orig_trail_map))
    print('Percent of mileage retraced: {0:.2f}%\n'.format((1-total_mileage_of_circuit/total_mileage_on_orig_trail_map)*-100))

    print('Number of edges in circuit: {}'.format(len(euler_circuit)))
    print('Number of edges in original graph: {}'.format(len(g.edges())))
    print('Number of nodes in original graph: {}\n'.format(len(g.nodes())))

    print('Number of edges traversed more than once: {}\n'.format(len(euler_circuit)-len(g.edges())))  

    print('Number of times visiting each node:')
    print(node_visits.to_string(index=False))

    print('\nNumber of times visiting each edge:')
    print(edge_visits.to_string(index=False))


''' Visualize CPP solution'''

def create_cpp_edgelist(euler_circuit):
    """
    Create the edgelist without parallel edge for the visualization
    Combine duplicate edges and keep track of their sequence and # of walks
    Parameters:
        euler_circuit: list[tuple] from create_euelerian_circuit
    """

    cpp_edgelist = {}# dictionary

    for i, e in enumerate(euler_circuit):
        edge = frozenset([e[0], e[1]])

        if edge in cpp_edgelist:
            cpp_edgelist[edge][2]['sequence'] += ', '+ str(i)
            cpp_edgelist[edge][2]['visits'] += 1
        else:
            cpp_edgelist[edge] = e
            cpp_edgelist[edge][2]['sequence'] = str(i)
            cpp_edgelist[edge][2]['visits'] = 1

    return list(cpp_edgelist.values())

cpp_edgelist = create_cpp_edgelist(euler_circuit)

if debug:
    print('Number of edges in CPP edge list: {}'.format(len(cpp_edgelist)))

g_cpp = nx.Graph(cpp_edgelist)

plt.figure(figsize=(14, 10))

visit_colors = {1: 'lightgray', 2: 'blue'}
edge_colors = [visit_colors[e[2]['visits']] for e in g_cpp.edges(data=True)]
node_colors = ['red' if  node in nodes_odd_degree else 'lightgray' for node in g_cpp.nodes()]

nx.draw_networkx(g_cpp, pos = node_positions, node_size = 20, node_color = node_colors, edge_color = edge_colors, with_labels = False)
plt.axis('off')
plt.show()

### Visualize with making MOVIE
visit_colors = {1:'black', 2:'red'}
edge_cnter = {}
g_i_edge_colors = []
for i, e in enumerate(euler_circuit, start=1):

    edge = frozenset([e[0], e[1]])
    if edge in edge_cnter:
        edge_cnter[edge] += 1
    else:
        edge_cnter[edge] = 1
    
    # Full graph (faded in background)
    nx.draw_networkx(g_cpp, pos = node_positions, node_size = 6, node_color = 'gray', with_labels = False, alpha = 0.07)

    # Edges walked as of iteration i
    euler_circuit_i = copy.deepcopy(euler_circuit[0:i])
    for i in range(len(euler_circuit_i)):
        edge_i = frozenset([euler_circuit_i[i][0], euler_circuit_i[i][1]])
        euler_circuit_i[i][2]['visits_i'] = edge_cnter[edge_i]
    g_i = nx.Graph(euler_circuit_i)
    g_i_edge_colors = [visit_colors[e[2]['visits_i']] for e in g_i.edges(data = True)]

    nx.draw_networkx_nodes(g_i, pos = node_positions, node_size = 6, alpha = 0.6, node_color = 'lightgray', with_labels = False, linewidths = 0.1)
    nx.draw_networkx_edges(g_i, pos = node_positions, edge_color = g_i_edge_colors, alpha = 0.8)

    plt.axis('off')
    plt.savefig('parkingimg{}.png'.format(i), dpi = 120, bbox_inches = 'tight')
    plt.close()