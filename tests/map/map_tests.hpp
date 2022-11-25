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
		typedef const_iterator							Cit;
		typedef const_reverse_iterator					Crit;

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

		void	add_range(int a, int b, int value){
			for (int i = a; i < b; ++i){
				Map.insert(value_type(i, value));
			}
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
			// fill map
			int i;

			for (i = 0; i < 5; i++){
				Map.insert(value_type(i, 2 * i));
			}
			
			// non-const
				// direct
				for (It it = Map.begin(); it != Map.end(); ++it){
					// NOTE: bidir iterator doesn't have <>, only == != 
					std::cout <<
						"{" << it->first << " : "  <<
					it->second << "}" << std::endl;
				}

					// forward - backward
					It it = Map.begin();
					for (i = 0; i < 3; ++it, ++i){
						std::cout <<  "{" << it->first << " : "  << it->second << "}" << std::endl;
					}
					for (; i > 0; --it, --i){
						std::cout << "{" << it->first << " : "  <<	it->second << "}" << std::endl;
					}

				// reverse
				std::cout << "reverse " << std::endl;
				for (Rit rit = Map.rbegin(); rit != Map.rend(); ++rit){
					std::cout << "{" << rit->first << " : "  <<	rit->second << "}" << std::endl;
				}
					// forward - backward
					Rit rit = Map.rbegin();
					for (i = 0; i < 3; ++rit, ++i){
						std::cout <<  "{" << rit->first << " : "  << rit->second << "}" << std::endl;
					}
					for (; i > 0; --rit, --i){
						std::cout << "{" << rit->first << " : "  <<	rit->second << "}" << std::endl;
					}
					
					for (Rit rit = --Map.rend(); rit != Map.rbegin(); --rit){
						std::cout <<  "{" << rit->first << " : "  << rit->second << "}" << std::endl;
					}
					
					for (It it = --Map.end(); it != Map.begin(); --it){
						std::cout <<  "{" << it->first << " : "  << it->second << "}" << std::endl;
					}

			// const
			typename map_type::const_iterator cbegin = Map.begin();
			typename map_type::const_reverse_iterator crbegin = Map.rbegin();
			typename map_type::const_iterator cend = Map.end();
			typename map_type::const_reverse_iterator crend = Map.rend();

			// direct
			for (Cit cit = cbegin; cit != cend; ++cit){
				// NOTE: bidir iterator doesn't have <>, only == != 
				std::cout <<
					"{" << cit->first << " : "  <<
				cit->second << "}" << std::endl;
			}

				// forward - backward
				Cit cit = cbegin;
				for (i = 0; i < 3; ++cit, ++i){
					std::cout <<  "{" << cit->first << " : "  << cit->second << "}" << std::endl;
				}
				for (; i > 0; --cit, --i){
					std::cout << "{" << cit->first << " : "  <<	cit->second << "}" << std::endl;
				}

			// reverse
			std::cout << "reverse " << std::endl;
			for (Crit crit = crbegin; crit != crend; ++crit){
				std::cout << "{" << crit->first << " : "  <<	crit->second << "}" << std::endl;
			}
				// forward - backward
				Crit crit = crbegin;
				for (i = 0; i < 3; ++crit, ++i){
					std::cout <<  "{" << crit->first << " : "  << crit->second << "}" << std::endl;
				}
				for (; i > 0; --crit, --i){
					std::cout << "{" << crit->first << " : "  <<	crit->second << "}" << std::endl;
				}
		}

		void	test_map_erase(){
			add_range(1, 4, 0);
			/* iterator first = Map.begin();	// 1 */

			// XXX debug root case - middle case ok, end case ok
			/* Map.erase(--Map.end()); // should leave [1,2] */
			// TODO: add functional end-node
			
			print_map(Map);
		}

		void test_iterator_increment(){
			add_range(1, 10, 0);

			It last = --Map.end();
			It end = Map.end();

			std::cout << last->first << std::endl;
			std::cout << (++last == end) << std::endl;

			Rit rlast = --Map.rend();
			Rit rend = Map.rend();
			
			std::cout << rlast->first << std::endl;
			std::cout << (++rlast == rend) << std::endl;

			print_map(Map);
		}



	};

#endif
