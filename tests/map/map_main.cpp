#include "tree.hpp"
#include "node.hpp"
#include "utils.hpp"

# include <cassert>

#include <iostream>
// #include <array> 



using ft::AVLNode;
using ft::Node;

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


ft::AVLTree<int>* ConstructAVLIntTree(AVLNode<int>* &root){
	using ft::AVLTree;

	AVLTree<int>* tree = new AVLTree<int>(root);


	print_tree(*tree);

	tree->Insert(11);
	// print_tree(tree);
	tree->Insert(7);
	// print_tree(tree);
	tree->Insert(12);
	// print_tree(tree);
	tree->Insert(4);
	// print_tree(tree);
	tree->Insert(2);
	// print_tree(tree);
	tree->Insert(-1);
	// print_tree(tree);
	tree->Insert(0);
	// print_tree(tree);
	tree->Insert(78);
	// print_tree(tree);
	tree->Insert(10);
	// print_tree(tree);
	tree->Insert(6);

	print_tree(*tree);

	return tree;
}

template <typename tree>
void	test_tree_next(tree* t){

	typedef typename tree::nodeptr nodeptr;

	std::cout << "Printing tree:" << std::endl;
	print_tree(*t);
// pretty print
	nodeptr n = t->tree_next(t->Root());
	print_node(n);
	nodeptr nn = t->tree_prev(n);
	print_node(nn);
	assert (nn == t->Root());

	nodeptr rmost = t->Rmost();
	print_node(rmost);
	nodeptr end = t->tree_next(rmost);
	nodeptr pend = t->tree_next(end);
	print_node(end);
	print_node(pend);

	print_adjacent_nodes(t->Root());
}

template <typename tree>
void test_tree_traverse(tree* t){
	typedef typename tree::nodeptr nodeptr;

	nodeptr tmp = t->Lmost();
	print_tree(*t);
	std::cout << "\tTraversing forwards" << std::endl;
	while (!IsPhony(tmp))
	{
		print_node(tmp, GREEN);
		tmp = t->tree_next(tmp);
	}
	std::cout << "\tTraversing backwards" << std::endl;
	tmp = t->Rmost();
	while (!IsPhony(tmp))
	{
		print_adjacent_nodes(tmp);
		tmp = t->tree_prev(tmp);
	}

	// subtrees
}

int main(){
	// Test nodes

// using test::make_unique;
using test::unique_ptr;
using ft::AVLTree;
using ft::tree_traits;

typedef 
	int
		type;

	// Node<int> baseNode;
	// AVLNode<int> avlnode(8);

	// std::cout << avlnode.get_balance_factor() << std::endl;
	// std::cout << avlnode.get() << std::endl;

	AVLNode<type>* root = ft::nullptr_my;
	// AVLTree<char> T(root);

	// MakeAVLCharTree(root);
	ft::AVLTree<type>* tree = ConstructAVLIntTree(root);
	test_tree_next(tree);
	test_tree_traverse(tree);
	
	delete tree;

	return (0);
}
