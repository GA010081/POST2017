#include"struct.h"
#include<vector>
#include"atom.h"

TEST(Struct, Match_Atom_UseTerm)
{
    Atom Tom("tom");
    Atom Jerry("jerry");
    std::vector<Term*> v = {&Tom,&Jerry};
    Struct hobby("hobby" , v);
    ASSERT_EQ("hobby",hobby.value());
    ASSERT_EQ("tom",hobby.index(0)->value());
    ASSERT_EQ("jerry",hobby.index(1)->value());

}