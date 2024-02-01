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
  private final Map<V, Set<AbstractEdge<V, L>>> adiacencyList;
  private final boolean directed;
  private final boolean labelled;

  /**
   * Constructs a new {@link Graph} with the specified characteristics.
   * @param directed {@code true} if the graph is directed, {@code false} otherwise.
   * @param labelled {@code true} if the graph is labelled, {@code false} otherwise.
   */
  public Graph(boolean directed, boolean labelled) {
    this.adiacencyList = new HashMap<>();
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
    if (adiacencyList.containsKey(node))
      return false;

    adiacencyList.put(node, new HashSet<>());
    return true;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation have constant time complexity O(1).
   */
  @Override
  public int numNodes() {
    return adiacencyList.size();
  }
}
