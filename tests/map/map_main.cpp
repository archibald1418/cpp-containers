#include "tree.hpp"
#include "node.hpp"
#include "utils.hpp"

#include <iostream>

void MakeAVLCharTree(AVLNode<char>* &root) // changing pointers
{
  AVLNode<char> *a, *b, *c, *d, *e;

  e = new AVLNode<char>('E', NULL, NULL, 0);
  d = new AVLNode<char>('D', NULL, NULL, 0);
  c = new AVLNode<char>('C', e, NULL, -1);
  b = new AVLNode<char>('B', NULL, d, 1);
  a = new AVLNode<char>('A', b, c, 0);
  root = a; // <- that one
}


int main(){
	// Test nodes

using test::make_unique;
using test::unique_ptr;

	Node<int> baseNode;
	AVLNode<int> avlnode(8);

	// std::cout << avlnode.get_balance_factor() << std::endl;
	// std::cout << avlnode.get() << std::endl;

	AVLNode<char>* root = NULL;
	make_unique(root);
	

	MakeAVLCharTree(root);

	print_tree(root);

	return (0);
}
