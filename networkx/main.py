import networkx


def main():
    G = networkx.Graph()
    G.add_weighted_edges_from([("A", "C", 2), ("A", "B", 1), ("B", "C", 0)])
    print(networkx.dijkstra_path(G, "A", "C"))


if __name__ == "__main__":
    main()
