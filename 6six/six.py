

def trace(obj):
    path = [obj]
    while obj in orbits:
        obj = orbits[obj]
        path.append(obj)
    return list(reversed(path))


data = [x.strip().split(")") for x in open("input.txt")]
orbits = {y: x for x, y in data}
you, san = trace("YOU"), trace("SAN")
offset = sum(x == y for x, y in zip(you, san))
print(sum(len(trace(x)) - 1 for x in orbits.keys()))
print(len(you) - you.index(you[offset + 1]) + len(san) - san.index(san[offset + 1]))

import networkx

G = networkx.DiGraph()

for a in open("input.txt").readlines(): 
    G.add_edge(*[x.strip() for x in a.split(')')])

print(networkx.transitive_closure(G).size())

print(networkx.shortest_path_length(G.to_undirected(), "YOU", "SAN")-2)