import itertools
import copy
import networkx as nx
import pandas as pd
from random import shuffle
import numpy as np
import os, sys

edgelist = []
nodelist = []
edgelist = pd.read_csv('ParkingEdgelist.csv')
nodelist = pd.read_csv('ParkingNodelist.csv')
edgelist2 = edgelist.sample(frac=1).reset_index(drop=True)
nodelist2 = nodelist.sample(frac=1).reset_index(drop=True)

g = nx.Graph()
h = nx.Graph()

eulerTour = []
eulerTour2 = []

for idx, row in edgelist.iterrows():
    g.add_edge(row[0], row[1], **row[2:].to_dict())

for idx, row in nodelist.iterrows():
    nx.set_node_attributes(g, {row['id']:  row[1:].to_dict()})

for idx, row in edgelist2.iterrows():
    h.add_edge(row[0], row[1], **row[2:].to_dict())

for idx, row in nodelist2.iterrows():
    nx.set_node_attributes(h, {row['id']:  row[1:].to_dict()})

def get_shortest_paths_distances(graph, pairs, edge_weight_name):
    distance = {}
    for pair in pairs:
        distance[pair] = nx.dijkstra_path_length(graph, pair[0], pair[1], weight = edge_weight_name)
    return distance


def create_complete_graph(pair_weights, flip_weights = True):

    g = nx.Graph()
    for k, v in pair_weights.items():
        wt_i = - v if flip_weights else v   
        g.add_edge(k[0], k[1], **{'distance': v, 'weight': wt_i})
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

'''=========================================='''
'''==================== g ==================='''
'''=========================================='''
node_positions = {}
node_positions = {node[0]: (node[1]['X'], node[1]['Y']) for node in g.nodes(data=True)}
edge_colors = []
edge_colors = [e[2]['color'] for e in list(g.edges(data=True))]
nodes_odd_degree = []
nodes_odd_degree = [v for v, d in g.degree() if d % 2 ==1]

odd_node_pairs = []
odd_node_pairs = list(itertools.combinations(nodes_odd_degree, 2))
odd_node_pairs_shortest_paths = {}
odd_node_pairs_shortest_paths = get_shortest_paths_distances(g, odd_node_pairs, 'distance')

g_odd_complete = create_complete_graph(odd_node_pairs_shortest_paths, flip_weights = True)
odd_matching_dupes = set()
odd_matching_dupes = nx.algorithms.max_weight_matching(g_odd_complete, True)
odd_matching = list()
odd_matching = list(pd.unique([tuple(sorted([k, v])) for k, v in odd_matching_dupes.items()]))

g_aug = add_augmenting_path_to_graph(g, odd_matching)

euler_circuit = []
euler_circuit = create_eulerian_circuit(g_aug, g, 'node0')

for j in range(len(euler_circuit)):
    eulerTour.append(euler_circuit[j][0])


'''=========================================='''
'''==================== h ==================='''
'''=========================================='''
node_positions = {}
node_positions = {node[0]: (node[1]['X'], node[1]['Y']) for node in h.nodes(data=True)}
edge_colors = []
edge_colors = [e[2]['color'] for e in list(h.edges(data=True))]
nodes_odd_degree = []
nodes_odd_degree = [v for v, d in h.degree() if d % 2 ==1]
odd_node_pairs = []
odd_node_pairs = list(itertools.combinations(nodes_odd_degree, 2))

odd_node_pairs_shortest_paths = {}
odd_node_pairs_shortest_paths = get_shortest_paths_distances(h, odd_node_pairs, 'distance')

h_odd_complete = create_complete_graph(odd_node_pairs_shortest_paths, flip_weights = True)
odd_matching_dupes = set()
odd_matching_dupes = nx.algorithms.max_weight_matching(h_odd_complete, True)
odd_matching = list()
odd_matching = list(pd.unique([tuple(sorted([k, v])) for k, v in odd_matching_dupes.items()]))
h_aug = add_augmenting_path_to_graph(h, odd_matching)


euler_circuit = []
euler_circuit = create_eulerian_circuit(h_aug, h, 'node0')

for j in range(len(euler_circuit)):
    eulerTour2.append(euler_circuit[j][0])

# ed: saver,loader added
route_saver = open('route_list.dat', 'a')
route_loader = open('route_list.dat', 'r')

b_isExist = False

for route in route_loader:
    route = route.strip()
    if(str(route) == str(eulerTour)):
        print("[-] SAME route detected! skipping...")
        b_isExist = True

if not b_isExist:
    print("[+] New Route added!")
    route_saver.write(str(eulerTour))
    route_saver.write('\n')

if(eulerTour != eulerTour2):
    # print(eulerTour)
    # print("----------")
    # print(eulerTour2)
    print("[+] New Route added2!")
    route_saver.write(str(eulerTour2))
    route_saver.write('\n')
    pass
else:
    print("[-] Other Routes are not found. Restarting...")
    python = sys.executable
    os.execl(python, python, *sys.argv)

route_saver.close()
route_loader.close()
