#ifndef UTTERM_H
#define UTTERM_H

#include "Number.h"
#include "Atom.h"
#include "Variable.h"

//test Number.value()
TEST (Number,ctor) {
    Number Num1(1);
    ASSERT_EQ(1,Num1.value());
}
//test Number.symbol()
TEST (Number, symbol) {

}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number  Num25(25);
    ASSERT_TRUE(Num25=Num25);
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number  Num25(25);
    Number  Num0(0);
    ASSERT_FALSE(Num25= Num0);
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number  Num25(25);
    Atom    Tom("tom");
    ASSERT_FALSE(Num25 = Tom);
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Variable X("X");
    Number Num25(25);
    ASSERT_TRUE(Num25 = X);
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {

    Atom Tom("tom");
    Number Num25(25);
    ASSERT_FALSE(Tom = Num25);

}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {

}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {

}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

}
#endif
