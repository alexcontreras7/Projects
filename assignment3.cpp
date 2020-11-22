/* Alex Contreras, 2001486950, 1002, Assignment 3
   Program will calculate the parameters of a pyramid
   height, base
   surface area, volume, base area, lateral area, slant length
*/

/* Plan 
 - declare all varibles we will use 
  (base, height, surfaceArea, baseArea, lateralArea, volume, slantLenth)
 - use setprecision to make all future outputs have two decimal places
 - Print header
 - Prompt the user for a height and a base and store those values with cin
 - Calculate surface area and output the anwser
   (Surface Area= base^2 + 2base* ( base^2/4 + height^2) ^(1/2))
 - Calculate volume and outut the answer
   (Volume= base^2 *height/3)
 - Calculate base area and output the answer
   (base area= base^2)
 - Calculate lateral area and output the answer
   (lateral area- surface area - base area)
 - Calculate slant lentg and output the answer
   (slant length= (height^2 + base^2 / 4) ^ (1/2)
   //NOTE: all formulas in plan are written in english not in c++
 */

#include <iostream> // cin, cout
#include <cmath> // sqrt(), power( , )
#include <iomanip> // setprecision ()
using namespace std;
int main ()
{
	
	double base = 0;
	double height = 0;
	double surfaceArea = 0;
	double baseArea = 0;
	double lateralArea = 0;
	double volume = 0;
	double slantLength = 0;
	// varibles that will be used in the program
	
	cout << fixed << setprecision (2);
	// fixes all outputs to have two decinal places
	//
	cout << "--------------------------------------------" << endl;
	cout << "Program to calculate parameters of a pyramid" << endl; // prints header
	cout << "--------------------------------------------" << endl;
	cout << "Enter the height in inches: ";
	

	cin >> height; // lets the user input a height
	if (height <= 0) {
		cout << "ERROR INVAlID INPUT, height again: " ;
		cin >> height;
	} // makes the user input another height if the first one is less than or equal to 0

	
	cout << "Enter the width of the base in inches: ";
	cin >> base; // lets the user input a base
	if (base <= 0 ) {
		cout << "ERROR INVALID BASE, enter again: " ;
		cin >> base; 
	} // makes the user inpout another base if the first one is less than or equal to 0

	surfaceArea = pow( base, 2) + 2 * base * sqrt( pow (base,2) / 4 + pow (height, 2));
	// formula to find surface area
	cout << "Surface Area: " << surfaceArea << endl; // ouputs surface area
	volume = pow ( base, 2) * height / 3;
	// formula to find volume
	cout << "Volume: " << volume << endl; // outputs volume
	baseArea = pow ( base, 2);
	// formula to find base area
	cout << "Base area: " << baseArea << endl; // ouputs base area
	lateralArea = surfaceArea-baseArea;
	// formula to find lateral area
	cout << "Lateral Area: " << lateralArea << endl; // ouputs lateral area
	slantLength = sqrt( pow(height, 2) + pow( base,2) / 4 );
	// formula to find slant length
	cout << "Slant Length: " << slantLength << endl; // ouputs slant length
	cout << "                                            " << endl;
	return 0;
}
