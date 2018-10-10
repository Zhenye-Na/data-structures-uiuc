/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Zesheng Wang
 * @author Wade Fagen-Ulmschneider
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 */

#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include "util/coloredout.h"
#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template <int Dim>
class KDTree
{
  private:
    /**
     * Internal structure for a node of KDTree.
     * Contains left, right children pointers and a K-dimensional point
     */
    struct KDTreeNode
    {
      Point<Dim> point;
      KDTreeNode *left, *right;

      KDTreeNode() : point(), left(NULL), right(NULL) {}
      KDTreeNode(const Point<Dim> &point) : point(point), left(NULL), right(NULL) {}
    };

  public:
    /**
     * Determines if Point a is smaller than Point b in a given dimension d.
     * If there is a tie, break it with Point::operator<().
     *
     * For example:
     *
     *     Point<3> a(1, 2, 3);
     *     Point<3> b(3, 2, 1);
     *     cout << smallerDimVal(a, b, 0) << endl; // should print true
     *     cout << smallerDimVal(a, b, 2) << endl; // should print false
     *     cout << smallerDimVal(a, b, 1) << endl; // based on operator<, this should be true
     *
     * @todo This function is required for MP 5.1.
     * @param first Point to compare.
     * @param second Second point to compare.
     * @param curDim Dimension these points are being compared in.
     * @return A boolean value indicating whether the first Point is smaller
     *  than the second Point in the curDim dimension.
     */
    bool smallerDimVal(const Point<Dim>& first, const Point<Dim>& second,
                       int curDim) const;

