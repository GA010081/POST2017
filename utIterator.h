#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term *> *it= s.createIterator();
  
  it->first();
  it->next();
  Iterator<Term *> *it2  = t.createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*>  *itList =l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

// TEST(iterator, NullIterator){
//   Number one(1);
//   NullIterator nullIterator(&one);
//   nullIterator.first();
//   ASSERT_TRUE(nullIterator.isDone());
//   Iterator * it = one.createIterator();
//   it->first();
//   ASSERT_TRUE(it->isDone());
// }


//DFS


TEST(DFSIterator, Struct){

  Number one(1);
  
  Variable X("X");
  Variable Y("Y");  
  Number two(2);
  
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });  
  Iterator<Term *> *it = t.createDFSIterator();
  it->first();
  ASSERT_FALSE(it->isDone());
  EXPECT_EQ("X",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone());  
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());  

}
TEST(DFSIterator, StructNested1){
  
    Number one(1);
    
    Variable X("X");
    Variable Y("Y");  
    Number two(2);
    
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });  

    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    EXPECT_EQ("1",it->currentItem()->symbol());  
    ASSERT_FALSE(it->isDone());
    it->next();
    EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());    
    it->next();
    EXPECT_EQ("X",it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());    
    it->next();
    EXPECT_EQ("2",it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());    
    it->next();
    EXPECT_EQ("Y",it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
    
    // it->next();
    // EXPECT_EQ("Y",it->currentItem()->symbol());
  
    
  }
  TEST(DFSIterator, StructNested2){
    
      Number one(1);
      
      Variable X("X");
      Variable Y("Y");  
      Number two(2);
      
      Struct t(Atom("t"), { &X, &two });
      Struct s(Atom("s"), { &one, &t, &Y });  
      Struct z(Atom("s"), { &one, &s, &Y });  
  
      Iterator<Term *> *it = z.createDFSIterator();
      it->first();
      ASSERT_FALSE(it->isDone());
      EXPECT_EQ("1",it->currentItem()->symbol());  
      ASSERT_FALSE(it->isDone());
      it->next();
      EXPECT_EQ("s(1, t(X, 2), Y)",it->currentItem()->symbol());
      ASSERT_FALSE(it->isDone());    
      it->next();
      EXPECT_EQ("1",it->currentItem()->symbol());
      ASSERT_FALSE(it->isDone());    
      it->next();
      EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
      ASSERT_FALSE(it->isDone());    
      it->next();
      EXPECT_EQ("X",it->currentItem()->symbol());
      it->next();
      ASSERT_FALSE(it->isDone());
      EXPECT_EQ("2",it->currentItem()->symbol());
      it->next();
      ASSERT_FALSE(it->isDone());
      EXPECT_EQ("Y",it->currentItem()->symbol());
      it->next();
      ASSERT_FALSE(it->isDone());
      EXPECT_EQ("Y",it->currentItem()->symbol());
      it->next();
      ASSERT_TRUE(it->isDone());
    }
TEST(DFSIterator, StructOfList){
      
        Number one(1);
        
        Variable X("X");
        Variable Y("Y");  
        Number two(2);
        
        List l({ &X, &two });
        Struct s(Atom("s"), { &one, &l, &Y });  
    
        Iterator<Term *> *it = s.createDFSIterator();
        it->first();
        ASSERT_FALSE(it->isDone());
        EXPECT_EQ("1",it->currentItem()->symbol());  
        ASSERT_FALSE(it->isDone());
        it->next();
        EXPECT_EQ("[X, 2]",it->currentItem()->symbol());
        ASSERT_FALSE(it->isDone());    
        it->next();
        EXPECT_EQ("X",it->currentItem()->symbol());
        ASSERT_FALSE(it->isDone());    
        it->next();
        EXPECT_EQ("2",it->currentItem()->symbol());
        ASSERT_FALSE(it->isDone());    
        it->next();
        EXPECT_EQ("Y",it->currentItem()->symbol());
        it->next();
        ASSERT_TRUE(it->isDone());
        
        // it->next();
        // EXPECT_EQ("Y",it->currentItem()->symbol());
      
        
      }

#endif