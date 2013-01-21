 // example one
 #include <iostream>
 #include <stdio.h>
 using namespace std;

 class Book
 	{
 	int PageCount;
 	int CurrentPage; 
 	public:
 	Book( int Numpages) ; // Constructor
 	~Book(){/*cout<<"Destructor called"<<endl;*/} ; // Destructor
 	void SetPage( int PageNumber) ;
 	int GetCurrentPage( void ) ;
 	}; 
 
 Book::Book( int NumPages) {
 	PageCount = NumPages;
 }
 
 void Book::SetPage( int PageNumber) {
 	CurrentPage=PageNumber;
 }
 
 int Book::GetCurrentPage( void ) {
 	return CurrentPage;
 }
 
 int main() {
 	Book ABook(128) ;
 	ABook.PageCount = 9;
 	ABook.SetPage( 56 ) ;
 	cout << "Current Page " << ABook.GetCurrentPage() << endl;
 	return 0;
 }