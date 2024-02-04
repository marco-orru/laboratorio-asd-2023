package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Objects;

/**
 * Represents an edge between to nodes of a {@link Graph}.
 * @param <V> Type of nodes in the graph.
 * @param <L> Type of labels associated with edges in the graph.
 */
public final class Edge<V, L> implements AbstractEdge<V, L> {
  private final @NotNull V start;
  private final @NotNull V end;
  private final L label;

  /**
   * @param start The start node. It can't be {@code null}.
   * @param end   The end node. It can't be {@code null}.
   * @param label The label associated with the edge.
   */
  public Edge(@NotNull V start, @NotNull V end, L label) {
    this.start = start;
    this.end = end;
    this.label = label;
  }

  @SuppressWarnings("unchecked")
  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Edge<?, ?>)) return false;
    if (obj == this) return true;
    var other = (Edge<V, ?>) obj;  // Ignore label.
    return Objects.equals(other.start, start) && Objects.equals(other.end, end);
  }

  @Override
  public int hashCode() {
    return Objects.hash(start, end);  // Ignore label.
  }

  @Override
  @Contract(pure = true)
  public @NotNull V getStart() {
    return start;
  }

  @Override
  @Contract(pure = true)
  public @NotNull V getEnd() {
    return end;
  }

  @Override
  @Contract(pure = true)
  public L getLabel() {
    return label;
  }
}
