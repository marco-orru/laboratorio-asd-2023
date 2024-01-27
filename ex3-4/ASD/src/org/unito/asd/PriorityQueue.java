package org.unito.asd;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a generic priority queue.
 *
 * @param <E> The type of elements in the priority queue.
 * @implNote The priority queue is implemented using a max-heap.
 */
public final class PriorityQueue<E> implements AbstractQueue<E> {
  private final MaxHeap<E> heap;
  private final Map<E, Integer> indexMap;

  /**
   * Constructs a new {@link PriorityQueue} with the given comparator.
   *
   * @param comparator The comparator used to compare elements priority in the priority queue.
   */
  public PriorityQueue(Comparator<E> comparator) {
    this.heap = new MaxHeap<>(comparator);
    this.indexMap = new HashMap<>();
  }

  /**
   * Checks whether the priority queue is empty or not.
   *
   * @return {@code true} if the priority queue is empty, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public boolean empty() {
    return heap.empty();
  }

  @Override
  public boolean push(@NotNull E element) {  // TODO
    return false;
  }

  /**
   * Checks whether a specific element is present in the priority queue or not.
   * The element shall not be {@code null}.
   *
   * @param element The element to check for existence.
   * @return {@code true} if the element is present, {@code false} otherwise.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public boolean contains(@NotNull E element) {
    return indexMap.containsKey(element);
  }

  /**
   * Accesses the element at the top of the priority queue without removing it.
   *
   * @return The element at the top of the queue, or {@code null} if the queue is empty.
   * @implNote This operation has constant time complexity O(1).
   */
  @Override
  public @Nullable E top() {
    return heap.root();
  }

  @Override
  public void pop() {  // TODO

  }

  @Override
  public boolean remove(@NotNull E element) {  // TODO
    return false;
  }
}
