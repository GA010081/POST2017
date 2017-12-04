#include "struct.h"
#include "iterator.h"
#include "atom.h"
Iterator<Term *> * Struct::createIterator()
{
  return new StructIterator<Term*>(this);
}

Iterator<Term *> * Struct::createDFSIterator()
{
  prepareDFSStack();
  return new StructDFSIterator<Term*>(this);
}
Iterator<Term *> * Struct::createBFSIterator()
{
  prepareBFSStack();
  return new StructBFSIterator<Term*>(this);
}

