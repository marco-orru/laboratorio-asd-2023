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
   * Adds an element to the queue.
   *
   * @param element The element to be added.
   * @return {@code true} if the element is successfully added, {@code false} otherwise.
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
   */
  void pop();

  /**
   * Removes a specific element from the queue.
   *
   * @param element The element to be removed.
   * @return {@code true} if the element is successfully removed, {@code false} otherwise.
   */
  boolean remove(E element);
}
