package org.unito.asd;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.*;

class MinPriorityQueueTest {
  private PriorityQueue<Integer> priorityQueue;

  @BeforeEach
  void setUp() {
    priorityQueue = new PriorityQueue<>(Comparator.<Integer>naturalOrder(), true);
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
    assertEquals(3, priorityQueue.top());
  }

  @Test
  void pop() {
    priorityQueue.push(8);
    priorityQueue.push(2);
    priorityQueue.push(5);
    assertEquals(2, priorityQueue.top());
    priorityQueue.pop();
    assertEquals(5, priorityQueue.top());
    priorityQueue.pop();
    assertEquals(8, priorityQueue.top());
  }

  @Test
  void remove() {
    priorityQueue.push(5);
    priorityQueue.push(3);
    priorityQueue.push(8);

    assertTrue(priorityQueue.remove(8));
    assertFalse(priorityQueue.contains(8));
    assertTrue(priorityQueue.remove(3));
    assertFalse(priorityQueue.contains(3));

    assertEquals(5, priorityQueue.top());

    assertFalse(priorityQueue.remove(10));
  }
}