#include "PhysicalNumber.h"
#include<string>
#include <exception>

double ariel::PhysicalNumber::convertRightToLeft(const PhysicalNumber& p2)const{

double temp;

if(u==p2.u)
    temp=p2.value;

else if((u==Unit::TON && p2.u==Unit::KG)||(u==Unit::KG&&p2.u==Unit::G)||(u==Unit::KM&&p2.u==Unit::M))
    temp=p2.value/1000;

else if((u==Unit::KG&&p2.u==Unit::TON)||(u==Unit::G&&p2.u==Unit::KG)||(u==Unit::M&&p2.u==Unit::KM))
    temp=p2.value*1000;

else if((u==Unit::MIN&&p2.u==Unit::HOUR)||(u==Unit::SEC&&p2.u==Unit::MIN))
    temp=p2.value*60;

else if((u==Unit::HOUR&&p2.u==Unit::MIN)||(u== Unit::MIN&&p2.u==Unit::SEC))
    temp=p2.value/60;

else if(u==Unit::HOUR&&p2.u==Unit::SEC)
    temp=p2.value/3600;

else if(u==Unit::SEC&&p2.u==Unit::HOUR)
    temp=p2.value*3600;

else if(u==Unit::TON&&p2.u==Unit::G)
    temp=p2.value/1000000;

else if(u==Unit::G&&p2.u==Unit::TON)
    temp=p2.value*1000000;

else if(u==Unit::KM&&p2.u==Unit::CM)
    temp=p2.value/100000;

else if(u==Unit::CM&&p2.u==Unit::KM)
    temp=p2.value*100000;

else if(u==Unit::M&&p2.u==Unit::CM)
    temp=p2.value/100;

else if(u==Unit::CM&&p2.u==Unit::M)
    temp=p2.value*100;

else throw("Units do not match - ["+p2.convertUnitToString()+"] cannot be converted to ["+this->convertUnitToString()+"]");

return temp;
}


const ariel::PhysicalNumber ariel::PhysicalNumber::operator+()const{ //implementaion of unary + operator 
    return PhysicalNumber(value, u);
} 

const ariel::PhysicalNumber ariel::PhysicalNumber::operator-()const{//implementation of unary - operator
    return PhysicalNumber(-value, u);
}

ariel::PhysicalNumber& ariel::PhysicalNumber::operator+=(const PhysicalNumber& other){

    double conversion=this->convertRightToLeft(other);
    (*this).value+=conversion;
    return *this;  
}

ariel::PhysicalNumber& ariel::PhysicalNumber::operator-=(const PhysicalNumber& other){

    double conversion=this->convertRightToLeft(other);
    (*this).value-=conversion;
    return *this; 
}

const ariel::PhysicalNumber ariel::PhysicalNumber::operator+(const PhysicalNumber& other)const{

double conversion=(*this).convertRightToLeft(other);
return PhysicalNumber(value+conversion, u);
}

const ariel::PhysicalNumber ariel::PhysicalNumber::operator-(const PhysicalNumber& other)const{

double conversion=(*this).convertRightToLeft(other);
return PhysicalNumber(value-conversion, u);
}

bool ariel::PhysicalNumber::operator> (const PhysicalNumber& other)const{
double conversion=(*this).convertRightToLeft(other);

if(this->value>conversion)
    return true;
else return false;
}

bool ariel::PhysicalNumber::operator< (const PhysicalNumber& other)const{

double conversion=this->convertRightToLeft(other);

if((*this).value<conversion)
    return true;
else return false;
}

bool ariel::PhysicalNumber::operator>= (const PhysicalNumber& other)const{

double conversion=this->convertRightToLeft(other);

if(this->value>=conversion)
    return true;
else return false;
}

bool ariel::PhysicalNumber::operator<= (const PhysicalNumber& other)const{

double conversion=this->convertRightToLeft(other);

if(this->value<=conversion)
    return true;
else return false;
}

bool ariel::PhysicalNumber::operator!= (const PhysicalNumber& other)const{

    double conversion=this->convertRightToLeft(other);

    if(this->value!=conversion)
        return true;
    else return false;
}