    /**
     * Determines if a Point is closer to the target Point than another
     * reference Point. Takes three points: target, currentBest, and
     * potential, and returns whether or not potential is closer to
     * target than currentBest.
     *
     * We are using Euclidean distance to compare k-dimensional
     * points: \f$\sqrt{(p_1-q_1)^2+(p_2-q_2)^2+\ldots+(p_n-q_n)^2} =
     * \sqrt{\sum_{i=1}^n (p_i-q_i)^2}\f$. Note, however, that
     * **minimizing distance is the same as minimizing squared
     * distance**, so you can **avoid invoking the square root** and
     * just compare squared distances in your code.
     *
     * For example:
     *
     *     Point<3> target(1, 3, 5);
     *     Point<3> currentBest1(1, 3, 2);
     *     Point<3> possibleBest1(2, 4, 4);
     *     Point<3> currentBest2(1, 3, 6);
     *     Point<3> possibleBest2(2, 4, 4);
     *     Point<3> currentBest3(0, 2, 4);
     *     Point<3> possibleBest3(2, 4, 6);
     *     cout << shouldReplace(target, currentBest1, possibleBest1) << endl; // true
     *     cout << shouldReplace(target, currentBest2, possibleBest2) << endl; // false
     *     cout << shouldReplace(target, currentBest3, possibleBest3) << endl;
     *      // based on operator<, this should be false
     *
     * @todo This function is required for MP 5.1.
     * @param target The Point we want to be close to.
     * @param currentBest The Point that is currently our closest Point
     *    to target.
     * @param potential Our Point that is a candidate to replace
     *    currentBest (that is, it may be closer to target than
     *    currentBest).
     * @return A boolean value indicating whether potential is closer
     *  to target than currentBest. Ties should be broken with
     *  Point::operator<().
     */
    bool shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest,
                       const Point<Dim>& potential) const;

    /**
     * Constructs a KDTree from a vector of Points, each having dimension Dim.
     *
     * You need to handle the case that the vector has no Point in it. It should
     * build the tree using recursive helper functions.
     *
     * Since we know the size of the KDTree at construction, we can
     * represent the tree as a linear structure and building the tree nodes
     * based off this structure efficiently. For testing, we **require**
     * the following:
     *
     * 1.  The median node of n nodes is calculated as the cell
     *     \f$\left\lfloor\frac{n-1}{2}\right\rfloor\f$. That is, the
     *     middle node is selected if there are an odd number, and the
     *     item before the middle if there are an even number. **If there
     *     are ties (two points have equal value along a dimension), they
     *     must be decided using Point::operator<().** Although this is
     *     arbitrary and doesn't affect the functionality of the KDTree,
     *     it is required to be able to grade your code.
     *
     * KD-trees are created recursively; at any stage of the construction,
     * the median value in the current dimension is selected and a node is
     * created based on it. Then, all the elements in the current subtree are divided
     * up into elements which are less than the median, or greater than
     * the median, and then the subtrees are created recursively.
     * The children pick the median in the next dimension, and repeat
     * until the entire set of inputs has been processed. Successive
     * levels of the tree split on increasing dimensions, modulo the
     * total number: a 3D tree will have levels split by dimension 0, 1, 2,
     * 0, 1, 2, etc.
     *
     * You will probably want to write a helper function which performs the
     * median selection and partitioning. Maybe you can use a function you
     * already wrote...
     *
     * @see Here is a reference that should help you create concise,
     * efficient code: [Partition-based General Selection
     * Algorithm](http://en.wikipedia.org/wiki/Selection_algorithm). Note
     * that "select pivotIndex between left and right" means that you
     * should choose a midpoint between the left and right indices.
     *
     * @todo This function is required for MP 5.1.
     * @param newPoints The vector of points to build your KDTree off of.
     */
    KDTree(const vector<Point<Dim>>& newPoints);


    /**
     * Copy constructor for KDTree.
     *
     * @param other The KDTree to copy.
     */
    KDTree(const KDTree& other);

    /**
     * Assignment operator for KDTree.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    KDTree const &operator=(const KDTree& rhs);

    /**
     * Destructor for KDTree.
     */
    ~KDTree();

    /**
     * Finds the closest point to the parameter point in the KDTree.
     *
     * This function takes a reference to a template parameter Point and
     * returns the Point closest to it in the tree. We are defining
     * closest here to be the minimum Euclidean distance between elements.
     * Again, **if there are ties (this time in distance), they must be
     * decided using Point::operator<().** Recall that an HSLAPixel is
     * defined by three components: hue, saturation, and luminance.
     *
     * The findNearestNeighbor() search is done in two steps: a search to
     * find the smallest hyperrectangle that contains the target element,
     * and then a back traversal to see if any other hyperrectangle could
     * contain a closer point, which may be a point with smaller distance
     * or a point with equal distance, but a "smaller" point (as defined
     * by operator< in the point class). In the first step, you must
     * recursively traverse down the tree, at each level choosing the
     * subtree which represents the region containing the search element
     * (another place to save some duplicate code?). When you reach the
     * lowest bounding hyperrectangle, then the corresponding node is
     * effectively the "current best" neighbor.
     *
     * However, it may be the case that a better match exists outside of
     * the containing hyperrectangle. At then end of first step of the
     * search, we start traversing back up the kdtree to the parent node.
     * The current best distance defines a radius which contains the
     * nearest neighbor. During the back-traversal (i.e., stepping out of
     * the recursive calls), you must first check if the distance to the
     * parent node is less than the current radius. If so, then that
     * distance now defines the radius, and we replace the "current best"
     * match. Next, it is necessary to check to see if the current
     * splitting plane's distance from search node is within the current
     * radius. If so, then the opposite subtree could contain a closer
     * node, and must also be searched recursively.
     *
     * During the back-traversal, it is important to only check the
     * subtrees that are within the current radius, or else the efficiency
     * of the kdtree is lost. If the distance from the search node to the
     * splitting plane is greater than the current radius, then there
     * cannot possibly be a better nearest neighbor in the subtree, so the
     * subtree can be skipped entirely.
     *
     * You can assume that findNearestNeighbor will only be called on a
     * valid kd-tree.
     *
     * @see Here is a reference we found quite useful in writing our kd-tree:
     *  [Andrew Moore's KD-Tree Tutorial]
     * (https://courses.engr.illinois.edu/cs225/sp2018/private/mps/5/moore-tutorial.pdf).
     *
     * @see There is [an example]
     * (https://courses.engr.illinois.edu/cs225/sp2018/mps/5/) in the MP5 instruction.
     *
     * @todo This function is required for MP 5.1.
     * @param query The point we wish to find the closest neighbor to in the
     *  tree.
     * @return The closest point to a in the KDTree.
     */
    Point<Dim> findNearestNeighbor(const Point<Dim>& query) const;

    // functions used for grading:

    /**
     * You do not need to modify this function. Its implementation is in
     *  kdtree_extras.cpp.
     * Prints the KDTree to the terminal in a pretty way.
     */
    void printTree(ostream& out = cout,
                   colored_out::enable_t enable_bold = colored_out::COUT,
                   int modWidth = -1) const;

  private:

    /** Internal representation, root and size **/
    KDTreeNode *root;
    size_t size;

    /** Helper function for grading */
    int getPrintData(KDTreeNode * subroot) const;

    /** Helper function for grading */
    void printTree(KDTreeNode * subroot, std::vector<std::string>& output,
                   int left, int top, int width, int currd) const;

    /**
     * @todo Add your helper functions here.
     */
};

#include "kdtree.cpp"
#include "kdtree_extras.cpp"
#endif
