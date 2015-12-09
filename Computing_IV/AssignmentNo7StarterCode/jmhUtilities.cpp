/* 
 * File:   jmhUtilities.cpp
 * Author: Jesse Heines, heines@cs.uml.edu
 * 
 * Created on November 23, 2015, 10:46 AM
 */

#include "jmhUtilities.h"
#include <string>
using namespace std ;

/**
 * NetBeans-supplied default constructor.
 */
jmhUtilities::jmhUtilities() {
}

/**
 * NetBeans-supplied copy constructor.
 */
jmhUtilities::jmhUtilities(const jmhUtilities& orig) {
}

/**
 * NetBeans-supplied destructor.
 */
jmhUtilities::~jmhUtilities() {
}


/**
 * Trim leading and trailing white space (spaces, tabs, and newlines) from the
 *    string passed as an argument and return the trimmed string.
 * This version is more sophisticated than the one above.  It uses iterators
 *    and an improved search technique.
 * @param str string to trim (a copy, so that the original is not destroyed)
 * @return a copy of the original string with leading and trailing white space removed
 */
string jmhUtilities::trim( string str ) {
  // define the iterator to be used in both loops
  string::iterator it ;

  // search for leading white space characters
  it = str.begin() ;
  while ( *it == ' ' || *it == '\t' || *it == '\n' ) {
    str.erase( it ) ;   // erase the found whitespace character
    it = str.begin() ;  // reposition the iterator to the first character in the string
  }

  // search for trailing white space characters
  it = str.end() - 1 ;
  while ( *it == ' ' || *it == '\t' || *it == '\n' ) {
    str.erase( it ) ;     // erase the found whitespace character
    it = str.end() - 1 ;  // reposition the iterator to the last character in the string
  }

  // return the result
  return str ;
}


/**
 * Compare two characters in a case-insensitive manner by converting them both to
 *    uppercase and then testing if they are equal.
 * @param a the first character to compare
 * @param b the second character to compare
 * @return true if the two uppercase characters are equal, false otherwise
   * @see https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s14.html
 */
inline bool jmhUtilities::caseInsCharCompareN(char a, char b) {
  return ( toupper( a ) == toupper( b ) ) ;
}

/**
 * Compare two strings in a case-insensitive manner using the companion case-insensitive
 *    character comparison helper function.
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return true if the two uppercase strings are equal, false otherwise
   * @see https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s14.html
 */
bool jmhUtilities::caseInsCompare( const string& s1, const string& s2 ) {
   return ( ( s1.size() == s2.size() ) &&
             equal( s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN ) ) ;
}
