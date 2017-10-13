#include"term.h"
#include"atom.h"
#include"number.h"
#include"struct.h"

TEST(Atom,symbol)
{   
    Atom tom("tom");
    ASSERT_EQ("tom",tom.symbol());
}
TEST(Atom,match_Num)
{   
    Atom tom("tom");
    Number Num25(25);
    ASSERT_FALSE(tom.match(Num25));
}
TEST(Atom,match_DiffConst)
{   
    Atom tom("tom");
    Atom jerry("jerry");
    ASSERT_FALSE(tom.match(jerry));
}
TEST(Atom,match_SameConst)
{   
    Atom tom("tom");
    Atom tom2("tom");
    ASSERT_TRUE(tom.match(tom));
    ASSERT_TRUE(tom.match(tom2));
}
TEST(Number,symbol)
{   
    Number Num25(25);
    ASSERT_EQ("25",Num25.symbol());
}
TEST(Number,match_Atom)
{   
    Atom tom("tom");
    Number Num25(25);
    ASSERT_FALSE(Num25.match(tom));
}
TEST(Number,match_DiffNum)
{   
    Number Num25(25);
    Number Num26(26);
    ASSERT_FALSE(Num25.match(Num26));
}
TEST(Number,match_SameNum)
{   
    Number Num25(25);
    Number Num25_(25);
    ASSERT_TRUE(Num25.match(Num25));
    ASSERT_TRUE(Num25.match(Num25_));
}
TEST(Struct,name)
{   
    Atom tom("tom");
    Atom jerry("jerry");
    std::vector<Term*> v = {&tom,&jerry};
    Struct hobby(Atom("hobby"),v);
    ASSERT_EQ("hobby",hobby.name().symbol());
}