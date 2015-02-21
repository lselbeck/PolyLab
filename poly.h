//-----------------------------------------------------------------------//
// POLY.H                                                                //
// Author: Luke Selbeck                                                  //
// Date: April 9th, 2014                                                 //
// Class: CSS 343                                                        //
//                                                                       //
// Poly holds a polynomial with non-negative exponents                   //
//-----------------------------------------------------------------------//
// Polynomial:  defined as a sum of coefficient and exponent pairs,      //
//     called terms.                                                     //
//                                                                       //
//     Term example:       Coefficient  Exponent                         //
//                               \         /                             //
//                               +3  *  x^5                              //
//                                                                       //
//     Polynomial example: +3*x^5 +7*x^3 -2*x^2 +9*x +1                  //
//                                                                       //
// Implementation and assumptions:                                       //
//   -- terms are stored in an array                                     //
//         > array position denotates exponent value                     //
//         > array values denotate coefficient values                    //
//   -- does not accept non-int coefficient/exponent values              //
//   -- does not accept non-positive exponent values                     //
//-----------------------------------------------------------------------//

#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;


class Poly {
//-----------------------------  <<  --------------------------------------
// Overloaded output operator for class Poly
// Preconditions:   coeffPtr must point to an array
// Postconditions:  prints exponent in this fashion, with no trailing endl
//          +3*x^5 +7*x^3 -2*x^2 +9*x +1
//          note: includes positive/negative sign for first coefficient
friend ostream& operator<<(ostream&, const Poly&);

//-----------------------------  >>  --------------------------------------
// Overloaded input operator for class Poly; overwrites terms into Poly
// *WARNING**  must be inputted in the specified format:
//       [newCoeff] [newExp]   [newCoeff] [newExp] ...etc... -1 -1
//       -- input "-1 -1" to end the input stream
// Preconditions:
//       -- coeffPtr must point to an array
// Postconditions:  takes two ints as coefficient and exponent, does no
//    error checking, inserts/overwrites term into Poly
friend istream& operator>>(istream&, Poly&);

public:
//-------------------------- Constructor ----------------------------------
// Default constructor for class Poly
// Preconditions:   none
// Postconditions:  
//       -- an array of size 1 is created  
//       -- one term is inserted into the array
//             -- coefficient=0, and exponent=0
//             -- i.e. 0*x^0
Poly();

//-------------------------- Constructor ----------------------------------
// Constructor accepting one int as the coefficient of the 0th term
// Preconditions:  none
// Postconditions: 
//       -- an array of size 1 is created  
//       -- one term is inserted into the array
//             -- coefficient=[int], and exponent=0
//             -- i.e. [int]*x^0
Poly(int);  

//-------------------------- Constructor ----------------------------------
// Constructor accepting two ints as coefficient and exponent, respectively
//    of the term to be inserted 
// Preconditions:  none
// Postconditions:
//       -- an array of size 1 is created  
//       -- one term is inserted into the array
//             -- coefficient=[int], and exponent=[int]
//             -- i.e. [coefficient]*x^[exponent]
Poly(int, int);

//------------------------- Copy Constructor ------------------------------
// Constructor accepting a Poly to be deep copied 
// Preconditions:  none
// Postconditions:
//       -- a Poly an exact copy of the parameter is made
Poly(const Poly&);

//--------------------------- Destructor ----------------------------------
// Destructor for class Poly
// Preconditions:   coeffPtr points to memory on the heap
// Postconditions:
//       -- array for coeffPtr is deallocated
//       -- highestExp = 0
~Poly();

//---------------------------- getCoeff -----------------------------------
// Get the coefficient of an int exponent
// Preconditions:   coeffPtr points to an array
// Postconditions:  Returns the coefficient value for the exponent
int getCoeff(int) const;

//---------------------------- setCoeff -----------------------------------
// Overwrite a term in Poly
// Preconditions:   coeffPtr points to an array
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, that term is
//          replaced with the new coefficient and exponent pair
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly, consisting of the new coefficient and new exponent
void setCoeff(int, int);

//---------------------------- addCoeff -----------------------------------
// Add a term to Poly
// Preconditions:   coeffPtr points to an array
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, that term is
//          added with the new coefficient and exponent pair
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly, consisting of the new coefficient and new exponent
void addCoeff(int, int);

//---------------------------- subCoeff -----------------------------------
// Subtract a term from Poly
// Preconditions:   coeffPtr points to an array
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, the new
//          coefficient and exponent pair is subtracted from the existing
//          term          
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly, consisting of the new coefficient's inverse
//          and new exponent
void subCoeff(int, int);

//------------------------------  +  --------------------------------------
// Overloaded addition operator; add 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the sum of this object and
//       rhs
const Poly operator+(const Poly&) const;

//------------------------------  +  --------------------------------------
// Overloaded addition operator; add a Poly and an int
// Preconditions:   coeffPtr point to array with size at least 1
// Postconditions:  a Poly is returned, which is the sum of this object and
//       the int
const Poly operator+(int) const;

//------------------------------  -  --------------------------------------
// Overloaded subtraction operator; subtract 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the negation of this
//       object and rhs  
const Poly operator-(const Poly&) const;

//------------------------------  -  --------------------------------------
// Overloaded subtraction operator; subtract an int from a Poly
// Preconditions:   coeffPtr points to array with size at least 1
// Postconditions:  a Poly is returned, which is the negation of this
//       object and the int
const Poly operator-(int) const;

//------------------------------  *  --------------------------------------
// Overloaded multiplication operator; multiply 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the product of this object
//       and rhs  
const Poly operator*(const Poly&) const;

//------------------------------  *  --------------------------------------
// Overloaded multiplication operator; multiply a Poly and an int
// Preconditions:   coeffPtr points to array with size at least 1
// Postconditions:  a Poly is returned, which is the product of this object
//       and the int
const Poly operator*(int) const;

//------------------------------  =  --------------------------------------
// Overloaded assignment operator; current object = parameter
// Preconditions:   rhs.coeffPtr points to an array of at least size 1
// Postconditions:
//       -- this object's array is deleted, and a new one with size equal
//          to rhs's array is created
//       -- all the terms from rhs's array are deep copied to this object's
//          array
Poly& operator=(const Poly&);

//-----------------------------  +=  --------------------------------------
// current object += parameter
// Preconditions:   rhs.coeffPtr points to an array of at least size 1
// Postconditions:
//       -- all the terms from rhs's array are passed into this object's
//          array using addCoeff()
Poly& operator+=(const Poly&);

//-----------------------------  -=  --------------------------------------
// current object -= parameter
// Preconditions:   rhs.coeffPtr points to an array of at least size 1
// Postconditions:
//       -- all the terms from rhs's array are passed into this object's
//          array using subCoeff()
Poly& operator-=(const Poly&);

//-----------------------------  *=  --------------------------------------
// current object *= parameter
// Preconditions:   rhs.coeffPtr points to an array of at least size 1
// Postconditions:  *this is assigned to be the product of this and rhs
Poly& operator*=(const Poly&);

//-----------------------------  ==  --------------------------------------
// Determine if two Polys are equal
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  
//       -- true is returned if all terms in this object and rhs are equal
//       -- false is returned if otherwise
bool operator==(const Poly&) const;

//-----------------------------  !=  --------------------------------------
// Determine if two Polys are not equal
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  
//       -- false is returned if all terms in this object and rhs are equal
//       -- true is returned if otherwise
bool operator!=(const Poly&) const;

//--------------------------- expIsValid ----------------------------------
// Determines if the int passed is a valid exponent value in Poly
// Preconditions:  none
// Postconditions:
//       -- returns true if exponent >= 0
//       -- returns false if otherwise, and throws a cerr message
bool expIsValid(int) const;

private:
   
//--------------------------- resizeArray ---------------------------------
// Copies coeffPtr's array into a new array of newSize
// **NOTE** -- newSize should be greater than highestExp+1, otherwise, loss
//             of data
// Preconditions:
//       -- coeffPtr points to an array
// Postconditions:
//       -- coeffPtr points to a new array of size newSize, with all the
//          old array elements copied over
//       -- the old array is deallocated
void resizeArray(int);

//pointer to an array storing the coefficients of the Poly
int *coeffPtr;
   
//array size == highestExp + 1, because the array position is the 
//exponent value
int highestExp; 

};

#endif
