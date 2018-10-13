/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#ifndef NIMLEARNER_H
#define NIMLEARNER_H

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"

/**
 * Represents a algorithm to learn the game of Nim.
 */
class NimLearner {
public:
  /**
   * Constructor to create a game of Nim with `startingTokens` starting tokens.
   *
   * This function creates a graph, `g_` representing all of the states of a
   * game of Nim with vertex labels "p#t#", where:
   * - p# is the current player's turn; p1 for Player 1, p2 for Player2
   * - t# is the tokens remaining at the start of a player's turn
   *
   * For example:
   *   "p1t4" is Player 1's turn with four (4) tokens remaining
   *   "p2t8" is Player 2's turn with eight (8) tokens remaining
   *
   * All legal moves between states are created as edges with initial weights
   * of 0.
   *
   * @param startingTokens The number of starting tokens in the game of Nim.
   */
  NimLearner(unsigned startingTokens);

  /**
   * Plays a random game of Nim, returning the path through the state graph
   * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
   * the vertex with the label "p1-#", where # is the number of starting
   * tokens.  (For example, in a 10 token game, result[0].origin must be the
   * vertex "p1-10".)
   *
   * @returns A random path through the state space graph.
   */
  std::vector<Edge> playRandomGame() const;

  /*
   * Updates the edge weights on the graph based on a path through the state
   * tree.
   *
   * If the `path` has Player 1 winning (eg: the last vertex in the path goes
   * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
   * took the last token), then all choices made by Player 1 (edges where
   * Player 1 is the source vertex) are rewarded by increasing the edge weight
   * by 1 and all choices made by Player 2 are punished by changing the edge
   * weight by -1.
   *
   * Likewise, if the `path` has Player 2 winning, Player 2 choices are
   * rewarded and Player 1 choices are punished.
   *
   * @param path A path through the a game of Nim to learn.
   */
  void updateEdgeWeights(const std::vector<Edge> & path);

  /**
   * Label the edges as "WIN" or "LOSE" based on a threshold.
   */
  void labelEdgesFromThreshold(int threshold);

  /**
   * Returns a constant reference to the state space graph.
   *
   * @returns A constant reference to the state space graph.
   */
  const Graph & getGraph() const;

private:
  Graph g_;
  Vertex startingVertex_;
};

#endif
