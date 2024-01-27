package org.unito.asd;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a generic priority queue.
 * @param <E> The type of elements in the priority queue.
 * @implNote The priority queue is implemented using a max-heap.
 */
public final  class PriorityQueue<E> {
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
}
