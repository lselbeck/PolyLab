#include "poly.cpp"
#include <iostream>
using namespace std;

int main() {
   Poly A(5, 7);
   Poly B(3, 2);
   Poly C(A);
   A.addCoeff(-5, 2);
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   C *= A;
   cout << "C *= A " << C << endl;
   cout << "B-A = " << B-A << endl;
   B -= A;
   cout << "B -= A: " << B << endl;
   B += A;
   cout << "B += A: " << B << endl;
   cout << "B = " << B << endl;
   cout << "A = " << A << endl;
   cout << "A-B = " << A-B << endl;
   
   cout << "A*B = " << A*B << endl;
   A = A+0;
   cout << "A+2-1 = " << A+2-1 << endl;
   
   cout << "overwrite terms to A: ";
   cin >> A;
   cout << "A = " << A << endl;
   
}