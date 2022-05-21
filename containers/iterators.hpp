#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>

namespace ft{

	// Explicitly Parametric iterator
	template<class T,
			class C = std::random_access_iterator_tag,
			class Dist = ptrdiff_t,
			class Pt = T*,
			class Rt = T&>
		struct iterator {
			// Type defenitions for addressing and manipulating allocated objects
			typedef C iterator_category;
			typedef T value_type;
			typedef Dist difference_type;
			typedef Pt pointer;
			typedef Rt reference;
		};

	// Copy iterator template
	template<class It> 
		struct iterator_traits {
			typedef typename It::iterator_category      iterator_category;
			typedef typename It::value_type             value_type;
			typedef typename It::distance_type          distance_type;
			typedef typename It::pointer                pointer;
			typedef typename It::reference              reference;
		};

	// Define iterator in terms of type
	template <class T>
		struct iterator_traits<T*>{
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t distance_type;
			typedef T* pointer;
			typedef T& reference;
		};

};

#endif 
