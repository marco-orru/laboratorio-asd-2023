package org.unito.asd;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.*;

class PriorityQueueTest {
  private PriorityQueue<Integer> priorityQueue;

  @BeforeEach
  void setUp() {
    priorityQueue = new PriorityQueue<>(Comparator.<Integer>naturalOrder());
  }

  @Test
  void empty() {
    assertTrue(priorityQueue.empty());
    priorityQueue.push(1);
    assertFalse(priorityQueue.empty());
    priorityQueue.pop();
    assertTrue(priorityQueue.empty());
  }

  @Test
  void push() {
  }

  @Test
  void contains() {
  }

  @Test
  void top() {
  }

  @Test
  void pop() {
  }

  @Test
  void remove() {
  }
}