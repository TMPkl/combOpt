import networkx as nx
import matplotlib.pyplot as plt

def generate_random_erdos_renyi_graph(n, p):
    """
    n: liczba węzłów
    p: prawdopodobieństwo krawędzi między dowolną parą węzłów
    """
    G = nx.erdos_renyi_graph(n, p)
    nx.draw(G, with_labels=True, node_color='skyblue', node_size=500, font_size=10)
    plt.show()
    return G

class Wielomian:
    def __init__(self, n_of_colors, factor_on_color):
        self.n_of_colors = n_of_colors
        self.factor_on_color = factor_on_color

    def wsplczynnik_na_kolorze(self, kolor):
        return self.factor_on_color[kolor]

    def __str__(self):
        # Correct the list comprehension to properly format each term in the polynomial
        polynomial_terms = [
            f"(x-{i})^{self.wsplczynnik_na_kolorze(i)} +" for i in range(self.n_of_colors)
        ]
        wiel_str = "Wielomian: " + " ".join(polynomial_terms)
        return wiel_str[:-1]

wielomian_grafu = Wielomian(3, [1, 2, 3])
print(wielomian_grafu)

G = generate_random_erdos_renyi_graph(n=6, p=0.3)

pos = nx.spring_layout(G)
colors = nx.coloring.greedy_color(G, strategy="largest_first")
node_colors = [colors[node] for node in G.nodes()]

nx.draw(G, pos, with_labels=True, node_color=node_colors, node_size=500, font_size=10, cmap=plt.cm.jet)
plt.show()