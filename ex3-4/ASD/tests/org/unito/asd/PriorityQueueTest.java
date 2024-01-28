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
    assertTrue(priorityQueue.push(1));
    assertTrue(priorityQueue.push(2));
    assertFalse(priorityQueue.push(2));
  }

  @Test
  void contains() {
    assertFalse(priorityQueue.contains(10));
    priorityQueue.push(10);
    assertTrue(priorityQueue.contains(10));
    priorityQueue.pop();
    assertFalse(priorityQueue.contains(10));
  }

  @Test
  void top() {
    assertNull(priorityQueue.top());
    priorityQueue.push(7);
    priorityQueue.push(3);
    assertEquals(7, priorityQueue.top());
  }

  @Test
  void pop() {
  }

  @Test
  void remove() {
  }
}