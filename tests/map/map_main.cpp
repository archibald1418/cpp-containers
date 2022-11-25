#include "tree.hpp"
#include "node.hpp"
#include "utils.hpp"
#include "map.hpp"

#include "pick_map.hpp"

# include <cassert> 
#include <iostream>
// #include <array> // absent from c++98

#include "map_tests.hpp"


using ft::AVLNode;
using ft::Node;

using ft::nullptr_my;

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


	print_tree(tree);

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

	print_tree(tree);

	return tree;
}

template <typename tree>
void	test_tree_next(tree* t){

	typedef typename tree::nodeptr nodeptr;

	std::cout << "Printing tree:" << std::endl;
	print_tree(t);
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
	print_tree(t);
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

template <typename tree>
void test_tree_delete(tree* t){
	print_tree(t);

	t->Delete(0);

	print_tree(t);
}

template <typename tree>
void test_empty_tree() {
	
	/* AVLNode<int>* root = ft::nullptr_my; */
	/* AVLTree<char> T(root); */
	/* delete tree; */
}

template <typename Key, typename Val>
void	test_map_typedefs (void){
	
	ft::map<Key, Val> Map;

	/* print_tree(Map.call_root()); */
	print_tree(Map.getRoot());
}

template <typename Key, typename Val>
void	test_map_insert(){
	
	ft::map<Key, Val> Map;
}

template <typename Key, typename Val>
void	test_map_iterator(){
	
	ft::map<Key, Val> Map;


}

template<>
void	test_map_iterator<int, int>(){
	
	typedef map<int, int> map_type;
	/* typedef map<int, int> map_type; */
	typedef map_type::iterator It;
	typedef map_type::value_type value_type;
	/* typedef pair<It, bool> return_type; */

	map_type Map;

	for (int i = 0; i < 10; i++){
		Map.insert(value_type(i, 2 * i));
	}

	/* print_map_tree(Map); */
	for (It it = Map.begin(); it != Map.end(); ++it){
		// NOTE: bidir iterator doesn't have <>, only == != 
		std::cout <<
			"{" << it->first << " : "  <<
		it->second << "}" << std::endl;
	}

	// TODO: check for similar keys - shouldn't insert (or what? check sys)
	// 
	/* TODO: equal range - lower b - upper b can just be like this:
	 * 
	 * equal range:
	 * - call find
	 * - increment
	 * - return pair<found, next_to_found>
	 * 
	 * lower bound:
	 * - call find
	 * - return found
	 *
	 * upper bound:
	 * - call find
	 * - return next_to_found
	*/

	// TODO: erase: just call the deleter

}

template<typename Pair_ii>
void	print_pair_ii(const Pair_ii& pair_ii){
	std::cout << "* " << *pair_ii.first << " : " << *pair_ii.second << " *\n";
}
template<typename Pair_ib>
void	print_pair_ib(const Pair_ib& pair_ib){
	std::cout << "? " << *pair_ib.first << " : " << pair_ib.second << " ?\n";
}

void 	test_map_ranges(){
	
	typedef map<int, int> map_type;
	//typedef pair<map_type::iterator, map_type::iterator> pair_ii;	
	//typedef pair<map_type::iterator, bool> 	pair_ib;	
	typedef map_type::value_type		value_type;

	map_type Map;
	/* int f = 1; */
	int i = 5;
	Map.insert(value_type(i , i));
	for (; i < 15; i+=3){
		Map.insert(value_type(i - 2, i));
		Map.insert(value_type(i + 2, i));
		Map.insert(value_type(i - 1, i));
		Map.insert(value_type(i + 1, i));

	} 
	print_map(Map);
	/* print_tree(Map.getRoot()); */
}


int main(){
	// Test nodes

// using test::make_unique;
using test::unique_ptr;
using ft::AVLTree;
using ft::tree_traits;

	/* AVLNode<int>* root = ft::nullptr_my; */
	/* AVLTree<char> T(root); */

	// MakeAVLCharTree(root);
	/* ft::AVLTree<int>* tree = ConstructAVLIntTree(root); */
	/* test_tree_next(tree); */
	/* test_tree_traverse(tree); */
	/* test_tree_delete(tree); */
	
	/* test_map_typedefs<std::string, int>(); */
	//test_map_iterator<int, int>();
	/* test_map_ranges(); */
	
	TestMap<int, int> t;
	/* t.test_map_insert(); */
	/* print_map_tree(t.Map); */
	/* print_map(t.Map); */
	/* t.test_map_iterator(); */

	/* delete tree; */
	t.test_map_erase();
	/* t.test_iterator_increment(); */

	return (0);
}
