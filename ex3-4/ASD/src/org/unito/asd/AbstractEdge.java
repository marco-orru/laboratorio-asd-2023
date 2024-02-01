package org.unito.asd;

import org.jetbrains.annotations.Contract;

/**
 * Defines an interface representing an edge in a {@link AbstractGraph graph}.
 *
 * @param <V> Type of nodes in the graph.
 * @param <L> Type of labels associated with edges in the graph.
 */
public interface AbstractEdge<V, L> {
  /**
   * Gets the start node of the edge.
   *
   * @return The start node of the edge.
   */
  @Contract(pure = true)
  V start();

  /**
   * Gets the end node of the edge.
   *
   * @return The end node of the edge.
   */
  @Contract(pure = true)
  V end();

  /**
   * Gets the label associated with the edge.
   *
   * @return The label associated with the edge.
   */
  @Contract(pure = true)
  L label();
}
