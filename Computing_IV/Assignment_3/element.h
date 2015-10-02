/* 
 * File:    element.h
 * Author:  Sohit Pal
 * Contact: sohitpal@outlook.com
 *
 * Created on September 10, 2015, 9:39 AM
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include <iostream>
#include <string>
using namespace std;

class Element
{  
  /**
   * This function will parse a line and get the Tag Name.
   * @param _lineToParse is the line that needs to be parsed.
   * @return Tag Name found in input parameter.
   */  
  string parseLine(string& _lineToParse);
  
  /**
   * To be used within parseLine(). Finds the open bracket in a given line.
   * @param _lineToParse is the line that will be searched.
   * @return A size_t that corresponds to the open brackets location.
   */
  size_t getOpenBracket(string& _lineToParse);
  
  /**
   * To be used within parseLine(). Finds the close bracket in a given line.
   * @param _lineToParse is the line that will be searched.
   * @param startPosition is the position that the function will start searching at.
   * @return A size_t that corresponds to the open brackets location
   */
  size_t getCloseBracket(string& _lineToParse, int startPosition);

  // PRIVATE MEMBER VARIABLES
  int    m_tagLine; // Store tag line number 
  string m_tagName; // Store tag name
  
public:
  /**
   * Default Constructor
   */
  Element() {};
  
  /**
   * Custom Constructor
   * @param _lineNumber is the line number of the element.
   * @param _lineEntire is the entire line. Will be parsed within this function.
   */
  Element(int _lineNumber, string _lineEntire);
  
  // PUBLIC GETTER FUNCTIONS
  string getTagLine() const;
  string getTagName() const;

};

#endif	/* ELEMENT_H */

