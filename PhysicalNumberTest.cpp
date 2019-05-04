/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
   

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT

      .setname("Basic input")
      .CHECK_OK(istringstream("700[hour]") >> a)
      .CHECK_OK(istringstream("102.43[ton]") >> b)
      .CHECK_OK(istringstream("0.05[g]") >> c)
      .CHECK_OK(istringstream("45.7654[sec]") >> d)

      .setname("Compatible comparison tests")
      .CHECK_EQUAL((a>d), true)
      .CHECK_EQUAL(a>=d, true)
      .CHECK_EQUAL(d<a, true)
      .CHECK_EQUAL(d<=a, true)
      .CHECK_EQUAL(b>c, true)
      .CHECK_EQUAL(c<=b, true)
      .CHECK_EQUAL(c<b, true)
      
      .setname("Basic output")
      .CHECK_OUTPUT(a, "700[hour]")
      .CHECK_OUTPUT(b, "102.43[ton]")
      .CHECK_OUTPUT(c, "0.05[g]")
      .CHECK_OUTPUT(d, "45.7654[sec]")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
