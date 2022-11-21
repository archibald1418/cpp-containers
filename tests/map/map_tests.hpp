#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP

# include "utils.hpp"
# include "pick_map.hpp"
# include <vector>

	template<typename Key, typename Val>
	class TestMap
	{
		typedef map<Key, Val>									map_type;
		typedef typename map_type::value_type					value_type;
		typedef typename map_type::const_iterator				const_iterator;
		typedef typename map_type::iterator						iterator;
		typedef typename map_type::reverse_iterator				reverse_iterator;
		typedef typename map_type::const_reverse_iterator		const_reverse_iterator;

		typedef iterator								It;
		typedef reverse_iterator						Rit;

		typedef pair<iterator, bool>				Pair_ib;
		typedef pair<iterator, iterator>			Pair_ii;
		
	public:
		map_type	Map;

	public:
		void	print_pair_ii(const Pair_ii& pair_ii){
			std::cout << "[ " << *pair_ii.first << " ; " << *pair_ii.second << " )\n";
		}
		void	print_pair_ib(const Pair_ib& pair_ib){
			std::string status[2] = {std::string("Not inserted"), std::string("Inserted ok")};

			std::cout << "? " << *pair_ib.first << " : " << status[pair_ib.second] << " ?\n";
		}
		
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

			// range insert
			using std::vector;
			vector<value_type> tmp;
			for (int i = -5; i < 0; ++i){
				tmp.push_back(value_type(i, -1)); // {-5, -1}, {-4, -1}...
			}
			Map.insert(tmp.begin(), tmp.end());
		}

		void	test_map_iterator()
		{
			
			for (int i = 0; i < 10; i++){
				Map.insert(value_type(i, 2 * i));
			}

			// forward
			for (It it = Map.begin(); it != Map.end(); ++it){
				// NOTE: bidir iterator doesn't have <>, only == != 
				std::cout <<
					"{" << it->first << " : "  <<
				it->second << "}" << std::endl;
			}

			// forward - backward
			int i = 0;
			It it = Map.begin();
			for (; i < 3; ++it, ++i){
				std::cout <<  "{" << it->first << " : "  << it->second << "}" << std::endl;
			}
			for (; i > 0; --it, --i){
				std::cout << "{" << it->first << " : "  <<	it->second << "}" << std::endl;
			}

			std::cout << "reverse " << std::endl;
			// reverse
			for (Rit rit = Map.rbegin(); rit != Map.rend(); ++rit){
				std::cout << "{" << rit->first << " : "  <<	rit->second << "}" << std::endl;
			}
		}


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
	};

#endif
