#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

# include "utils.hpp"
# include "pick_map.hpp"

	template<typename Key, typename Val>
	class TestMap
	{
		typedef map<Key, Val>						map_type;
		typedef typename map_type::value_type			value_type;
		typedef typename map_type::const_iterator		const_iterator;
		typedef typename map_type::iterator		iterator;
		typedef iterator								It;

		typedef pair<iterator, bool>				pair_ib;
		typedef pair<iterator, iterator>			pair_ii;
		
	public:
		map_type	Map;

	public:
		void	test_map_insert()
		{
			// Adds these
			Map.insert(value_type(0, 5));
			Map.insert(value_type(3, 5));
			Map.insert(value_type(2, 3));
			Map.insert(value_type(1, 3));

			// Doesn't add these
			Map.insert(value_type(0, 3));
			Map.insert(value_type(0, 3));
			Map.insert(value_type(3, 3));
			Map.insert(value_type(1, 3));
		}

		template <typename K, typename V>
		void	test_map_iterator(){
			
			ft::map<K, V> Map;
		}

		template<>
		void	test_map_iterator<int, int>(){
			
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
			 */
		}
	};

#endif
