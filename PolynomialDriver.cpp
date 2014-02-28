#include "Polynomial.h"
#include <iostream>

using namespace std;
//Assumptions about main:  All public functions, operators, and constructors should be tested.  The correctness of the overloaded << operator can be determined by 
//using it and visually checking that it displays Polynomials as expected. Actual results of functions should be tested against expected results using == operator 
//when possible. Correctness of == operator can be determined by creating a deep copy of a Polynomial and comparing the original to the deep copy.  The correctness of
//the deep copy method can be determined by first visually checking if all terms are displayed as expected, then ensuring that a change made to the deep copy
//does not effect the original, and that a change made to the original does not effect the deep copy. The correctness of the deconstructor can be determined using
//valgrind.  Two Polynomials created with default constructor should be equivalent.  If the same parameters are used in the changeCoefficient function for two
//equivalent Polynomials, they are still equivalent.  Two Polynomials with the same terms are equal. Two Polynomials with one or more unlike terms are not equal.
//I did not need to create a User Interface for the Polynomial class; a script is sufficient.
int main( ) 
{
  Polynomial p1;	//create empty Polynomial p1 using default constructor
  cout << "p1 = " << p1 << endl; 
  p1.changeCoefficient( 1, 1 );  //add term x to p1
  p1.changeCoefficient( 4, 4 );  //add term 4x^4 to p1
  p1.changeCoefficient( 2.2, 2 );  //add term 2.2x^2 to p1
  p1.changeCoefficient( -3.8, 3 );	//add term -3.8x^3 to p1
  p1.changeCoefficient( 0 , 9 );
  p1.changeCoefficient( 5, -6);

  cout << "p1 should equal:  4x^4 - 3.8x^3 + 2.2x^2 + x" << endl; 
  cout << "p1 = " << p1 << endl;  //check overloaded << operator against expected result above
  cout << "it appears that the default constructor and changeCoefficient work correctly " << endl;  //assume based on result
  cout << "removing 2.2x^2 from p1 using changeCoefficient()" << endl;
  cout << "p1 should now equal 4x^4 - 3.8x^3 + x" << endl;
  
  p1.changeCoefficient( 0, 2 );  //Test remove
  
  Polynomial rt;
  rt.changeCoefficient(-23, 3 );

  cout << "rt = " << rt << endl;  

  Polynomial asdf;
  asdf += p1;
  cout << " += p1 = " << asdf << endl;
  Polynomial g1;
  g1 -= asdf;
  cout << " -= p1 " << g1 << endl;

  cout << "p1 = " << p1 << endl;  //Visually inspect to show remove works
  cout << "creating a deep copy of Polynomial p1 and assigning it to Polynomail p2 using default constructor and = operator" << endl;
  
  Polynomial p2 = p1;

  cout << "p2 = " << p2 << endl;  //visually inspect result of deep copy using = operator.
  cout << "p1 = p2, but what is the result of the == operator?" << endl;

  if(p2 == p1) //test == operator
	cout << " True! The == operator works!" << endl;
  else if(p2 != p1)
	cout << "Error with == operator!" << endl;	
  
  cout << "adding 9.5x^2 to p2" << endl;
  
  p2.changeCoefficient( 9.5, 2 );  //test deep copy
  
  cout << "p1 is the same, p1 = " << p1 << endl;
  cout << "Now, p2 = " << p2 << endl;
  cout << "now p1 != p2 what is the result of the != operator?" << endl;
  if(p1 != p2)  //test != operator and deep copy
	cout << " TRUE! The != operator works, and we have also demonstrated that the = assignment operator creates " <<
		"a deep, not a shallow copy" << endl;
  else if(p1 == p2) //2nd test of == operator and deep copy
	cout << " FALSE!!! There is an error with the != operator, or the = operator" << endl; 

  Polynomial p3 = p1 + p2; //test + operator

  cout << "adding p1 + p2 with + operator, and assigning sum to p3" << endl;
  cout << "expected result: 8x^4 - 7.6x^3 + 9.5x^2 + 2x" << endl;
  cout << "creating Polynomial pA = expected result" << endl;

  Polynomial pA;  //create Polynomial containing expected result
  pA.changeCoefficient(8,4);
  pA.changeCoefficient(-7.6,3);
  pA.changeCoefficient(9.5,2);
  pA.changeCoefficient(2,1);

  cout << "p3 = " << p3 << endl;  //ensure p3 == expected result
  cout << "Testing p3 == pA" << endl;
  if(p3 == pA)  //assume if p3 == pA == expected result assume + operator is working
	cout << " + operator appears to work" << endl;
  else
	cout << "Huston we have a problem!" << endl;

  Polynomial p4;  //create p4
  p4.changeCoefficient(9, 8);
  p4.changeCoefficient(2, 1);
  p4.changeCoefficient(-4,0);
  p4.changeCoefficient(7,2);		
  p4.changeCoefficient(4,3);

  cout << "Created p4, p4 = " << p4 << endl;
  cout << "Subtracting p3 from p4 and assigning difference to p5" << endl;
  cout << "expected result: 9x^8 - 8x^4 + 11.6x^3 - 2.5x^2 - 4" << endl;
  cout << "creating Polynomial pB == expected result" << endl;

  Polynomial p5 = p4 - p3;  //test - operator

  Polynomial pB;  //create Polynomial pB containing expected result
  pB.changeCoefficient(9,8);
  pB.changeCoefficient(-8,4);
  pB.changeCoefficient(11.6,3);
  pB.changeCoefficient(-2.5,2);
  pB.changeCoefficient(-4,0);

  cout << "p5 = " << p5 << endl;  //ensure p5 == expected result
  cout << "Testing p5 == pB" << endl;
  if(p5 == pB)  //assume if p5 == pb == expected result - operator is working
	cout << " - operator appears to work" << endl;
  else
	cout << "Huston we have a problem!" << endl;
  
  cout << "setting p4 == to p5 using -= operator" << endl;
  cout << "p4 -= p3 = " << (p4 -= p3) << endl;  
  cout << "p4 = " << p4 << endl;
  cout << "p5 = " << p5 << endl;
  cout << "p4 == p5? " << endl;
  
  if(p4 == p5)  //assume if p4 = p4 - p3 = p5, -= operator is working
	cout << "TRUE, -= operator appears to be working" << endl;
  else if(p4 != p5)
	cout << "False, -= operator not working!" << endl;
  cout << "setting p1 == p3 using += operator" << endl;
  cout << "p1 += p2 = " << (p1 += p2) << endl;
  cout << "p1 == p3? " << endl;
  if(p1 != p3)   //assume if p1 != p1 + p2 != p3 -= operator is not working
	cout << "True, something is up here!" << endl;
   else if(p1 == p3)
	cout << "True, += operator appears to be working!" << endl;
  cout << "p5 != p3 does the != operator work?" << endl;
  if(p5 != p3)
	cout << "True, != operator is working." << endl;
  else
	cout << "My program sucks! That's all folks!" << endl;
  cout << "Testing copy constructor by creating Polynomial p6(p5) and checking equality with == before any changes are made and " <<
	  "after a change is made to only p5" << endl;
  Polynomial p6(p5); //test deep copy constructor
  if(p6 == p5)
	cout << "  == passes, now changing p5  " << endl;
  p5.changeCoefficient(100, 50);  //change original
  if( p6 == p5) //check if change effects deep copy
	cout << "Not a deep copy."  << endl;
  else
	cout << "Copy constructor fine!" << endl;	
  cout << "That's all folks!" << endl;
  return 0;
}
