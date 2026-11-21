# 🌳 Estrutura de Dados 2 (ED2)

![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow?style=for-the-badge)
![Linguagem](https://img.shields.io/badge/Linguagem-C%20%2F%20C%2B%2B-blue?style=for-the-badge)
![Licença](https://img.shields.io/badge/Licença-MIT-green?style=for-the-badge)

Repositório dedicado às implementações, algoritmos, análises de complexidade e trabalhos práticos desenvolvidos durante a disciplina de **Estrutura de Dados 2**. O foco principal abrange estruturas de dados não lineares, algoritmos em grafos, indexação e manipulação de arquivos em memória secundária.

---

## 📂 Estrutura do Repositório

```text
estrutura-de-dados-2/
├── 01-arvores-binarias/
│   ├── bst/                  # Árvore Binária de Busca (Binary Search Tree)
│   ├── avl/                  # Árvore Balanceada AVL (Rotações simples e duplas)
│   └── red-black/            # Árvore Rubro-Negra
├── 02-arvores-multiway/
│   ├── arvore-b/             # Árvore B (Indexação e manipulação em disco)
│   └── arvore-b-mais/        # Árvore B+
├── 03-heaps-e-filas-prioridade/
│   ├── min-max-heap/         # Heap Binário (Min-Heap e Max-Heap)
│   └── heapsort/             # Algoritmo de ordenação Heapsort
├── 04-tabelas-hash/
│   ├── encadeamento/         # Tratamento de colisão por encadeamento separado
│   └── enderecamento-aberto/ # Sondagem linear, quadrática e duplo hash
├── 05-grafos/
│   ├── representacoes/       # Matriz de Adjacência e Lista de Adjacência
│   ├── buscas/               # Busca em Largura (BFS) e Busca em Profundidade (DFS)
│   ├── caminhos-minimos/     # Dijkstra, Bellman-Ford e Floyd-Warshall
│   └── arvore-geradora/      # Árvore Geradora Mínima (Kruskal e Prim)
├── 06-ordenacao-externa/
│   └── merge-sort-externo/   # Intercalação balanceada de múltiplos caminhos
├── tests/                    # Casos de teste (.in / .out) para validação
└── README.md
