/* 
 * File:   Attributes.h
 * Author: Sohit
 *
 * Created on October 13, 2015, 9:51 PM
 */

#ifndef ATTRIBUTES_H
#define	ATTRIBUTES_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Attributes 
{
  /** Store Attribute Name */
  string m_attributeName;
  
  /** Store Attribute Content */
  string m_attributeContent;

 /**
  * This function removes all occurrences of the specified character from the inputted string 
  * @param ps the parser state
  * 
  * // This following code was obtained from:
  * // https://piazza.com/class/icm9zfoyt6m5v0?cid=50
  * // It was written by Cullin Lam .
  * // Changes made are as follows:
  * // 1. Change return type from STRING to VOID
  * // 2. Changed parameter 'char z', to 'string delimiter'
  */
  void strip( string& str, string delimiter);
  
public:
  /**
   * Default Constructor
   */
  Attributes();
  
  /**
   * Custom Constructor
   * @param attrName Attribute Name
   * @param attrContent Attribute Content
   */
  Attributes( string attrName, string attrContent );
  
  /**
   * Custom Constructor
   * @param _attributes vector of strings as input.
   */
  Attributes( vector<string> _attributes );
  
  /**
   * Function to easily convert all Attribute information into string
   * @return Attribute name and content as formatted string
   */
  string getAttributeInfo();

};

#endif	/* ATTRIBUTES_H */

