#ifndef PRINTTREE_H
#define PRINTTREE_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

// Curiously recurring template pattern
// You don't actually need to extend this class,
// but here are the functions you need to implement
template <class DerivedDescriptor>
class GenericNodeDescriptor
{
	public:
	virtual bool isNull() const = 0;
	virtual std::string key() const = 0;
	virtual DerivedDescriptor left() const = 0;
	virtual DerivedDescriptor right() const = 0;
};

namespace private_print_functions
{
	template <class NodeDescriptor>
	int getPrintHeight(NodeDescriptor croot);

	template <class NodeDescriptor>
	void printSubtree(NodeDescriptor croot,
			std::vector<std::string> & output,
			int left,
			int top,
			int curr_width);
}

template <class NodeDescriptor>
void printTree(NodeDescriptor root, std::ostream & out = std::cout)
{
	using namespace private_print_functions;

	// Base case
	if (root.isNull())
	{
		out << "(empty)" << std::endl;
		return;
	}

	// Make a character matrix for outputting the tree onto
	int root_height = getPrintHeight(root);
	int print_matrix_width = (4 << root_height) - 3;
	int print_matrix_height = 2 * root_height + 1;

	// Initialize this matrix to be filled with spaces
	std::vector<std::string> output(print_matrix_height);
	for (size_t i = 0; i < output.size(); ++i)
		output[i] = std::string(print_matrix_width + 4, ' '); // + 4 extra room for long things

	// Recursively print each node
	printSubtree(root, output, 0, 0, print_matrix_width);

	// Output the matrix
	for (int row = 0; row < print_matrix_height; ++row)
		out << output[row] << std::endl;
}

namespace private_print_functions
{
	template <class NodeDescriptor>
	int getPrintHeight(NodeDescriptor croot)
	{
		if (croot.isNull())
			return -1;
		int l_height = getPrintHeight(croot.left());
		int r_height = getPrintHeight(croot.right());
		return 1 + std::max(l_height, r_height);
	}


	template <class NodeDescriptor>
	void printSubtree(NodeDescriptor croot, std::vector<std::string> & output, int left, int top, int curr_width)
	{
		// Convert data to std::string
		std::string nodeStr = croot.key();
		
		// Output data
		int left_start_shift = 1 - (nodeStr.length()-1)/2;
		for (size_t i = 0; i < nodeStr.length() && left + curr_width/2 + i < output[top].length(); i++)
			output[top][left + curr_width/2 + left_start_shift + i] = nodeStr[i];
		
		// Calculate / \ offset = 2 ^ height
		int branchOffset = (curr_width+3) >> 3; //(1 << (node->printData - 1));
		
		// Print left child
		int center = left + curr_width/2;
		int leftcenter = left + (curr_width/2 - 1)/2;
		int rightcenter = left + curr_width/2 + 2 + (curr_width/2 - 1)/2;

		if (!croot.left().isNull())
		{
			int branch_pos = center - branchOffset + 1;
			// draw left upper branch
			for (int pos = center + left_start_shift - 2; pos > branch_pos; pos--)
				output[top][pos] = '_';
			// draw left '/'
			output[top+1][branch_pos] = '/';
			// draw left lower branch
			for (int pos = branch_pos-1; pos > leftcenter + 2; pos--)
				output[top+1][pos] = '_';
			// draw left subtree
			printSubtree(croot.left(), output, left, top+2, curr_width/2 - 1);
		}

		// Print right child
		if (!croot.right().isNull())
		{
			int branch_pos = center + branchOffset + 1;
			// draw right upper branch
			for (int pos = center + left_start_shift + nodeStr.length() + 1; pos < branch_pos; pos++)
				output[top][pos] = '_';
			// draw right '\'
			output[top+1][branch_pos] = '\\';
			// draw right lower branch
			for (int pos = branch_pos+1; pos < rightcenter; pos++)
				output[top+1][pos] = '_';
			// draw right subtree
			printSubtree(croot.right(), output, left + curr_width/2 + 2, top+2, curr_width/2 - 1);
		}
	}
}

#endif
