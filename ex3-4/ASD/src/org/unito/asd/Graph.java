package org.unito.asd;

import org.jetbrains.annotations.Contract;

/**
 * Represents a graph optimized for sparse data.
 * @param <V> The type of nodes in the graph.
 * @param <L> The type of labels associated with edges in the graph.
 */
public final class Graph<V, L> implements AbstractGraph<V, L> {
  private final boolean directed;
  private final boolean labelled;

  /**
   * Constructs a new {@link Graph} with the specified characteristics.
   * @param directed {@code true} if the graph is directed, {@code false} otherwise.
   * @param labelled {@code true} if the graph is labelled, {@code false} otherwise.
   */
  public Graph(boolean directed, boolean labelled) {
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
    return this.directed;
  }

  /**
   * {@inheritDoc}
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean isLabelled() {
    return this.labelled;
  }
}
