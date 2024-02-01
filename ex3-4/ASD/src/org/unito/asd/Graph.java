package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Represents a graph optimized for sparse data.
 * @param <V> The type of nodes in the graph.
 * @param <L> The type of labels associated with edges in the graph.
 */
public final class Graph<V, L> implements AbstractGraph<V, L> {
  private final Map<V, Set<AbstractEdge<V, L>>> adjacencyList;
  private final boolean directed;
  private final boolean labelled;

  /**
   * Constructs a new {@link Graph} with the specified characteristics.
   * @param directed {@code true} if the graph is directed, {@code false} otherwise.
   * @param labelled {@code true} if the graph is labelled, {@code false} otherwise.
   */
  public Graph(boolean directed, boolean labelled) {
    this.adjacencyList = new HashMap<>();
    this.directed = directed;
    this.labelled = labelled;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean isDirected() {
    return directed;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean isLabelled() {
    return labelled;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(mutates = "this")
  public boolean addNode(@NotNull V node) {
    if (containsNode(node))
      return false;

    adjacencyList.put(node, new HashSet<>());
    return true;
  }

  /**
   * {@inheritDoc}
   * @exception IllegalArgumentException If {@code label} is {@code null} and the graph is labelled.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(mutates = "this")
  public boolean addEdge(@NotNull V start, @NotNull V end, L label) throws IllegalArgumentException {
    if (labelled && label == null)
      throw new IllegalArgumentException("The label of an edge can't be 'null' in a labelled graph.");

    if (!containsNode(start) || !containsNode(end))
      return false;

    var edge = new Edge<>(start, end, label);
    if (!adjacencyList.get(start).add(edge))
      return true;  // Already present, but it's not an error.

    if (!directed) {
      edge = new Edge<>(end, start, label);
      adjacencyList.get(end).add(edge);
    }

    return true;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean containsNode(@NotNull V node) {
    return adjacencyList.containsKey(node);
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean containsEdge(@NotNull V start, @NotNull V end) {
    var edge = new Edge<>(start, end, null);
    return containsNode(start) && adjacencyList.get(start).contains(edge);
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public int numNodes() {
    return adjacencyList.size();
  }
}
