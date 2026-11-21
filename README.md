# 🌳 Estrutura de Dados 2 (ED2)

![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow?style=for-the-badge)
![Linguagem](https://img.shields.io/badge/Linguagem-C%20(C11)-00599C?style=for-the-badge&logo=c&logoColor=white)
![Licença](https://img.shields.io/badge/Licença-MIT-green?style=for-the-badge)

Repositório dedicado às implementações em **linguagem C**, análises de complexidade e trabalhos práticos desenvolvidos durante a disciplina de **Estrutura de Dados 2**. O foco principal abrange alocação dinâmica, manipulação de ponteiros em estruturas não lineares, algoritmos em grafos e gerenciamento de arquivos binários em memória secundária.

---

## 📂 Estrutura do Repositório

Cada módulo é estruturado seguindo a modularização padrão em C (`.h` para cabeçalhos/TADs e `.c` para implementações):

```text
estrutura-de-dados-2/
├── 01-arvores-binarias/
│   ├── bst/                  # Árvore Binária de Busca (bst.h, bst.c, main.c)
│   ├── avl/                  # Árvore Balanceada AVL (avl.h, avl.c, main.c)
│   └── red-black/            # Árvore Rubro-Negra (rb.h, rb.c, main.c)
├── 02-arvores-multiway/
│   ├── arvore-b/             # Árvore B em memória secundária (btree.h, btree.c)
│   └── arvore-b-mais/        # Árvore B+ (bplustree.h, bplustree.c)
├── 03-heaps-e-filas-prioridade/
│   ├── min-max-heap/         # Heap Binário (heap.h, heap.c)
│   └── heapsort/             # Ordenação Heapsort (heapsort.c)
├── 04-tabelas-hash/
│   ├── encadeamento/         # Tratamento de colisão por encadeamento separado
│   └── enderecamento-aberto/ # Sondagem linear, quadrática e duplo hash
├── 05-grafos/
│   ├── representacoes/       # Matriz de Adjacência e Lista de Adjacência
│   ├── buscas/               # Busca em Largura (BFS) e Busca em Profundidade (DFS)
│   ├── caminhos-minimos/     # Dijkstra, Bellman-Ford e Floyd-Warshall
│   └── arvore-geradora/     # Árvore Geradora Mínima (Kruskal e Prim)
├── 06-ordenacao-externa/
│   └── merge-sort-externo/   # Intercalação balanceada de arquivos binários
├── tests/                    # Casos de teste (.in / .out) para validação
├── .gitignore
└── README.md
