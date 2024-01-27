package org.unito.asd;

import org.jetbrains.annotations.NotNull;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a generic priority queue.
 * @param <E> The type of elements in the priority queue.
 * @implNote The priority queue is implemented using a max-heap.
 */
public final class PriorityQueue<E> implements AbstractQueue<E> {
    private final MaxHeap<E> heap;
    private final Map<E, Integer> indexMap;

    /**
     * Constructs a new {@link PriorityQueue} with the given comparator.
     * @param comparator The comparator used to compare elements priority in the priority queue.
     */
    public PriorityQueue(Comparator<E> comparator) {
        this.heap = new MaxHeap<>(comparator);
        this.indexMap = new HashMap<>();
    }

    @Override
    public boolean empty() {  // TODO
        return false;
    }

    @Override
    public boolean push(@NotNull E element) {  // TODO
        return false;
    }

    @Override
    public boolean contains(@NotNull E element) {  // TODO
        return false;
    }

    @Override
    public E top() {  // TODO
        return null;
    }

    @Override
    public void pop() {  // TODO

    }

    @Override
    public boolean remove(@NotNull E element) {  // TODO
        return false;
    }
}
