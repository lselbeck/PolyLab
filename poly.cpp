//-----------------------------------------------------------------------//
// POLY.CPP                                                              //
// Author: Luke Selbeck                                                  //
// Date: April 9th, 2014                                                 //
// Class: CSS 343                                                        //
//                                                                       //
// Member function definitions for class Poly                            //
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

#include "poly.h"

//-------------------------- Constructor ----------------------------------
// Default constructor for class Poly
// Preconditions:   none
// Postconditions:  
//       -- an array of size 1 is created  
//       -- one term is in the array
//             -- coefficient=0, and exponent=0
//             -- i.e. 0*x^0
Poly::Poly() {
   highestExp = 0;
   coeffPtr = new int[highestExp + 1];
   for (int i = highestExp; i >= 0; i--)
      coeffPtr[i] = 0;
}

//-------------------------- Constructor ----------------------------------
// Constructor accepting newCoeff as the coefficient of the 0th term
// Preconditions:  none
// Postconditions: 
//       -- an array of size 1 is created  
//       -- one term is inserted into the array
//             -- coefficient=newCoeff, and exponent=0
//             -- i.e. newCoeff*x^0
Poly::Poly(int newCoeff) {
   highestExp = 0;
   coeffPtr = new int[highestExp + 1];
   for (int i = highestExp; i >= 0; i--)
      coeffPtr[i] = 0;
      
   coeffPtr[0] = newCoeff;   //array position == exponent value
} 

//-------------------------- Constructor ----------------------------------
// Constructor accepting two ints as coefficient and exponent, respectively
//    of the term to be inserted 
// Preconditions:  expIsValid() checks for exponent validity
// Postconditions:
//       -- an array of size 1 is created  
//       -- non-positive exponent value throws error message
//       -- one term is inserted into the array
//             -- coefficient = newCoeff, and exponent = newExp
//             -- i.e. newCoeff*x^newExp
Poly::Poly(int newCoeff, int newExp) {
   if (expIsValid(newExp)) {
      highestExp = newExp;
      coeffPtr = new int[highestExp + 1];
      for (int i = highestExp; i >= 0; i--)
         coeffPtr[i] = 0;
         
      coeffPtr[newExp] = newCoeff;   //array position == exponent value
   }
} 

//------------------------- Copy Constructor ------------------------------
// Constructor accepting a Poly to be deep copied 
// Preconditions:  none
// Postconditions:
//       -- a Poly an exact copy of the parameter is made
Poly::Poly(const Poly& toBeCopied) {
   //*this = toBeCopied;
   
   
   highestExp = toBeCopied.highestExp;
   coeffPtr = new int[highestExp + 1];
   for (int i = highestExp; i >= 0; i--)
      coeffPtr[i] = toBeCopied.coeffPtr[i];
   
}

//--------------------------- Destructor ----------------------------------
// Destructor for class Poly
// Preconditions:   coeffPtr points to memory on the heap
// Postconditions:
//       -- array for coeffPtr is deallocated
//       -- highestExp = 0
Poly::~Poly() {
   delete[] coeffPtr;
   coeffPtr = NULL;
   highestExp = 0;
}

//---------------------------- getCoeff -----------------------------------
// Get the coefficient of an int exponent
// Preconditions:
//       -- coeffPtr points to an array
//       -- expIsValid() checks for exponent validity
//       -- exponent is a valid value, otherwise nothing is done
// Postconditions:  Returns the coefficient value for the exponent
int Poly::getCoeff(int exponent) const {
   if (!expIsValid(exponent) || exponent > highestExp) //out of array bounds
      return 0;
   else
      return coeffPtr[exponent];
}

//---------------------------- setCoeff -----------------------------------
// Overwrite a term in Poly
// Preconditions:
//       -- coeffPtr points to an array
//       -- expIsValid() checks for exponent validity
//       -- newExp is a valid exponent value, otherwise nothing is done
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, that term is
//          replaced with the new coefficient and exponent pair
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly, consisting of the new coefficient and new exponent
void Poly::setCoeff(int newCoeff, int newExp) {
   if (expIsValid(newExp)) {
      if (newExp > highestExp) {         
         resizeArray(newExp + 1);
         highestExp = newExp;
      }
      coeffPtr[newExp] = newCoeff;
   }
}

//---------------------------- addCoeff -----------------------------------
// Add a term to Poly
// Preconditions:
//       -- coeffPtr points to an array
//       -- expIsValid() checks for exponent validity
//       -- newExp is a valid exponent value, otherwise nothing is done
//       -- setCoeff() overwrites a term into Poly
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, that term is
//          added with the new coefficient and exponent pair
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly using setCoeff()
void Poly::addCoeff(int newCoeff, int newExp) {
   if (expIsValid(newExp)) {
      if (newExp > highestExp) setCoeff(newCoeff, newExp);
      else coeffPtr[newExp] += newCoeff;
   }
}

