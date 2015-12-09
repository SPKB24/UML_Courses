/* 
 * File:   jmhUtilities.h
 * Author: Jesse Heines, heines@cs.uml.edu
 *
 * Created on November 23, 2015, 10:46 AM
 */

#ifndef JMHUTILITIES_H
#define JMHUTILITIES_H

#include <string>

using namespace std ;

class jmhUtilities {
public:
  /**
   * NetBeans-supplied default constructor.
   */
  jmhUtilities();

  /**
   * NetBeans-supplied copy constructor.
   */
  jmhUtilities(const jmhUtilities& orig);

  /**
   * NetBeans-supplied destructor.
   */
  virtual ~jmhUtilities();
  
  /**
   * Trim leading and trailing white space (spaces, tabs, and newlines) from the
   *    string passed as an argument and return the trimmed string.
   * This version is more sophisticated than the one above.  It uses iterators
   *    and an improved search technique.
   * @param str string to trim (a copy, so that the original is not destroyed)
   * @return a copy of the original string with leading and trailing white space removed
   */
  static string trim( string str ) ;
  
  /**
   * Compare two characters in a case-insensitive manner by converting them both to
   *    uppercase and then testing if they are equal.
   * @param a the first character to compare
   * @param b the second character to compare
   * @return true if the two uppercase characters are equal, false otherwise
   * @see https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s14.html
   */
  static inline bool caseInsCharCompareN(char a, char b) ;
  /**
   * Compare two strings in a case-insensitive manner using the companion case-insensitive
   *    character comparison helper function.
   * @param s1 the first string to compare
   * @param s2 the second string to compare
   * @return true if the two uppercase strings are equal, false otherwise
   * @see https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s14.html
   */
  static bool caseInsCompare(const string& s1, const string& s2) ;

  private:

};

#endif /* JMHUTILITIES_H */
