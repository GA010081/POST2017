#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>
using std::string;


//test Number.value()
TEST (Number,ctor) {
    Number Num1(1);
    ASSERT_EQ("1",Num1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number Num1(1);
    ASSERT_EQ("1",Num1.symbol());
    
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number  Num25(25);
    ASSERT_TRUE(Num25.match(Num25));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number  Num25(25);
    Number  Num0(0);
    ASSERT_FALSE(Num25.match(Num0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number  Num25(25);
    Atom    Tom("tom");
    ASSERT_FALSE(Num25.match(Tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Variable X("X");
    Number Num25(25);
    Number Num26(26);
    ASSERT_TRUE(Num25.match(&X));
    ASSERT_FALSE(Num26.match(&X));
    ASSERT_TRUE(Num25.match(&X));

}

// ?- tom=25.
// false.
TEST (Atom, matchFailureDiffConstant) {

    Atom Tom("tom");
    Number Num25(25);
    ASSERT_FALSE(Tom.match(&Num25));

}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom Tom("tom");
    Variable X("X");
    ASSERT_TRUE(Tom.match(&X));

}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom Jerry("jerry");
    Atom Tom("tom");
    Variable X("X");
    ASSERT_TRUE(Tom.match(&X));
    ASSERT_FALSE(X.match(Jerry));
    ASSERT_TRUE(X.match(Tom));
    
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom Tom("tom");
    Atom Jerry("jerry");
    Variable X("X");
    ASSERT_TRUE(Tom.match(&X));
    ASSERT_FALSE(Jerry.match(&X));
    ASSERT_TRUE(Tom.match(&X));

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable X("X");
    Number Num5(5);
    ASSERT_TRUE(X.match(Num5));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Number Num25(25);
    Number Num100(100);
    Variable X("X");
    ASSERT_TRUE(X.match(Num25));
    ASSERT_FALSE(X.match(Num100));
    ASSERT_TRUE(X.match(Num25));


}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Number Num25(25);
    Atom Tom("tom");
    Variable X("X");
    ASSERT_TRUE(X.match(Tom));
    ASSERT_FALSE(X.match(Num25));

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Number Num25(25);
    Atom Tom("tom");
    Variable X("X");
    ASSERT_TRUE(Tom.match(&X));
    ASSERT_FALSE(Num25.match(&X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Atom Tom("tom");
    Variable X("X");
    ASSERT_TRUE(X.match(Tom));
    ASSERT_TRUE(X.match(Tom));
    ASSERT_TRUE(Tom.match(&X));
    ASSERT_TRUE(Tom.match(&X));
}
#endif
