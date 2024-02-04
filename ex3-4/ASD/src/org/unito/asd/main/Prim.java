package org.unito.asd.main;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
 import org.unito.asd.*;
import org.unito.asd.PriorityQueue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

import static java.lang.StringTemplate.STR;
import static java.util.FormatProcessor.FMT;

public class Prim {
  @Contract(pure = true)
  public static <V, L extends Number> @NotNull Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(@NotNull Graph<V, L> graph) {
    var visitedNodes = new HashSet<V>(graph.numNodes());
    var priorityQueue = new PriorityQueue<Edge<V, L>>(Comparator.comparing(edge -> edge.getLabel().doubleValue()), true);
    var msf = new ArrayList<AbstractEdge<V, L>>();

    // Iter through all the nodes to make sure every mst is considered.
    for (var node : graph.getNodes()) {
      // If the node has been already visited, continue with the next one, otherwise, mark it as visited.
      if (!visitedNodes.add(node))
        continue;

      // Loop until eventually all the nodes has been analyzed
      // this condition is true iff there is only one mst in the graph, otherwise the "break" from below will be used.
      while (visitedNodes.size() < graph.numNodes()) {

        // Add all the edges from the current node to its neighbours to the priority queue.
        for (var neighbour : graph.getNeighbours(node)) {
          // Optimization: Add it iff the node has not been considered yet.
          if (!visitedNodes.contains(neighbour)) {
            var edge = new Edge<>(node, neighbour, graph.getLabel(node, neighbour));
            priorityQueue.push(edge);
          }
        }

        // Keep extracting the min edge from the priority queue,
        // until the priority queue is empty (the mst is complete) or
        // the end node of the edge has already been visited (it should be ignored).
        var minEdge = priorityQueue.top();
        while (minEdge != null && visitedNodes.contains(minEdge.getEnd())) {
          priorityQueue.pop();
          minEdge = priorityQueue.top();
        }

        // If the min edge is null, the mst built from 'node' is complete, so we should break the loop.
        if (minEdge == null)
          break;

        // Add the edge to the mst, add its end node to the visited nodes and restart the loop, using the end
        // node as the start node for the subsequent node search.
        msf.add(minEdge);
        visitedNodes.add(minEdge.getEnd());
        node = minEdge.getEnd();
      }

      if (visitedNodes.size() == graph.numNodes())
        break;
    }

    return msf;
  }

  private static Graph<String, Double> readDataToGraph(BufferedReader inputFile) throws IOException {
    var graph = new Graph<String, Double>(false, true);

    String line;
    while ((line = inputFile.readLine()) != null) {
      var fmtLine = line.split(",");

      graph.addNode(fmtLine[0]);  // from
      graph.addNode(fmtLine[1]);  // to
      graph.addEdge(fmtLine[0], fmtLine[1], Double.parseDouble(fmtLine[2]));  // distance
    }

    return graph;
  }

  private static <V, L extends Number> void printMsfInfo(@NotNull Collection<? extends AbstractEdge<V, L>> msf) {
    System.err.println(STR."Number of edges: \{msf.size()}");
    System.err.println(FMT."Total weight: %.0f\{msf.stream().mapToDouble(edge -> edge.getLabel().doubleValue()).sum()} km");

    for (var edge : msf)
      System.out.println(STR."[\{edge.getStart()}]--(\{edge.getLabel()})--[\{edge.getEnd()}]");
  }

  public static void main(String @NotNull [] args) {
    var path = args[0];

    Graph<String, Double> graph;
    try (var inputFile = new BufferedReader(new FileReader(path))) {
      graph = readDataToGraph(inputFile);
    } catch (IOException e) {
      System.err.println("Error while opening input file");
      throw new RuntimeException(e);
    }

    var msf = minimumSpanningForest(graph);

    printMsfInfo(msf);
  }
}
