package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.*;

/**
 * Represents a graph optimized for sparse data.
 * @param <V> The type of nodes in the graph.
 * @param <L> The type of labels associated with edges in the graph.
 */
public final class Graph<V, L> implements AbstractGraph<V, L> {
  private final Map<V, Set<AbstractEdge<V, L>>> adjacency;
  private final boolean directed;
  private final boolean labelled;
  private int numEdges;

  /**
   * Constructs a new {@link Graph} with the specified characteristics.
   * @param directed {@code true} if the graph is directed, {@code false} otherwise.
   * @param labelled {@code true} if the graph is labelled, {@code false} otherwise.
   */
  public Graph(boolean directed, boolean labelled) {
    this.adjacency = new HashMap<>();
    this.directed = directed;
    this.labelled = labelled;
    this.numEdges = 0;
  }

  /**
   * Checks if the graph is directed.
   * @return {@code true} if the graph is directed, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean isDirected() {
    return directed;
  }

  /**
   * Checks if the graph is labelled.
   * @return {@code true} if the graph is labelled, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean isLabelled() {
    return labelled;
  }

  /**
   * Adds a node to the graph.
   * The node shall not be {@code null}.
   * A node is being added if and only if it is not already present in the graph.
   * @param node The node to be added.
   * @return {@code true} if the node was successfully added, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(mutates = "this")
  public boolean addNode(@NotNull V node) {
    if (containsNode(node))
      return false;

    adjacency.put(node, new HashSet<>());
    return true;
  }

  /**
   * Adds an edge from node {@code start} to node {@code end} if the graph is directed, or between
   * node {@code start} to node {@code end} if the graph is undirected.
   * The provided nodes shall not be {@code null}.
   * The provided label shall not be {@code null} if the graph is labelled.
   * An edge can be added if and only if the graph contains the two nodes.
   * If an edge already exists between the two nodes then this function returns {@code true}, but no operation is being made.
   * @param start The start node of the edge.
   * @param end The end node of the edge.
   * @param label The label associated with the edge (it is ignored if the graph is not labelled).
   * @return {@code true} if the edge was successfully added, {@code false otherwise}.
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
    if (!adjacency.get(start).add(edge))
      return true;  // Already present, but it's not an error.

    numEdges++;

    if (!directed) {
      edge = new Edge<>(end, start, label);
      adjacency.get(end).add(edge);
    }

    return true;
  }

  /**
   * Checks if a node is present in the graph.
   * The node shall not be {@code null}.
   * @param node The node to check for.
   * @return {@code true} if the node is present in the graph, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean containsNode(@NotNull V node) {
    return adjacency.containsKey(node);
  }

  /**
   * Checks if a node is present from node {@code start} to {@code end} if the graph is directed, or between {@code start} and
   * {@code end} if the graph is undirected.
   * The nodes shall not be {@code null}.
   * @param start The start node of the edge.
   * @param end The end node of the edge.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public boolean containsEdge(@NotNull V start, @NotNull V end) {
    var edge = new Edge<>(start, end, null);
    return containsNode(start) && adjacency.get(start).contains(edge);
  }

  /**
   * Removes a node from the graph, deleting also the edges linked from and linked to it.
   * The node shall not be {@code null}.
   * The node is being removed if and only if it's present inside the graph.
   * @param node The node to be removed.
   * @return {@code true} if the node was successfully removed, {@code false} otherwise.
   * @implNote This operation has linear time complexity O(N).
   */
  @Override
  @Contract(mutates = "this")
  public boolean removeNode(@NotNull V node) {
    return false;  // TODO
  }

  /**
   * Removes an edge between two nodes from the graph.
   * The nodes shall not be {@code null}.
   * The edge is being removed if and only if is present in the graph.
   * @param start The start node of the edge.
   * @param end The end node of the edge.
   * @return {@code true} if the edge was successfully removed, {@code false} otherwise.
   * @implSpec This operation has constant time complexity O(1).
   */
  @Override
  @Contract(mutates = "this")
  public boolean removeEdge(@NotNull V start, @NotNull V end) {
    return false;  // TODO
  }

  /**
   * Gets the number of nodes in the graph.
   * @return The number of nodes in the graph.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public int numNodes() {
    return adjacency.size();
  }

  /**
   * Gets the number of edges in the graph.
   * @return The number of edges in the graph.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public int numEdges() {
    return numEdges;
  }

  /**
   * Gets a collection of all the nodes in the graph.
   * The collection will be empty if the graph is empty.
   * @return A collection of all the nodes in the graph.
   * @implNote  This operation has linear time complexity O(N).
   */
  @Override
  @Contract(pure = true)
  public Collection<V> getNodes() {
    return null;  // TODO
  }

  /**
   * Gets a collection of all the edges in the graph.
   * The collection will be empty if there are no edges in the graph.
   * @return A collection of all the edges in the graph.
   * @implNote  This operation has linear time complexity O(N).
   */
  @Override
  @Contract(pure = true)
  public Collection<? extends AbstractEdge<V, L>> getEdges() {
    return null;  // TODO
  }

  /**
   * Get a collection of neighboring nodes for the given node.
   * The node shall not be {@code null} and shall be present in the graph.
   * @param node The node for which neighbours are to be received.
   * @return A collection of neighbouring nodes for the given node.
   * @exception IllegalStateException If the node is not present in the graph.
   * @implSpec This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public Collection<V> getNeighbours(@NotNull V node) throws IllegalStateException {
    return null; // TODO
  }

  /**
   * Gets the label associated with an edge between nodes {@code start} and node {@code end}.
   * The nodes shall not be {@code null}.
   * The graph shall be labelled.
   * @param start The start node of the edge.
   * @param end The end node of the edge.
   * @return The label associated with the edge, if exists, or {@code null} if the edge does not exist.
   * @exception IllegalStateException The graph is not labelled.
   * @implSpec This operation has constant time complexity O(1).
   */
  @Override
  @Contract(pure = true)
  public @Nullable L getLabel(@NotNull V start, @NotNull V end) throws IllegalStateException {
    return null;  // TODO
  }
}
