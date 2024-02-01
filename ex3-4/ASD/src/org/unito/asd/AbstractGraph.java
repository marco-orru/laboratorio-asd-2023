package org.unito.asd;

import org.jetbrains.annotations.Contract;

/**
 * Defines an interface representing a graph with generic nodes and edge labels.
 * @param <V> The type of nodes in the graph.
 * @param <L> The type of labels associated with edges in the graph.
 */
public interface AbstractGraph<V, L> {
  /**
   * Checks if the graph is directed.
   * @return {@code true} if the graph is directed, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean isDirected();

  /**
   * Checks if the graph is labelled.
   * @return {@code true} if the graph is labelled, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean isLabelled();
}

/*
public interface AbstractGraph<V,L> {
  public boolean addNode(V a); // aggiunge un nodo -- O(1)
  public boolean addEdge(V a, V b, L l); // aggiunge un arco dati estremi ed etichetta -- O(1)
  public boolean containsNode(V a); // controlla se un nodo è nel grafo -- O(1)
  public boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)
  public boolean removeNode(V a); // rimuove un nodo dal grafo -- O(N)
  public boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)
  public int numNodes(); // numero di nodi -- O(1)
  public int numEdges(); // numero di archi -- O(N)
  public Collection<V> getNodes(); // recupero dei nodi del grafo -- O(N)
  public Collection<? extends AbstractEdge<V,L>> getEdges(); // recupero degli archi del grafo -- O(N)
  public Collection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
  public L getLabel(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)
};

 */