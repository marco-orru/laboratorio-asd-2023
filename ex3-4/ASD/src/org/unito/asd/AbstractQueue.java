package org.unito.asd;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * Defines an interface representing a queue with generic elements.
 *
 * @param <E> The type of elements in the queue.
 */
public interface AbstractQueue<E> {
  /**
   * Checks whether the queue is empty or not.
   *
   * @return {@code true} if the queue is empty, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean empty();

  /**
   * Pushes an element onto the queue.
   *
   * @param element The element to be pushed.
   * @return {@code true} if the element is successfully pushed, {@code false} otherwise.
   * @implSpec This operation shall have logarithmic time complexity O(log N).
   */
  boolean push(E element);

  /**
   * Checks whether a specific element is present in the queue or not.
   *
   * @param element The element to check for existence.
   * @return {@code true} if the element is present, {@code false} otherwise.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  boolean contains(E element);

  /**
   * Accesses the element at the top of the queue without removing it.
   *
   * @return The element at the top of the queue.
   * @implSpec This operation shall have constant time complexity O(1).
   */
  @Contract(pure = true)
  E top();

  /**
   * Removes the element at the top of the queue.
   * @implSpec This operation shall have logarithmic time complexity O(log N).
   */
  void pop();

  /**
   * Removes the specified element from the queue.
   *
   * @param element The element to be removed.
   * @return {@code true} if the element is successfully removed, {@code false} otherwise.
   * @implSpec This operation shall have logarithmic time complexity O(log N).
   */
  boolean remove(E element);
}