//---------------------------- subCoeff -----------------------------------
// Subtract a term from Poly
// Preconditions:
//       -- coeffPtr points to an array
//       -- addCoeff adds a term to Poly
//       -- newExp is a valid exponent value, otherwise nothing is done
// Postconditions:  
//       -- params are coefficient and exponent respectively
//       -- if the exponent already exists within the Poly, the new
//          coefficient and exponent pair is subtracted from the existing
//          term          
//       -- if the exponent is not already in the Poly, a new term is added
//          to the Poly, consisting of the new coefficient's inverse
//          and new exponent
void Poly::subCoeff(int newCoeff, int newExp) {
   addCoeff((-1 * newCoeff), newExp);
}

//--------------------------- expIsValid ----------------------------------
// Determines if the int passed is a valid exponent value in Poly
// Preconditions:  none
// Postconditions:
//       -- returns true if exponent >= 0
//       -- returns false if otherwise, and throws a cerr message
bool Poly::expIsValid(int exponent) const {
   return exponent >= 0;
}

//--------------------------- resizeArray ---------------------------------
// Copies coeffPtr's array into a new array of newSize
// **WARNING** this resize should only be used if you are going to insert a 
//             term into the last element, and then assign highestExp to
//             that last element after this method is finished.  Otherwise,
//             it screws everything up because highestExp isn't set to the
//             right place.
// **NOTE** -- newSize should be greater than highestExp+1, otherwise, loss
//             of data
// Preconditions:
//       -- coeffPtr points to an array
// Postconditions:
//       -- coeffPtr points to a new array of size newSize, with all the
//          old array elements copied over
//       -- the old array is deallocated
void Poly::resizeArray(int newSize) {
   int* tmp = new int[newSize];
   
   for (int i = 0; i < newSize; i++)
      tmp[i] = 0;
   
   for (int i = 0; i <= highestExp; i++) 
      tmp[i] = coeffPtr[i];
      
   delete[] coeffPtr;
   coeffPtr = tmp;
   tmp = NULL;
}

//------------------------------  +  --------------------------------------
// Overloaded addition operator; add 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the sum of this object and
//       rhs
const Poly Poly::operator+(const Poly& rhs) const {
   Poly sum;
   sum = *this;
   for (int i = rhs.highestExp; i >= 0; i--)
      sum.addCoeff(rhs.coeffPtr[i], i);
   return sum;
}


//------------------------------  +  --------------------------------------
// Overloaded addition operator; add a Poly and an int
// Preconditions:   coeffPtr points to array with size at least 1
// Postconditions:  a Poly is returned, which is the sum of this object and
//       int
const Poly Poly::operator+(int rhs) const {
   Poly sum;
   sum = *this;
   sum.addCoeff(rhs, 0);
   return sum;
}

//------------------------------  -  --------------------------------------
// Overloaded subtraction operator; subtract 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the negation of this
//       object and rhs  i.e. this - rhs
const Poly Poly::operator-(const Poly& rhs) const {
   Poly negation;
   negation = *this;
   for (int i = rhs.highestExp; i >= 0; i--)
         negation.subCoeff(rhs.coeffPtr[i], i);
   return negation;
}


//------------------------------  -  --------------------------------------
// Overloaded subtraction operator; subtract an int from a Poly
// Preconditions:   coeffPtr points to array with size at least 1
// Postconditions:  a Poly is returned, which is the negation of this
//       object and the int
const Poly Poly::operator-(int rhs) const {
   Poly negation;
   negation = *this;
   negation.subCoeff(rhs, 0);
   return negation;
}

//------------------------------  *  --------------------------------------
// Overloaded multiplication operator; multiply 2 Polys
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  a Poly is returned, which is the product of this object
//       and rhs  
const Poly Poly::operator*(const Poly& rhs) const {
   Poly product;
   for (int i = highestExp; i >= 0; i--)
      for (int j = rhs.highestExp; j >= 0; j--)
         product.addCoeff((coeffPtr[i] * rhs.coeffPtr[j]), (i + j));
   return product;
}


//------------------------------  *  --------------------------------------
// Overloaded multiplication operator; multiply a Poly and an int
// Preconditions:   coeffPtr points to array with size at least 1
// Postconditions:  a Poly is returned, which is the product of this object
//       and the int
const Poly Poly::operator*(int rhs) const {
   Poly product;
   for (int i = highestExp; i >= 0; i--)
      product.setCoeff((coeffPtr[i] * rhs), i);
   return product;
}

