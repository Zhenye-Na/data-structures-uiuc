/**
 * @file huffman_tree.h
 * Definition of a Huffman Tree class.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date Summer 2012
 * @date Fall 2017
 */

#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <utility>
#include <sstream>
#include <map>
#include <string>
#include <ostream>

#include "printtree.h"
#include "frequency.h"
#include "binary_file_reader.h"
#include "binary_file_writer.h"

/**
 * HuffmanTree: class that represents a Huffman tree for encoding and
 * decoding files with Huffman coding.
 */
class HuffmanTree
{
  public:
    /**
     * Creates a HuffmanTree from a given set of Frequency objects.
     *
     * @param frequencies The Frequency objects for this tree.
     */
    HuffmanTree(std::vector<Frequency> frequencies);

    /**
     * Creates a HuffmanTree from a binary file that has been written
     * to compress the tree information.
     *
     * @param bfile The binary file to read our compressed tree
     *	information from
     */
    HuffmanTree(BinaryFileReader& bfile);

    /**
     * Copy constructor for Huffman Trees.
     *
     * @param other The HuffmanTree to copy.
     */
    HuffmanTree(const HuffmanTree& other);

    /**
     * Destructor for Huffman Trees.
     */
    ~HuffmanTree();

    /**
     * Assignment operator for HuffmanTree.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    const HuffmanTree& operator=(const HuffmanTree& rhs);

    /**
     * Decodes a given file into its string contents.
     *
     * @param bfile BinaryFileReader to read bits from.
     * @return The decoded contents of the file.
     */
    std::string decodeFile(BinaryFileReader& bfile);

    /**
     * Writes a string of data to the binary file using Huffman coding.
     *
     * @param data The string to be written.
     * @param bfile The binary file to write the string to.
     */
    void writeToFile(const std::string& data, BinaryFileWriter& bfile);

    /**
     * Writes a signle character to the binary file using Huffman
     * coding.
     *
     * @param c The character to be written.
     * @param bfile The binary file to write the character to.
     */
    void writeToFile(char c, BinaryFileWriter& bfile);

    /**
     * Writes a compressed version of the tree to the file.
     *
     * @param bfile The binary file to be written to.
     */
    void writeTree(BinaryFileWriter& bfile);

    /**
     * Prints each element in the tree in an in-order traversal.
     */
    void printInOrder() const;

    /**
     * Prints the tree to a stream.
     * @param out The stream to print to
     */
    void print(std::ostream& out) const;

  private:
    /**
     * TreeNode class: internal representation of the Huffman tree.
     * Done using linked memory.
     */
    class TreeNode
    {
      public:
        Frequency
            freq;        /**< Data for this TreeNode: contains a
                                  character and a frquency count. */
        TreeNode* left;  /**< Left child of this TreeNode. */
        TreeNode* right; /**< Right child of this TreeNode. */

        /**
         * Builds a new TreeNode with the given frequency as data.
         *
         * @param theFreq The Frequency to build this TreeNode
         *	with.
         */
        TreeNode(Frequency theFreq) : freq(theFreq), left(NULL), right(NULL)
        {
            // nothing
        }

        /**
         * Builds a new TreeNode with the given integer as its
         * frequency counter, used for building internal nodes.
         *
         * @param frequency The frequency for this internal node.
         */
        TreeNode(int frequency) : freq(frequency), left(NULL), right(NULL)
        {
            // nothing
        }
    };

    /**
     * Private helper function that copies another HuffmanTree.
     *
     * @param other The HuffmanTree to be copied.
     */
    void copy(const HuffmanTree& other);

    /**
     * Recursive, private helper function that copies a given subtree
     * of another HuffmanTree.
     *
     * @param current The root of the subtree in the other HuffmanTree
     *	to be copied.
     * @return A pointer to the root of the new, copied subtree.
     */
    TreeNode* copy(const TreeNode* current);

    /**
     * Recursive, private helper function that frees all memory
     * associated with a subtree of the HuffmanTree.
     *
     * @param current The root of the subtree to free data from.
     */
    void clear(TreeNode* current);

    /**
     * Helper function used by the constructor to build a HuffmanTree
     * for a collection of Frequency data. Each Frequency object
     * represents a character and how often it appears in the data to
     * be encoded.
     *
     * @param frequencies The set of Frequency objects to build the
     *	tree with.
     */
    void buildTree(const std::vector<Frequency>& frequencies);

    /**
     * Helper function used by the constructor to build a HuffmanTree
     * from a compressed version of the tree written in a binary file.
     *
     * @param bfile The binary file we are reading.
     * @return A pointer to the root of the subtree built.
     */
    TreeNode* readTree(BinaryFileReader& bfile);

    /**
     * Recursive helper function used by the constructor to build a map
     * of characters to their encoded values based on the tree
     * structure built.
     *
     * @param current The current node we are visiting.
     * @param path The current path we have taken to get to this node.
     *	Used to store the encoded value for the characters of the tree.
     */
    void buildMap(TreeNode* current, std::vector<bool>& path);

    /**
     * Private helper for printing a tree in order.
     * @param current The current subRoot
     */
    void printInOrder(const TreeNode* current) const;

    /**
     * Helper function: finds the smallest element on the two queues
     * and removes it. In the event that there is a tie, it should
     * remove the front of the **singleQueue**.
     *
     * @param singleQueue The first queue to inspect.
     * @param mergeQueue The second queue to inspect.
     * @return A pointer to the smallest TreeNode that used to be at
     *	the front of one of the queues.
     */
    TreeNode* removeSmallest(std::queue<TreeNode*>& singleQueue,
                             std::queue<TreeNode*>& mergeQueue);

    /**
     * Determines the encoded value for a given character.
     *
     * @param c The character to find the encoded value for.
     * @return The encoded value for that character.
     */
    std::vector<bool> getBitsForChar(char c);

    /**
     * Helper function that decodes a file by traversing the tree based on
     * the bits read.
     *
     * @param ss The stringstream being used to build the decoded
     *	output string.
     * @param bfile The binary file we are decoding.
     */
    void decode(std::stringstream& ss, BinaryFileReader& bfile);

    /**
     * Helper function to write the tree out to a binary file in a
     * compressed way.
     *
     * @param current The root of the subtree we are currently writing.
     * @param bfile The fiel we are writing to.
     */
    void writeTree(TreeNode* current, BinaryFileWriter& bfile);

    /**
     * Private helper to get the height of the HuffmanTree.
     * @param subRoot Where we're currently at.
     * @return the height of the tree
     */
    int height(const TreeNode* subRoot) const;

    /**
     * Maximum height of trees to enable printing for
     * (chosen by fair dice roll)
     */
    const static int _max_print_height = 9;

    /**
     * Root of the HuffmanTree.
     */
    TreeNode* root_;                            

    /**
     * Standard map that maps characters to their encoded values.
     */
    std::map<char, std::vector<bool>> bitsMap_; 
};
#endif
