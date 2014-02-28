//@file Polynomial.h
//@author Bret A. Van Hof
//Polynomial Class
#ifndef POLYNOMIAL_H                                  
#define POLYNOMIAL_H
#include <iostream>
#include <string>
 
using namespace std;

//---------------------------------------------------------------------------
// Polynomial class:
//   --operator<<: friend class used to print polynomial in correct form
//	 --default constructor
//	 --copy constructor
//	 --deconstructor
//   --degree: return degree of leading term
//   --coefficient: return coefficient of term of given degree
//   --changeCoefficient: Change or create a term
//   --operator+: add two polynomials
//   --operator-: subtract a polynomial from another
//   --operator==: determine equivalency of two polynomials
//   --operator!=: determine if two polynomials are non-equivalent
//   --operator=: set this polynomial equal to another polynomial
//   --operator+=: add polynomial to this polynomial
//   --operator-=: subtract polynomial from this polynomial
//   --insert: private function, insert a term before given term
//   --remove: private function, remove given term
// Assumptions:
//   -- a Polynomial can not have a term with degree < 0
//   -- a Term can not have coefficient == 0
//   -- Heap memory should be deallocated by deconstructor
//---------------------------------------------------------------------------

class Polynomial { 
  // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
  friend ostream& operator<<( ostream &output, const Polynomial& p );


public:
  // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
  //@pre none
  //@post a 0-degree polynomial with 0.0 coefficient and size = 0 created
  Polynomial( );
  //Constructor: copy constructor creates a deep copy of polynomial passed as parameter
  //@pre none
  //@post: a deep copy of p created
  Polynomial( const Polynomial& p );
  //Deconstructor: deallocates all heap memory in use.
  //@pre none
  //@post all heap memory deallocated
  ~Polynomial( );

  // Member functions
  //degree
  // returns the degree of a polynomial
  //@pre none
  //@post degree of leading term returned, if size = 0, -1 returned
  //@return int representing degree of leading term
  int degree( ) const;

  //coefficient
  // returns the coefficient of the x^power term.
  //@pre none
  //@post degree of term of power returned
  //@return degree of term of power returned, it is 0 if no term of power contained in this polynomial
  double coefficient( const int power ) const; 
 
  //changeCoefficient
  // replaces the coefficient of the x^power term
  //@pre none
  //@post Polynomial term of power coefficient = newCoefficient
  //@param const double newCoefficient, the coefficient for polynomial term of power
  //@param const int power, power of polynomial term whose coefficient is changed
  //@return bool, true if change successfull, false if not
  bool changeCoefficient( const double newCoefficient, const int power );

  // Arithmetic operators
  //operator+
  //@pre none
  //@post Polynomial created
  //@param const Polynomial&p, polynomial to add to this polynomial
  //@return Polynomial, the sum of this polynomial and p
  Polynomial operator+( const Polynomial& p ) const;

  //operator-
  //@pre none
  //@post Polynomial created
  //@param const Polynomial&p, polynomial to subtract from this polynomial
  //@return Polynomial, the difference of this polynomial and p
  Polynomial operator-( const Polynomial& p ) const;
 
  // Boolean comparison operators
  //operator==
  //@pre none
  //@post none
  //@param const Polynomial&p, polynomial to be checked for equality with this polynomial
  //@return bool, true if this polynomial is equivalent to p, otherwise false
  bool operator==( const Polynomial& p ) const;

  //operator!=
  //@pre none
  //@post none
  //@param const Polynomial&p, polynomial to be checked for equality with this polynomial
  //@return bool, false if this polynomial is equivalent to p, otherwise true
  bool operator!=( const Polynomial& p ) const;

  // Assignment operators

  //operator=
  //@pre none
  //@post this Polynomial is a deep copy of p
  //@param const Polynomial&p, polynomial to be copied
  //@return Polynomial&, a deep copy of p
  Polynomial& operator=( const Polynomial& p );

  //operator+=
  //@pre none
  //@post this polynomial = sum of this polynomial and p 
  //@param const Polynomial&p, polynomial to be added to this polynomial
  //@return Polynomial&, this
  Polynomial& operator+=( const Polynomial& p );

  //operator-=
  //@pre none
  //@post this polynomial = differnce of this polynomial and p 
  //@param const Polynomial&p, polynomial to be subtracted from this polynomial
  //@return Polynomial&, this
  Polynomial& operator-=( const Polynomial& p );
 
 private:

  struct Term {     // a term on the sparse polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    Term *prev;     // a pointer to the previous higher term
    Term *next;     // a pointer to the next lower term
  };
 
  int size;         // # terms in the sparce polynomial
 
  Term *head;       // a pointer to the doubly-linked circular list of
                    // sparce polynomial

  //insert
  //inserts a new term into this polynomial
  //@pre Term* prev is a term in this polynomial && newCoefficient != 0 && power > 0
  //@post this polynomial has new term
  //@param Term* prev, the term that follows the term to be inserted
  //@param const double newCoefficient, coefficient of term to be inserted
  //@param const int power,  power of term to be inserted
  //@return bool, true if insertion successful, otherwise false
  bool insert( Term* prev, const double newCoefficient, const int power );

  //remove
  //removes a term from this polynomial
  //@pre Term* pos is a term in this polynomial
  //@post Term* pos is not a term in this polynomial
  //@param Term* pos, term to removed from this polynomial
  //@return bool, truee if removal successful, otherwise false
  bool remove( Term* pos );
};
 
 
 
#endif
