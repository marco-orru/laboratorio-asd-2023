package org.unito.asd;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.*;

/**
 * Represents a generic priority queue.
 *
 * @param <E> The type of elements in the priority queue.
 * @implNote The priority queue is implemented using a max-heap.
 */
public final class PriorityQueue<E> implements AbstractQueue<E> {
  private final Comparator<E> comparator;
  private final List<E> heap;
  private final Map<E, Integer> indexMap;

  /**
   * Constructs a new {@link PriorityQueue} with the given comparator.
   * The provided comparator shall not be {@code null}.
   *
   * @param comparator The comparator used to compare elements priority in the priority queue.
   */
  public PriorityQueue(@NotNull Comparator<E> comparator) {
    this.comparator = Objects.requireNonNull(comparator);
    this.heap = new ArrayList<>();
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
    return heap.isEmpty();
  }

  /**
   * Pushes an element onto the priority queue.
   * The element shall not be {@code null}.
   * An element is not pushed when it is already present in the priority queue.
   *
   * @param element The element to be pushed.
   * @return {@code true} if the element is successfully pushed, {@code false} otherwise.
   * @implNote This operation has logarithmic time complexity O(log N).
   */
  @Override
  public boolean push(@NotNull E element) {
    Objects.requireNonNull(element);

    if (contains(element))
      return false;

    heap.add(element);
    indexMap.put(element, heap.size() - 1);

    heapifyUp(heap.size() - 1);
    return true;
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
    Objects.requireNonNull(element);

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
    if (empty())
      return null;

    return heap.getFirst();
  }


  /**
   * Removes the element at the top of the priority queue.
   *
   * @throws NoSuchElementException If the priority queue is empty.
   * @implSpec This operation has logarithmic time complexity O(log N).
   */
  @SuppressWarnings("DataFlowIssue")  // top() is always NotNull if do an empty() check.
  @Override
  public void pop() {
    if (empty())
      throw new NoSuchElementException("Cannot pop from an empty priority list");

    remove(top());
  }

  /**
   * Removes the specified element from the priority queue.
   * The element shall not be {@code null}.
   * An element is not removed when it is not present in the priority queue.
   *
   * @param element The element to be removed.
   * @return {@code true} if the element is successfully removed, {@code false} otherwise.
   * @implNote This operation has logarithmic time complexity O(log N).
   */
  @Override
  public boolean remove(@NotNull E element) {  // TODO
    if (!contains(element))
      return false;

    var elementIndex = indexMap.get(element);

    swapNodes(elementIndex, heap.size() - 1);

    heap.removeLast();
    indexMap.remove(element);

    heapifyDown(elementIndex);

    return true;
  }

  // PURPOSE: Gets the parent node index of a specific node, given its index.
  private int getParentIndex(int nodeIndex) {
    assert nodeIndex >= 0 && nodeIndex < heap.size() : "Node index out of heap bounds";

    return (nodeIndex - 1) / 2;
  }

  // PURPOSE: Gets the left child node index of a specific parent node, given its index.
  // NOTE: If the parent has not a left child, returns the parent index.
  private int getLeftIndex(int parentIndex) {
    assert parentIndex >= 0 && parentIndex < heap.size() : "Parent index out of heap bounds";

    var res = 2 * parentIndex + 1;
    return res < heap.size() ? res : parentIndex;
  }

  // PURPOSE: Gets the right child node index of a specific parent node, given its index.
  // NOTE: If the parent has not a right child, returns the parent index.
  private int getRightIndex(int parentIndex) {
    assert parentIndex >= 0 && parentIndex < heap.size() : "Parent index out of heap bounds";

    var res = 2 * parentIndex + 2;
    return res < heap.size() ? res : parentIndex;
  }

  // PURPOSE: Swaps two nodes given their indexes.
  // NOTE: If the two indexes are the same, no operation is being performed.
  private void swapNodes(int sourceIndex, int destinationIndex) {
    assert sourceIndex >= 0 && sourceIndex < heap.size() : "Source index out of heap bounds";
    assert destinationIndex >= 0 && destinationIndex < heap.size() : "Destination index out of heap bounds";

    if (sourceIndex == destinationIndex)
      return;

    var tmp = heap.get(sourceIndex);
    heap.set(sourceIndex, heap.get(destinationIndex));
    heap.set(destinationIndex, tmp);

    indexMap.put(heap.get(sourceIndex), sourceIndex);
    indexMap.put(heap.get(destinationIndex), destinationIndex);
  }

  // PURPOSE: Returns the max node index between the provided parent node index and its children.
  private int maxParentChildren(int parentIndex) {
    assert parentIndex >= 0 && parentIndex < heap.size() : "Parent index out of heap bounds";

    var max = parentIndex;

    var leftIndex = getLeftIndex(parentIndex);
    if (comparator.compare(heap.get(leftIndex), heap.get(max)) > 0)
      max = leftIndex;

    var rightIndex = getRightIndex(parentIndex);
    if (comparator.compare(heap.get(rightIndex), heap.get(max)) > 0)
      max = rightIndex;

    return max;
  }

  // PURPOSE: Returns the max node index between the provided children node index and its parent.
  private int maxChildrenParent(int childrenIndex) {
    assert childrenIndex >= 0 && childrenIndex < heap.size() : "Parent index out of heap bounds";

    var max = childrenIndex;

    var parentIndex = getParentIndex(childrenIndex);
    if (comparator.compare(heap.get(parentIndex), heap.get(max)) > 0)
      max = parentIndex;

    return max;
  }

  // PURPOSE: Performs a descending heapify operation on the heap from the specific index.
  private void heapifyDown(int fromIndex) {
    if (fromIndex < heap.size()) {
      var maxIndex = maxParentChildren(fromIndex);

      if (maxIndex != fromIndex) {
        swapNodes(fromIndex, maxIndex);
        heapifyDown(maxIndex);
      }
    }
  }

  // PURPOSE: Performs an ascending heapify operation on the heap from the specific index.
  private void heapifyUp(int fromIndex) {
    if (fromIndex > 0) {
      var maxIndex = maxChildrenParent(fromIndex);

      if (maxIndex != fromIndex) {
        swapNodes(fromIndex, maxIndex);
        heapifyUp(maxIndex);
      }
    }
  }
}