//------------------------------  =  --------------------------------------
// Overloaded assignment operator; current object = parameter
// Preconditions:
//       -- rhs.coeffPtr points to an array of at least size 1
//       -- setCoeff overwrites a term into Poly
// Postconditions:
//       -- this object's array is deleted, and a new one with size equal
//          to rhs's array is created
//       -- all the terms from rhs's array are deep copied to this object's
//          array
Poly& Poly::operator=(const Poly& rhs) {  
   if (*this == rhs)
      return *this;
      
   delete[] coeffPtr;
   coeffPtr = new int[rhs.highestExp + 1];
   highestExp = rhs.highestExp;
   
   for (int i = highestExp; i >= 0; i--)
      setCoeff(rhs.coeffPtr[i], i);
   
   return *this;
}

//-----------------------------  +=  --------------------------------------
// current object += parameter
// Preconditions:
//       -- rhs.coeffPtr points to an array of at least size 1
//       -- addCoeff() adds a term to Poly
// Postconditions:
//       -- all the terms from rhs's array are passed into this object's
//          array using addCoeff()
Poly& Poly::operator+=(const Poly& rhs) {
   for (int i = rhs.highestExp; i >= 0; i--)
      addCoeff(rhs.coeffPtr[i], i);
   return *this;
}

//-----------------------------  -=  --------------------------------------
// current object -= parameter
// Preconditions:
//       -- rhs.coeffPtr points to an array of at least size 1
//       -- subCoeff() subtracts a term from Poly
// Postconditions:
//       -- all the terms from rhs's array are passed into this object's
//          array using subCoeff()
Poly& Poly::operator-=(const Poly& rhs) {
   for (int i = rhs.highestExp; i >= 0; i--)
      subCoeff(rhs.coeffPtr[i], i);
   return *this;
}

//-----------------------------  *=  --------------------------------------
// current object *= parameter
// Preconditions:   rhs.coeffPtr points to an array of at least size 1
// Postconditions:  *this is assigned to be the product of this and rhs
Poly& Poly::operator*=(const Poly& rhs) {
   // I couldn't find a more efficient way than this, which is the same as
   // return *this = *this * rhs
   Poly product;
   for (int i = highestExp; i >= 0; i--)
      for (int j = rhs.highestExp; j >= 0; j--)
         product.addCoeff((coeffPtr[i] * rhs.coeffPtr[j]), (i + j));
   *this = product;
   return *this;
}

//-----------------------------  ==  --------------------------------------
// Determine if two Polys are equal
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  
//       -- true is returned if all terms in this object and rhs are equal
//       -- false is returned if otherwise
bool Poly::operator==(const Poly& rhs) const {
   if (highestExp != rhs.highestExp) 
      return false;
   for (int i = highestExp; i >= 0; i--)
      if (coeffPtr[i] != rhs.coeffPtr[i]) 
         return false;
   return true;
}

//-----------------------------  !=  --------------------------------------
// Determine if two Polys are not equal
// Preconditions:   coeffPtr and rhs.coeffPtr point to arrays with size at
//       least 1
// Postconditions:  
//       -- false is returned if all terms in this object and rhs are equal
//       -- true is returned if otherwise
bool Poly::operator!=(const Poly& rhs) const {
   return !(*this == rhs);
}

//-----------------------------  <<  --------------------------------------
// Overloaded output operator for class Poly
// Preconditions:   coeffPtr must point to an array
// Postconditions:  prints polynomial in this fashion, with no trailing endl
//          +3x^5 +7x^3 -2x^2 +9x +1
//          note: includes positive/negative sign for first coefficient
ostream& operator<<(ostream& out, const Poly& a) {
   for (int i = a.highestExp; i >= 0; i--) {
      //print coefficient
      if (a.coeffPtr[i] > 0) {
         out << " +" << a.coeffPtr[i];
      } else if (a.coeffPtr[i] < 0) {
         out << " " << a.coeffPtr[i];
      }
      
      //print exponent
      if (a.coeffPtr[i] != 0) {
         if (i > 1)
            out << "x^" << i;
         else if (i == 1)
            out << "x";
      }
   }
   return out;
}

//-----------------------------  >>  --------------------------------------
// Overloaded input operator for class Poly; overwrites terms into Poly
// *WARNING**  must be inputted in the specified format:
//       [newCoeff] [newExp]   [newCoeff] [newExp] ...etc... -1 -1
//       -- input "-1 -1" to end the input stream
// Preconditions:
//       -- coeffPtr must point to an array
// Postconditions:  takes two ints as coefficient and exponent, does no
//    error checking, inserts/overwrites term into Poly
istream& operator>>(istream& in, Poly& rhs) {
   int newCoeff = -1;
   int newExp = -1;
   bool done = false;
   
   while (!done) {      
      in >> newCoeff;
      in >> newExp;
      if (newCoeff == -1 && newExp == -1)
         done = true;
      else
         rhs.setCoeff(newCoeff, newExp);
   }
   return in;
}

