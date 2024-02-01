package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public final class Edge<V, L> implements AbstractEdge<V, L> {
  private final V start;
  private final V end;
  private final L label;

  public Edge(@NotNull V start, @NotNull V end, L label) {
    this.start = start;
    this.end = end;
    this.label = label;
  }

  @Override
  @Contract(pure = true)
  public V getStart() {
    return start;
  }

  @Override
  @Contract(pure = true)
  public V getEnd() {
    return end;
  }

  @Override
  @Contract(pure = true)
  public L getLabel() {
    return label;
  }
}
