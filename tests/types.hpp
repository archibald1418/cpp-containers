#ifndef TYPES_H
#define TYPES_H

# include <typeinfo>
# include <map>
# include <iostream>
# include <utility>

# include "Test.hpp"
# include "colors.hpp"

# define NTYPES 7


namespace test
{
    const char *Types[NTYPES] = {
        typeid(int).name(),
        typeid(char).name(),
        typeid(std::string).name(),
        typeid(test).name(),
        typeid(const char).name(),
        typeid(const int).name(),
        typeid(const std::string).name()
    };

    const char *TypeNames[NTYPES] = {
        "[int]",
        "[char]",
        "[string]",
        "[test]",
        "[const_char]",
        "[const_int]",
        "[const_string]"
    };

    enum Type {
        Int,
        Char,
        String,
        Test,
        ConstChar,
        ConstInt,
        ConstString
    };

typedef std::map<const char *, std::string> TypeRepr;

    
    struct CreateMap
    {
        struct CreateNode
        {
            const char *id;
            std::string value;

            operator TypeRepr::value_type() const
            {
                return std::pair<const char *, std::string>(id, value);
            }
        };

        static const CreateNode MapPairs[];
        static TypeRepr TheMap;
    };

    const CreateMap::CreateNode CreateMap::MapPairs[NTYPES] = {
        { Types[Int],            TypeNames[Int]},
        { Types[Char],           TypeNames[Char]},
        { Types[String],         TypeNames[String]},
        { Types[Test],           TypeNames[Test]},
        { Types[ConstChar],      TypeNames[ConstChar]},
        { Types[ConstInt],       TypeNames[ConstInt]},
        { Types[ConstString],    TypeNames[ConstString]}};

    TypeRepr CreateMap::TheMap(CreateMap::MapPairs, CreateMap::MapPairs + NTYPES);
    
}

#endif
