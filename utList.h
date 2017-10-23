#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List l;
  l.symbol();
  ASSERT_EQ("[]",l.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
  Number num8128(8128);
  std::vector<Term *> v={&num8128};
  List l(v);
  ASSERT_EQ("[8128]",l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> v={&terence_tao,&alan_mathison_turing};
  List l(v);
  ASSERT_EQ("[terence_tao, alan_mathison_turing]",l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v={&X,&Y};
  List l(v);
  ASSERT_EQ("[X, Y]",l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Variable X("X");
  Atom tom("tom");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  List l(v);
  ASSERT_FALSE(tom.match(l));
  ASSERT_FALSE(l.match(tom));


}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Variable X("X");
  Number num8128(8128);
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  List l(v);
  ASSERT_FALSE(num8128.match(l));
   ASSERT_FALSE(l.match(num8128));

}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  std::vector<Term *> v2={&X};
  List l(v);
  Struct s(Atom("s"),v2);
  ASSERT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  List l(v);

  ASSERT_TRUE(l.match(Y));
  ASSERT_TRUE(Y.match(l));
  ASSERT_EQ("[496, X, terence_tao]",Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable X("X");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  List l(v);
  ASSERT_FALSE(X.match(l));
  ASSERT_FALSE(l.match(X)); 
  ASSERT_EQ("X",X.value());
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Variable X("X");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  List l(v);
  ASSERT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  std::vector<Term *> v2={&num496,&Y,&terence_tao};
  List l(v);
  List l2(v2);
  ASSERT_TRUE(l.match(l2));
 

}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Variable X("X");
  Number num8128(8128);
  Atom terence_tao("terence_tao");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  std::vector<Term *> v2={&num496,&num8128,&terence_tao};
  List l(v);
  List l2(v2);
  ASSERT_TRUE(l.match(l2));
  ASSERT_EQ("[496, 8128, terence_tao]",l.value()); 
  ASSERT_EQ("[496, 8128, terence_tao]",l2.value());
  ASSERT_EQ("8128",X.value());

}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  Number num496(496);
  std::vector<Term *> v={&num496,&X,&terence_tao};
  std::vector<Term *> v2={&num496,&alan_mathison_turing,&terence_tao};
  List l(v);
  Y.match(l);
  X.match(alan_mathison_turing);
  List l2(v2);
  ASSERT_EQ("alan_mathison_turing",X.value());
  // ASSERT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
  ASSERT_TRUE(l.match(l2));
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->symbol());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f};
  List l(args);
  vector<Term *> args2 = {&l,&s,&t};
  List l2(args2);
  EXPECT_EQ(string("[first]"), l2.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l2.tail()->symbol());

}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());

}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l;
 try{
  EXPECT_EQ(string("Accessing head in an empty list"), l.head()->value());
 }
   catch(std::string &e){
  EXPECT_EQ("Accessing head in an empty list",e);
}
 

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l;
 try{
  EXPECT_EQ(string("Accessing tail in an empty list"), l.tail()->value());
 }
     catch(std::string &e){
  EXPECT_EQ("Accessing tail in an empty list",e);
}
 
}




#endif
