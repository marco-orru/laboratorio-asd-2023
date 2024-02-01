package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

/**
 * Represents an edge between to nodes of a {@link Graph}.
 * @param start The start node. It can't be {@code null}.
 * @param end The end node. It can't be {@code null}.
 * @param label The label associated with the edge.
 * @param <V> Type of nodes in the graph.
 * @param <L> Type of labels associated with edges in the graph.
 */
public record Edge<V, L>(
        @Contract(pure = true) @NotNull V start,
        @Contract(pure = true) @NotNull V end,
        @Contract(pure = true) L label
) implements AbstractEdge<V, L> { }
