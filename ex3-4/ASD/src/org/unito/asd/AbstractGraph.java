package org.unito.asd;

import org.jetbrains.annotations.Contract;

import java.util.AbstractCollection;

/**
 * Defines an interface representing a graph with generic nodes and edge labels.
 *
 * @param <V> The type of nodes in the graph.
 * @param <L> The type of labels associated with edges in the graph.
 */
public interface AbstractGraph<V, L> {
  /**
   * Checks if the graph is directed.
   *
   * @return {@code true} if the graph is directed, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean isDirected();

  /**
   * Checks if the graph is labelled.
   *
   * @return {@code true} if the graph is labelled, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean isLabelled();

  /**
   * Adds a node to the graph.
   *
   * @param node The node to be added.
   * @return {@code true} if the node was successfully added, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(mutates = "this")
  boolean addNode(V node);

  /**
   * Adds an edge from node {@code start} to node {@code end} if the graph is directed, or between
   * node {@code start} to node {@code end} if the graph is undirected.
   *
   * @param start The start node of the edge.
   * @param end   The end node of the edge.
   * @param label The label associated with the edge (it is ignored if the graph is not labelled).
   * @return {@code true} if the edge was successfully added, {@code false otherwise}.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(mutates = "this")
  boolean addEdge(V start, V end, L label);

  /**
   * Checks if a node is present in the graph.
   *
   * @param node The node to check for.
   * @return {@code true} if the node is present in the graph, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean containsNode(V node);

  /**
   * Checks if a node is present from node {@code start} to {@code end} if the graph is directed, or between {@code start} and
   * {@code end} if the graph is undirected.
   *
   * @param start The start node of the edge.
   * @param end   The end node of the edge.
   * @return {@code true} if the graph contains the edge, {@code false otherwise}.
   */
  @Contract(pure = true)
  boolean containsEdge(V start, V end);

  /**
   * Removes a node from the graph, deleting also the edges linked from and linked to it.
   *
   * @param node The node to be removed.
   * @return {@code true} if the node was successfully removed, {@code false} otherwise.
   * @implSpec This operation shall have linear time complexity O(N).
   */
  @Contract(mutates = "this")
  boolean removeNode(V node);

  /**
   * Removes an edge between two nodes from the graph.
   *
   * @param start The start node of the edge.
   * @param end   The end node of the edge.
   * @return {@code true} if the edge was successfully removed, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(mutates = "this")
  boolean removeEdge(V start, V end);

  /**
   * Gets the number of nodes in the graph.
   *
   * @return The number of nodes in the graph.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  int numNodes();

  /**
   * Gets the number of edges in the graph.
   *
   * @return The number of edges in the graph.
   * @implSpec This operation shall have linear time complexity O(n).
   */
  @Contract(pure = true)
  int numEdges();

  /**
   * Gets a collection of all the nodes in the graph.
   *
   * @return A collection of all the nodes in the graph.
   * @implSpec This operation shall have linear time complexity O(N).
   */
  @Contract(pure = true)
  AbstractCollection<V> getNodes();

  /**
   * Gets a collection of all the edges in the graph.
   *
   * @return A collection of all the edges in the graph.
   * @implSpec This operation shall have linear time complexity O(N).
   */
  @Contract(pure = true)
  AbstractCollection<? extends AbstractEdge<V, L>> getEdges();

  /**
   * Get a collection of neighboring nodes for the given node.
   *
   * @param node The node for which neighbours are to be received.
   * @return A collection of neighbouring nodes for the given node.
   * @implSpec This operation has constant time complexity O(1).
   */
  @Contract(pure = true)
  AbstractCollection<V> getNeighbours(V node);

  /**
   * Gets the label associated with an edge between nodes {@code start} and node {@code end}.
   *
   * @param start The start node of the edge.
   * @param end   The end node of the edge.
   * @return The label associated with the edge.
   * @implSpec This operation has constant time complexity O(1).
   */
  @Contract(pure = true)
  L getLabel(V start, V end);
}