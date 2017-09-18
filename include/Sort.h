#include <list>
#include "Shapes.h"

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){

        shapeList->sort([](const Shape (*f), const Shape (*s)) { return f->perimeter() < s->perimeter(); });         
  }

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape (*f), const Shape (*s)) { return f->perimeter() > s->perimeter(); });    
}


  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList){

    shapeList->sort([](const Shape (*f), const Shape (*s)) { return f->area() < s->area(); });    


  }

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape (*f), const Shape (*s)) { return f->area() > s->area(); });    
  }
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    shapeList->sort([](const Shape (*f), const Shape (*s)) { return f->area()/f->perimeter() < s->area()/f->perimeter(); });  
  }
  
};
