import networkx as nx
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np
import scipy.io
import random
from random import randint

f= open("file.txt","r+")
open('output.txt', 'w+').close()
f_w = open("output.txt", "a+")
f1=f.readlines()
f.close()
for line in f1:
    flag=0
    gp = line.split()
    n = int(gp[0])
    e=n-1
    if len(gp)==2:
        e = int(gp[1])
    else:
        flag=1
    

    # print(n,e)
    # G = nx.erdos_renyi_graph(n, 0.5, seed=123, directed=False)
    # print(nx.is_connected(G))
    # print(nx.info(G))
f_w.write("%d " % n)
f_w.write("%d\n" % e)
l=[]
nodes=[]
for x in range(0, n):
	l.append(x)
	nodes.append(x)
S, T = set(l), set()


# Pick a random node, and mark it as visited and the current node.
current_node = random.sample(S, 1).pop()
S.remove(current_node)
T.add(current_node)
neighbor_node = random.sample(S, 1).pop()
S.remove(neighbor_node)
T.add(neighbor_node)

graph = nx.empty_graph(n,create_using=None)
graph.add_edge(current_node, neighbor_node, weight = randint(0,n))
# print(current_node, neighbor_node)

f_w.write("%d " % current_node)
f_w.write("%d " % neighbor_node)
str1 = str(graph.get_edge_data(current_node,neighbor_node))[::-1][1:].split()
weight = int(str1[0])
f_w.write("%d\n" % weight)

# Create a random connected graph.
while S:
    # Randomly pick the next node from the neighbors of the current node.
    neighbor_node = random.sample(S, 1).pop()
    current_node = random.sample(T, 1).pop()
    # If the new node hasn't been visited, add the edge from current to new.
    weight = randint(0,n)
    graph.add_edge(current_node, neighbor_node, weight = randint(0,n))
    S.remove(neighbor_node)
    T.add(neighbor_node)
    # print(current_node, neighbor_node)
    f_w.write("%d " % current_node)
    f_w.write("%d " % neighbor_node)
    str1 = str(graph.get_edge_data(current_node,neighbor_node))[::-1][1:].split()
    weight = int(str1[0])
    f_w.write("%d\n" % weight)
    # f_w.write("%d\n" % weight)

#create random edges
if flag==0:
    rem = e-n+1
    if rem<0:
        f_w.write("Graph created with minimum required no edges.")
        # print("Graph created with minimum required no edges.")
    else:
        while rem:
            rem=rem-1
            neighbor_node = random.sample(T, 1).pop()
            current_node = random.sample(T, 1).pop()
            weight = randint(0,n)
            graph.add_edge(current_node, neighbor_node, weight = randint(0,n))
            # print(current_node, neighbor_node)
            f_w.write("%d " % current_node)
            f_w.write("%d " % neighbor_node)
            str1 = str(graph.get_edge_data(current_node,neighbor_node))[::-1][1:].split()
            weight = int(str1[0])
            f_w.write("%d\n" % weight)
