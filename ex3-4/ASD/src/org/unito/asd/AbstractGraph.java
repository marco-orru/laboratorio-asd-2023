package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

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

  /**
   * Adds a node to the graph.
   * The node shall not be {@code null}.
   * A node is being added if and only if it is not already present in the graph.
   * @param node The node to be added.
   * @return {@code true} if the node was successfully added, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(mutates = "this")
  boolean addNode(@NotNull V node);

  /**
   * Adds an edge from node {@code start} to node {@code end} if the graph is directed, or between
   * node {@code start} to node {@code end} if the graph is undirected.
   * The provided nodes shall not be {@code null}.
   * The provided label shall not be {@code null} if the graph is labelled.
   * An edge can be added if and only if the graph contains the two nodes.
   * If an edge already exists between the two nodes (eventually with the same label, if the graph is labelled)
   * then this function returns {@code true}, but no operation is being made.
   * @param start The start node of the edge.
   * @param end The end node of the edge.
   * @param label The label associated with the edge (it is ignored if the graph is not labelled).
   * @return {@code true} if the edge was successfully added, {@code false otherwise}.
   * @exception IllegalArgumentException If {@code label} is {@code null} and the graph is labelled.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(mutates = "this")
  boolean addEdge(@NotNull V start, @NotNull V end, L label) throws IllegalArgumentException;

  /**
   * Gets the number of nodes in the graph.
   * @return The number of nodes in the graph.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  int numNodes();
}

/*
public interface AbstractGraph<V,L> {
  public boolean containsNode(V a); // controlla se un nodo è nel grafo -- O(1)
  public boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)
  public boolean removeNode(V a); // rimuove un nodo dal grafo -- O(N)
  public boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)
  // public int numNodes(); // numero di nodi -- O(1)
  public int numEdges(); // numero di archi -- O(N)
  public Collection<V> getNodes(); // recupero dei nodi del grafo -- O(N)
  public Collection<? extends AbstractEdge<V,L>> getEdges(); // recupero degli archi del grafo -- O(N)
  public Collection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
  public L getLabel(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)
};

 */