bool ariel::PhysicalNumber::operator== (const PhysicalNumber& other)const{

    double conversion=this->convertRightToLeft(other);

    if(this->value==conversion)
        return true;
    else return false;

}

ariel::PhysicalNumber& ariel::PhysicalNumber::operator++(){// why not const PhysicalNumber&

this->value++;
return *this;
}

const ariel::PhysicalNumber ariel::PhysicalNumber::operator++(int dummy_flag_postfix_increment){

PhysicalNumber copy=*this;
this->value++;
return copy;
}

ariel::PhysicalNumber& ariel::PhysicalNumber::operator--(){// why not const PhysicalNumber&

this->value--;
return *this;
}

const ariel::PhysicalNumber ariel::PhysicalNumber::operator--(int dummy_flag_postfix_increment){

PhysicalNumber copy=*this;
this->value--;
return copy;
}

std::string ariel::PhysicalNumber::convertUnitToString()const{

    std::string temp;

    switch(u){

case ariel::Unit::KM:
    temp="km"; break;
case ariel::Unit::M:
    temp="m"; break;
case ariel::Unit::CM:
    temp="cm"; break;
case ariel::Unit::TON:
    temp="ton"; break;
case ariel::Unit::KG:
    temp="kg"; break;
case ariel::Unit::G:
    temp="g"; break;
case ariel::Unit::HOUR:
    temp="hour"; break;
case ariel::Unit::MIN:
    temp="min"; break;
case ariel::Unit::SEC:
    temp="sec"; break;
default:
    temp="error";
    }
return temp;
}

void ariel::PhysicalNumber::convertStringToUnit(const std::string& str){

 if( (str.compare("kg") )==0)
    u=ariel::Unit::KG;

else if(str.compare("km")==0){
   
    u=ariel::Unit::KM; 
}
else if(str.compare("m")==0)
   u=ariel::Unit::M; 

else if(str.compare("cm")==0)
   u=ariel::Unit::CM;

else if(str.compare("ton")==0)
   u=ariel::Unit::TON;
else if(str.compare("g")==0)
    u=ariel::Unit::G;

else if(str.compare("hour")==0)
   u=ariel::Unit::HOUR;

else if(str.compare("min")==0)
    u=ariel::Unit::MIN;

else if(str.compare("sec")==0)
    u=ariel::Unit::SEC;  
}

std::ostream& ariel::operator<<(std::ostream& o,const ariel::PhysicalNumber& p){
    return (o<<p.value<<'['<<p.convertUnitToString()<<']');
}

//std::istream&
bool checkStringIsAValidUnit(std::istream& input, std::string& str){

input >> str;

std::string temp=str.substr(1, str.length()-2);

if (!input)
    return false; //input;
 
 if ( ( (str.at(0) ) !='[') || (str.at (str.length()-1) !=']') ||
 (temp.compare("kg")!=0 && temp.compare("ton")!=0  && temp.compare("g")!=0  &&  temp.compare("hour")!=0
 && temp.compare("min")!=0 &&  temp.compare("sec")!=0 &&  temp.compare("km")!=0 &&  temp.compare("m")!=0 
 && temp.compare("cm")!=0 )){

     input.setstate(std::ios::failbit); // failbit is for format error
     return false;
 }

 else{ 
    str=temp;
    return true ;//input;
}
}

  // Checks format, with rewind on failure.
std::istream& ariel::operator>>(std::istream& input, ariel::PhysicalNumber& p){

    double new_value;
    std::string unit_str;

// remember place for rewinding
std::ios::pos_type startPosition = input.tellg();

 if ( (!(input >> new_value))      ||
(!checkStringIsAValidUnit(input, unit_str))) 
 // rewind on error
 {
auto errorState = input.rdstate(); // remembererror state
        input.clear(); // clear error so seekg will work
        input.seekg(startPosition); // rewind
        input.clear(errorState); // set back the error flag
} 
     else {
        p.value = new_value; 
        p.convertStringToUnit(unit_str);//convertStringToUnit(unit_str);
    }

    return input;
}








  
       
  