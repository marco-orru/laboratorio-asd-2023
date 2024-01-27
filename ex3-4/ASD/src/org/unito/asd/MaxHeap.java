package org.unito.asd;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**
 * Represents a generic max-heap.
 * @param <E> The type of elements in the max-heap.
 */
public final class MaxHeap<E> {
    private final Comparator<E> comparator;
    private final List<E> heapArray;

    /**
     * Constructs a new {@link MaxHeap} with the given comparator.
     * @param comparator The comparator used to compare elements in the max-heap.
     */
    public MaxHeap(Comparator<E> comparator) {
        this.comparator = comparator;
        this.heapArray = new ArrayList<>();
    }
}