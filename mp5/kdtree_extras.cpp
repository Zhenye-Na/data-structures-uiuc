/**
 * @file kdtree_extras.cpp
 * You do not need to modify this file.
 * Code here is only used for grading.
 */

#include <unistd.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include "util/no_sort.h"
#include "util/coloredout.h"
#include "point.h"
#include "kdtree.h"

using namespace std;

const int32_t _KDTree_maxPrintLen = 150;

template <int Dim>
void KDTree<Dim>::printTree(ostream& out /*cout*/ ,
                            colored_out::enable_t enable_bold /* = COUT */,
                            int modWidth /* =  -1*/) const
{
    // Base case
    if (root == NULL) {
        out << "(empty)" << endl;
        return;
    }

    // Make a character matrix for outputting the tree onto
    int rootData = getPrintData(root);
    int height = (Dim + 1) * rootData + Dim;
    int width;
    if (modWidth != -1)
        width = (4 << modWidth) - 3;
    else
        width = (4 << rootData) - 3;

    if (width + 6 > _KDTree_maxPrintLen) {
        out << "(tree too large for terminal)" << endl;
        return;
    }

    // Initialize this matrix to be filled with spaces
    vector<string> output(height);
    for (size_t i = 0; i < output.size(); i++)
        output[i] = string(width + 6, ' '); // extra room for long things

    // Recursively print each node
    printTree(root, output, 0, 0, width, 0);
    //nodeOut << std::unsetf(
    // Output the matrix
    int currd = 0;
    for (int row = 0; row < height;) {
        for (int d = 0; d < Dim + 1 && row < height; d++, row++) {
            if (d == currd)
                colored_out::output_bold_digits(output[row], out, enable_bold);//TODO: check what this does
            else
                out << output[row];
            out << endl;
        }
        currd = (currd + 1) % Dim;
    }
}

// Finds height of each node to determine the size of the output matrix
template <int Dim>
int KDTree<Dim>::getPrintData(KDTreeNode * subroot) const
{
    using std::max;
    if (subroot == NULL)
        return -1;
    return 1 + max(getPrintData(subroot->left),
                   getPrintData(subroot->right));
}

// Recursively prints tree to output matrix
template <int Dim>
void KDTree<Dim>::printTree(KDTreeNode * subroot, vector<string>& output,
                            int left, int top, int width, int currd) const
{
    // Convert data to string
    //int med = (low + high) / 2;

    vector<string> nodeStr;
    nodeStr.reserve(Dim);
    for (int dim = 0; dim < Dim; dim++) {
        std::ostringstream nodeOut;
        nodeOut << std::fixed << std::setprecision(0);

        Point<Dim> p = subroot -> point;
        if (dim == 0)
            nodeOut << (p.isMine() ? '{' : '(');
        else
            nodeOut << ' ';

        nodeOut << p[dim];
        if (dim == Dim - 1)
            nodeOut << (p.isMine() ? '}' : ')');
        else
            nodeOut << ',';

        nodeStr.push_back(nodeOut.str());
    }

    // Output data
    for (int dim = 0; dim < Dim; dim++)
        for (size_t i = 0;
             i < nodeStr[dim].length()
                 && (left + width / 2 + i < output[top + dim].length());
             i++)//TODO
            output[top + dim][left + width / 2 + i] = nodeStr[dim][i];

    // Calculate / \ offset = 2 ^ height
    int branchOffset = (width + 3) >> 3; //(1 << (node->printData - 1));

    // Print left child
    int center = left + width / 2;
    int leftcenter = left + (width / 2 - 1) / 2;
    int rightcenter = left + width / 2 + 2 + (width / 2 - 1) / 2;
    if (subroot->left != NULL) { //node->left  != NULL
        int branch_pos = center - branchOffset + 1;
        // draw left upper branch
        for (int pos = center - 1; pos > branch_pos; pos--)
            output[top + Dim - 1][pos] = '_';
        // draw left '/'
        output[top + Dim][branch_pos] = '/';
        // draw left lower branch
        for (int pos = branch_pos - 1; pos > leftcenter + 2; pos--)
            output[top + Dim][pos] = '_';
        // draw left subtree
        printTree(subroot->left, output, left, top + Dim + 1, width / 2 - 1,
                  (currd + 1) % Dim);
    }
    // Print right child
    if (subroot->right) { //node->right != NULL
        int branch_pos = center + branchOffset + 1;
        // draw right upper branch
        for (int pos = center + nodeStr[Dim - 1].length(); pos < branch_pos; pos++)
            output[top + Dim - 1][pos] = '_';
        // draw right '\'
        output[top + Dim][branch_pos] = '\\';
        // draw right lower branch
        for (int pos = branch_pos + 1; pos < rightcenter; pos++)
            output[top + Dim][pos] = '_';
        // draw right subtree
        printTree(subroot->right, output, left + width / 2 + 2, top + Dim + 1,
                  width / 2 - 1, (currd + 1) % Dim);
    }
}
