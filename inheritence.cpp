 #include <iostream>
 #include <stdio.h>
 
 class Point
 {
 
 int x,y;
 public:
 Point(int atx,int aty ) ; // Constructor
 inline virtual ~Point() ; // Destructor
 virtual void Draw() ;
 }; 
 
 class Circle : public Point {
 
 	int radius;
 public:
 	Circle(int atx,int aty,int theRadius) ;
 	inline virtual ~Circle() ;
 	virtual void Draw() ;
 };
 
 
 Point ::Point(int atx,int aty) {
 	x = atx;
 	y = aty;
 }
 
 inline Point::~Point ( void ) { 
 	std::cout << "Point Destructor called\n";
 }
 
 void Point::Draw( void ) {
 	std::cout << "Point::Draw point at " << x << " " << y << std::endl;
 }
 
 
 Circle::Circle(int atx,int aty,int theRadius) : Point(atx,aty) {
 	radius = theRadius;
 }
 
 inline Circle::~Circle() {
 	std::cout << "Circle Destructor called" << std::endl;
 }
 
 void Circle::Draw( void ) {
 	Point::Draw() ;
 std::cout << "circle::Draw point " << " Radius "<< radius << std::endl;
 }
 
 int main() {
 	Circle ACircle(10,10,5) ;
 	ACircle.Draw() ;
 	return 0;
 }