#include<iostream>
#include "Unit.h"

namespace ariel{ 

class PhysicalNumber{

private:

double value;
Unit u;

double convertRightToLeft(const PhysicalNumber& p2)const; //main converting method between units
std::string convertUnitToString()const; // convert between Unit enum class ans string
void convertStringToUnit(const std::string& str); // convert between string and  Unit enum class
friend bool checkStringIsAValidUnit(std::istream& input,std::string& str); // validate unit input

public:

PhysicalNumber(double aValue=0.0, Unit aUnit=Unit::NAU): value{aValue}, u{aUnit} {}; // default constructor & initializtion list

const PhysicalNumber operator+(const PhysicalNumber& other) const;//binary + operator  
PhysicalNumber& operator+=(const PhysicalNumber& other); //binary += operator 
const PhysicalNumber operator+()const; // unary + operator

const PhysicalNumber operator-(const PhysicalNumber& other) const; // binary - operator
PhysicalNumber& operator-=(const PhysicalNumber& other); // binary -= operator
const PhysicalNumber operator-()const; // unary - opeartor

bool operator> (const PhysicalNumber& other)const;
bool operator>= (const PhysicalNumber& other)const;
bool operator< (const PhysicalNumber& other)const;
bool operator<= (const PhysicalNumber& other)const;
bool operator== (const PhysicalNumber& other)const;
bool operator!= (const PhysicalNumber& other)const;

const PhysicalNumber operator++(int dummy_flag_for_postfix_increment);//postfix ++operator
PhysicalNumber& operator++(); //prefix ++operator
const PhysicalNumber operator--(int dummy_flag_for_postfix_decrement);//postfix --operator
PhysicalNumber& operator--(); //prefix --operator

friend std::ostream& operator<<(std::ostream& o, const PhysicalNumber& p);
friend std::istream& operator>>(std::istream& is, PhysicalNumber& physicalNum);

};//end PhysicalNumber class
} //end namespace ariel