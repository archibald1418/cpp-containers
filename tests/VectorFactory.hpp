#ifndef VECTORFACTORY_H
# define VECTORFACTORY_H

#include "pick_vector.hpp"
#include "utils.hpp"
#include "Test.hpp"
#include <random>

namespace test{

  template <typename T>
  class VectorFactory
  {
    public:
      typedef T value_type;
      typedef vector<value_type> Container;
      typedef Container* pointer;

      template <typename V>
        struct ifactory{
          static pointer create(void){
            return VectorFactory::create(V());
          }
          static void add(Container& c, V& v){
            VectorFactory::add(c, v);
          }
        };

        typedef struct ifactory<value_type> factory;

        VectorFactory(){};
        virtual ~VectorFactory(){};

    private:

        static void add(Container& C, char& v){
          C.push_back(v);
        }
        static void add(Container& C, int& v){
          C.push_back(v);
        }
        static void add(Container& C, std::string& v){
          C.push_back(v);
        }
        

        static Container* create(char){
          Container* cc = new Container;

          Container& c = *cc;

          c.push_back('H');c.push_back('e');
          c.push_back('l');c.push_back('l');c.push_back('o');

          c.push_back(',');c.push_back(' ');

          c.push_back('W');c.push_back('o');
          c.push_back('r');c.push_back('l');c.push_back('d');

          c.push_back('!');      

          return cc;
        };

        static Container* create(int){
          Container* c = new Container;
          ::create_vector_of_ints(*c, 10); 
          return c;
        };
      
        static Container* create(std::string){
          Container* cc = new Container;
          Container& c = *cc;
          c.push_back("Hello");
          c.push_back("This");
          c.push_back("Is");
          c.push_back("Dog");
          return cc;
        };

      static Container* test_create_vector_custom_type(test my_obj)
      {
        Container* cc = new Container;
        Container& c = *cc;

        for (int i = 0; i < 10; ++i){
          c.push_back(my_obj);
          my_obj++;
        }
        return cc;
      }

  };

  template <typename T>
  struct factory_type{
    typedef VectorFactory<T> type;
  };
};

#endif