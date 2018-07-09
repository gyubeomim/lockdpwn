import itertools
import copy
import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt
from random import shuffle
import numpy as np
import os

# g = nx.Graph()
# for i in range(3):
    # g.clear()

edgelist = []
nodelist = []
edgelist = pd.read_csv('ParkingEdgelist.csv')
nodelist = pd.read_csv('ParkingNodelist.csv')
# edgelist2 = edgelist.sample(frac=1).reset_index(drop=True)
# nodelist2 = nodelist.sample(frac=1).reset_index(drop=True)

# print(edgelist2)
# print(nodelist2)
g = nx.Graph()
# h = nx.Graph()

eulerTour = []
# eulerTour2 = []

for idx, row in edgelist.iterrows():
    g.add_edge(row[0], row[1], **row[2:].to_dict())

for idx, row in nodelist.iterrows():
    nx.set_node_attributes(g, {row['id']:  row[1:].to_dict()})

# for idx, row in edgelist2.iterrows():
#     h.add_edge(row[0], row[1], **row[2:].to_dict())

# for idx, row in nodelist2.iterrows():
#     nx.set_node_attributes(h, {row['id']:  row[1:].to_dict()})


def get_shortest_paths_distances(graph, pairs, edge_weight_name):
    distance = {}
    for pair in pairs:
        distance[pair] = nx.dijkstra_path_length(graph, pair[0], pair[1], weight = edge_weight_name)
    return distance


def create_complete_graph(pair_weights, flip_weights = True):

    g = nx.Graph()# define a new graph for making complete one.
    for k, v in pair_weights.items():# get a key and a value from 'pair_weights'
        wt_i = - v if flip_weights else v   
        g.add_edge(k[0], k[1], **{'distance': v, 'weight': wt_i})# (node1, node2, information)
    return g

def add_augmenting_path_to_graph(graph, min_weight_pairs):
    graph_aug = nx.MultiGraph(graph.copy())
    for pair in min_weight_pairs:
        graph_aug.add_edge(pair[0],
                        pair[1],
                        **{'distance': nx.dijkstra_path_length(graph, pair[0], pair[1]) , 'trail' : 'augmented'})
    return graph_aug

def create_eulerian_circuit(graph_augmented, graph_original, starting_node = None):
    euler_circuit = []
    aug_path = ()
    aug_path_pairs = []
    naive_circuit = []

    naive_circuit = list(nx.eulerian_circuit(graph_augmented, source = starting_node))
    # print("ddddd", naive_circuit)
    for edge in naive_circuit:
        edge_data = graph_augmented.get_edge_data(edge[0], edge[1])

        if edge_data[0]['trail'] != 'augmented':
            edge_att = graph_original[edge[0]][edge[1]]
            euler_circuit.append((edge[0], edge[1], edge_att))
        
        else:
            aug_path = nx.shortest_path(graph_original, edge[0], edge[1], weight = 'distance')
            aug_path_pairs = list(zip(aug_path[:-1], aug_path[1:]))

            for edge_aug in aug_path_pairs:
                edge_aug_att = graph_original[edge_aug[0]][edge_aug[1]]
                euler_circuit.append((edge_aug[0], edge_aug[1], edge_aug_att))


    return euler_circuit


node_positions = {}
node_positions = {node[0]: (node[1]['X'], node[1]['Y']) for node in g.nodes(data=True)}
# print(dict(list(node_positions.items())))
edge_colors = []
edge_colors = [e[2]['color'] for e in list(g.edges(data=True))]# store edges' color
# drawing
# plt.figure(figsize = (8, 6))
# nx.draw(g, pos = node_positions, edge_color = edge_colors, node_size = 10, node_color = 'red')
# plt.title('MOANA')
# plt.show()
# quit()
nodes_odd_degree = []
nodes_odd_degree = [v for v, d in g.degree() if d % 2 ==1]
odd_node_pairs = []
odd_node_pairs = list(itertools.combinations(nodes_odd_degree, 2))
# print(odd_node_pairs)
odd_node_pairs_shortest_paths = {}
odd_node_pairs_shortest_paths = get_shortest_paths_distances(g, odd_node_pairs, 'distance')
# print(odd_node_pairs_shortest_paths)
g_odd_complete = create_complete_graph(odd_node_pairs_shortest_paths, flip_weights = True)
# plt.figure(figsize = (8, 6))
# pos_random = nx.random_layout(g_odd_complete)
# nx.draw_networkx_nodes(g_odd_complete, node_positions, node_size = 20, node_color = 'red')
# nx.draw_networkx_edges(g_odd_complete, node_positions, alpha = 0.1)
# plt.axis('off')
# plt.title('Yo, Yeah~')
# plt.show()
odd_matching_dupes = set()
odd_matching_dupes = nx.algorithms.max_weight_matching(g_odd_complete, True)
odd_matching = list()
odd_matching = list(pd.unique([tuple(sorted([k, v])) for k, v in odd_matching_dupes]))
# print(odd_matching)
# quit()
# plt.figure(figsize = (8, 6))
# nx.draw(g_odd_complete, pos = node_positions, node_size = 20, alpha = 0.05)
# g_odd_complete_min_edges = nx.Graph(odd_matching)
# nx.draw(g_odd_complete_min_edges, pos = node_positions, node_size = 20, edge_color = 'blue', node_color = 'red')
# plt.title('Min Weight Matching on Complete Graph')
# plt.show()


g_aug = add_augmenting_path_to_graph(g, odd_matching)
# print('g_aug', g_aug)




# eulerTour2 = []
euler_circuit = []
euler_circuit = create_eulerian_circuit(g_aug, g, 'node0')
# euler_circui2 = create_eulerian_circuit(g_aug, g, 'node0')

# print(g.edges)
# print(g.nodes)

for j in range(len(euler_circuit)):
    eulerTour.append(euler_circuit[j][0])

# print('g_aug', g_aug)

# eulerTour2 = []

eulerSet = []
eulerSet.append(eulerTour)



    # if eulerTour not in eulerSet:
    # eulerSet.append(eulerTour)
# eulerTour = []
# for i in range(len(euler_circuit)):
#     eulerTour.append(euler_circuit[i][0])
# print(eulerSet)
# print(len(eulerSet))

# quit()


def create_cpp_edgelist(euler_circuit):
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

g_cpp = nx.Graph(cpp_edgelist)
plt.figure(figsize = (8, 6))

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
    # i => index, e => element
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

    nx.draw_networkx_nodes(g_i, pos = node_positions, node_size = 6, alpha = 0.6, node_color = 'gray', with_labels = False, linewidths = 0.1)
    nx.draw_networkx_edges(g_i, pos = node_positions, edge_color = g_i_edge_colors, alpha = 0.8)

    plt.axis('off')
    # plt.savefig('img{}.png'.format(i), dpi = 120, bbox_inches = 'tight')
    plt.show()
    plt.close()


