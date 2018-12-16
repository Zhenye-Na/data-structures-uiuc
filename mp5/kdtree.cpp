/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     if (first[curDim] < second[curDim]) {
         return true;
     } else if (first[curDim] > second[curDim]) {
         return false;
     } else {
         // If there is a tie, break it using Point's operator<
         return (first < second);
     }

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

     // get distance from target to currentBest and Point
     double distCur = getDistance(target, currentBest);
     double distP = getDistance(target, potential);

     if (distCur < distP) return false;
     if (distP < distCur) return true;

     // with a tie being broken by the operator <
     return (potential < currentBest);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<Dim>> points = newPoints;
     if (newPoints.size() == 1) return;
     build(0, points.size()-1, 0);
}


/**
 * This method holds recursive cases on dim and builds the tree.
 */
template <int Dim>
void KDTree<Dim>::build(int start, int end, int dimension)
{
    if (start >= end) return;
    int median = (start + end) / 2;
    quickSelect(start, end, median, dimension); // ensure median is median point
    build(start, median-1, (dimension + 1) % Dim);
    build(median+1, end, (dimension + 1) % Dim);
}

/**
 * This method does a quick select on the Point at index k in vector--points.
 */
template <int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int k, int dimension)
{
    if (start >= end) return;
    int index = partition(start, end, (start + end) / 2, dimension);
    if (index > k) return quickSelect(start, index - 1, k, dimension);
    if (index < k) return quickSelect(index + 1, end, k, dimension);
}

/**
 * This method does a partition aroung pivot and will be used in quick select.
 * It returns the index of the pivot in the new vector.
 */
template <int Dim>
int KDTree<Dim>::partition(int start, int end, int pivot, int dimension)
{
    Point<Dim> thePoint = points[pivot];
    int record = start;
    swap(points[pivot], points[end]);

  for (int i = start; i < end; i++) {
      if (smallerDimVal(points[i], thePoint, dimension)) {
          swap(points[record], points[i]);
          record++;
      }
  }

    swap(points[record], points[end]);
    return record;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}


template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}


/**
 * Helper function to be called recursively to get the nearest neighbor.
 */
template <int Dim>
void KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, Point<Dim>&
  currBest, int start, int end, int dimension, double& distance, bool& first) const
{
  if (start > end)
    return;

  if (start == end) {
    if (first) {
      currBest = points[start];
      distance = getDistance(query, currBest);
      first = false;
    } else {
      if (shouldReplace(query, currBest, points[start])) {
        currBest = points[start];
        distance = getDistance(currBest, query);
      }
    }
    return;
  }

  int mid = (start + end) / 2;
  if (smallerDimVal(query, points[mid], dimension)) {
    findNearestNeighborHelper(query, currBest, start, mid-1, (dimension+1) % Dim, distance, first);

      if (shouldReplace(query, currBest, points[mid])) {
        currBest = points[mid];
        distance = getDistance(currBest, query);
        first = false;  //0 1 2 3 4 5 _6 7   3,5,6   0-7:3  4-7:5 6-7:6 6-5
      }
      if (possibleOtherSide(query, points[mid], dimension, distance)) {
        findNearestNeighborHelper(query, currBest, mid+1, end, (dimension+1) % Dim, distance, first);
      }
  } else {
    findNearestNeighborHelper(query, currBest, mid+1, end, (dimension+1) % Dim, distance, first);

      if (shouldReplace(query, currBest, points[mid])) {
        currBest = points[mid];
        distance = getDistance(currBest, query);
        first = false;
      }
      if (possibleOtherSide(query, points[mid], dimension, distance)) {
        findNearestNeighborHelper(query, currBest, start, mid - 1, (dimension+1) % Dim, distance, first);
      }

  }
}



/**
 * Helper function to get squared distance between two points.
 */
template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& query, const Point<Dim>& currBest) const
{
    double distance = 0;
    for (int i = 0; i < Dim; i++) {
        distance += pow((query[i] - currBest[i]), 2);
    }
    return distance;
}

/**
 * Helper function to tell if the nearest neighbor could be on the other side
 * of the KD tree.
 */
template <int Dim>
bool KDTree<Dim>::possibleOtherSide(const Point<Dim>& query,
                                    const Point<Dim>& curr,
                                    int dimension,
                                    double distance) const
{
    return pow((curr[dimension]- query[dimension]), 2) <= distance;
}
