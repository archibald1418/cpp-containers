#include "tree.hpp"
#include "node.hpp"
#include "utils.hpp"
#include "map.hpp"

# include <cassert> 
#include <iostream>
// #include <array> // absent from c++98

using ft::AVLNode;
using ft::Node;
using ft::nullptr_my;

template <typename Key, typename Val>
void	test_map_typedefs (void){
	
	ft::map<Key, Val> Map;

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
template <>
void	test_map_iterator<int, int>(){
	
	typedef ft::map<int, int> map_type;
	typedef map_type::iterator It;
	typedef map_type::value_type value_type;
	typedef ft::pair<It, bool> return_type;

	map_type Map;

	for (int i = 0; i < 10; i++){
		return_type ret(
			Map.insert(value_type(i, 2 * i))
		);
	}

	print_map_tree(Map);

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
	test_map_iterator<int, int>();
	/* delete tree; */

	return (0);
}
