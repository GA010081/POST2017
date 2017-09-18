#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Sort.h"
#include <algorithm>


TEST (Sort, sortByIncreasingPerimeter) {
    Circle cir0(0,0,1);

    Circle cir1(0,0,2);

    Rectangle Rect1(0,0,4,4);


    std::list<Shape * > Shapes ;
  
    Shapes.push_back (&Rect1); 
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);


    Sort sor1; 
    sor1.sortByIncreasingPerimeter(&Shapes);
    std::list<Shape *>::iterator it=Shapes.begin();

    ASSERT_EQ(cir0.perimeter(),(*it)->perimeter());
    it++;
    ASSERT_EQ(cir1.perimeter(),(*it)->perimeter());
    it++;
    ASSERT_EQ(Rect1.perimeter(),(*it)->perimeter());

}
      

TEST (Sort, sortByDecreasingPerimeter) {

    Circle cir0(0,0,1);

    Circle cir1(0,0,2);

    Rectangle Rect1(0,0,4,4);


    std::list<Shape * > Shapes ;
  
    Shapes.push_back (&Rect1); 
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);


    Sort sor1; 
    sor1.sortByDecreasingPerimeter(&Shapes);
    std::list<Shape *>::iterator it=Shapes.begin();

    ASSERT_EQ(Rect1.perimeter(),(*it)->perimeter());
    it++;
    ASSERT_EQ(cir1.perimeter(),(*it)->perimeter());
    it++;
    ASSERT_EQ(cir0.perimeter(),(*it)->perimeter());


}

TEST (Sort, sortByIncreasingArea) {
    Circle cir0(0,0,1);

    Circle cir1(0,0,2);

    Rectangle Rect1(0,0,4,4);


    std::list<Shape * > Shapes ;
  
    Shapes.push_back (&Rect1); 
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);


    Sort sor1; 
    sor1.sortByIncreasingArea(&Shapes);
    std::list<Shape *>::iterator it=Shapes.begin();

    ASSERT_EQ(cir0.area(),(*it)->area());
    it++;
    ASSERT_EQ(cir1.area(),(*it)->area());
    it++;
    ASSERT_EQ(Rect1.area(),(*it)->area());

}

TEST (Sort, sortByDecreasingArea) {
     Circle cir0(0,0,1);

    Circle cir1(0,0,2);

    Rectangle Rect1(0,0,4,4);


    std::list<Shape * > Shapes ;
  
    Shapes.push_back (&Rect1); 
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);


    Sort sor1; 
    sor1.sortByDecreasingArea(&Shapes);
    std::list<Shape *>::iterator it=Shapes.begin();

    ASSERT_EQ(Rect1.area(),(*it)->area());
    it++;
    ASSERT_EQ(cir1.area(),(*it)->area());
    it++;
    ASSERT_EQ(cir0.area(),(*it)->area());

}

TEST (Sort, sortByIncreasingCompactness) {
    
    Circle cir0(0,0,1);

    Circle cir1(0,0,2);

    Rectangle Rect1(0,0,4,4);


    std::list<Shape * > Shapes ;
  
    Shapes.push_back (&Rect1); 
    Shapes.push_back (&cir1);
    Shapes.push_back (&cir0);


    Sort sor1; 
    sor1.sortByIncreasingCompactness(&Shapes);
    std::list<Shape *>::iterator it=Shapes.begin();

    ASSERT_EQ(cir0.area()/cir0.perimeter(),(*it)->area()/(*it)->perimeter());
    it++;
    ASSERT_EQ(cir1.area()/cir1.perimeter(),(*it)->area()/(*it)->perimeter());
    it++;
    ASSERT_EQ(Rect1.area()/Rect1.perimeter(),(*it)->area()/(*it)->perimeter());

}

#endif
