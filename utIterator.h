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

TEST(iterator, NullIterator){
  Number one(1);
  Iterator<Term *> *it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());

}


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
TEST(DFSIterator, StructNested){
  
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
  TEST(DFSIterator, List){
    
      Number one(1);
      
      Variable X("X");
      Number two(2);
      List l({ &X, &two });
      Iterator<Term *> *it = l.createDFSIterator();
      it->first();
      EXPECT_EQ("X",it->currentItem()->symbol());  
      it->next();
      ASSERT_FALSE(it->isDone());
      EXPECT_EQ("2",it->currentItem()->symbol());
      ASSERT_FALSE(it->isDone());    
      it->next();
      ASSERT_TRUE(it->isDone());
    }
TEST(DFSIterator, ListNested){
      
        Number one(1);
        
        Variable X("X");
        Variable Y("Y");  
        Number two(2);
        
        List l({ &X, &two });
        List l2({ &X, &l,&two });
    
        Iterator<Term *> *it = l2.createDFSIterator();
        it->first();
        ASSERT_FALSE(it->isDone());
        EXPECT_EQ("X",it->currentItem()->symbol());  
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
        EXPECT_EQ("2",it->currentItem()->symbol());
        it->next();
        ASSERT_TRUE(it->isDone());
        
        // it->next();
        // EXPECT_EQ("Y",it->currentItem()->symbol());
      
        
      }
TEST(BFSIterator, Struct){
        
          Number one(1);
          
          Variable X("X");
          Variable Y("Y");  

          Struct s(Atom("s"), { &one, &X, &Y });  

      
          Iterator<Term *> *it = s.createBFSIterator();
          it->first();
          ASSERT_FALSE(it->isDone());
          EXPECT_EQ("1",it->currentItem()->symbol());  
          it->next();
          ASSERT_FALSE(it->isDone());
          EXPECT_EQ("X",it->currentItem()->symbol());
          it->next();
          ASSERT_FALSE(it->isDone());    
          EXPECT_EQ("Y",it->currentItem()->symbol());
          it->next();
          ASSERT_TRUE(it->isDone());    

          
}
TEST(BFSIterator, StructNested){
  
   
  
  Variable X("X");
  Number two(2);
  Number one(1);
  
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("t"), { &X, &t, &one });

  Iterator<Term *> *it = s.createBFSIterator();
  it->first();
  ASSERT_FALSE(it->isDone());
  EXPECT_EQ("X",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("t(X, 2)",it->currentItem()->symbol());
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());  

    
}
TEST(BFSIterator, List){
  
   
  Variable X("X");
  Number two(2);
  Number one(1);
  Struct l(Atom("t"), { &X, &two });

  Iterator<Term *> *it = l.createBFSIterator();
  it->first();
  ASSERT_FALSE(it->isDone());
  EXPECT_EQ("X",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone()); 
  
    
}
TEST(BFSIterator, ListNested){
  
   
  
  Variable X("X");
  Number two(2);
  Number one(1);
  
  List l( { &X, &two });
  List l2( { &X,&l, &two });


  Iterator<Term *> *it = l2.createBFSIterator();
  it->first();
  ASSERT_FALSE(it->isDone());
  EXPECT_EQ("X",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("[X, 2]",it->currentItem()->symbol());
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("2",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("X",it->currentItem()->symbol());  
  it->next();
  ASSERT_FALSE(it->isDone()); 
  EXPECT_EQ("2",it->currentItem()->symbol());  
  it->next();
  ASSERT_TRUE(it->isDone()); 
  
    
}
  

#endif