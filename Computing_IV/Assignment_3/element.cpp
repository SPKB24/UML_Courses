/* 
 * File:   element.cpp
 * Author: Sohit Pal
 * 
 * Created on September 10, 2015, 9:39 AM
 */

#include "element.h"
#include <sstream>
using namespace std;

/**
 * Int to String converter
 * @param arg is an integer that will be converted to a string
 * @return Will return arg (int) as a string
 */
string intToString(int arg)
{
  std::stringstream toString;
  toString << arg;
  return toString.str();
}

/**
 * Custom Constructor
 * @param _lineNumber is the line number of the element.
 * @param _lineEntire is the entire line. Will be parsed within this function.
 */
Element::Element(int _lineNumber, string _lineContent) : m_tagLine(_lineNumber) 
{
  // Parse lineContent here
  this->m_tagName = parseLine(_lineContent);
}

/**
 * This function will parse a line and get the Tag Name.
 * @param _lineToParse is the line that needs to be parsed.
 * @return Tag Name found in input parameter.
 */
string Element::parseLine(string& _lineToParse) 
{
  int start = getOpenBracket(_lineToParse) + 1;
  int end = getCloseBracket(_lineToParse, start);

  return _lineToParse.substr(start, (end - start));
}

/**
 * To be used within parseLine(). Finds the open bracket in a given line.
 * @param _lineToParse is the line that will be searched.
 * @return A size_t that corresponds to the open brackets location.
 */
size_t Element::getOpenBracket(string& _lineToParse)
{
  if (_lineToParse.find("<") != string::npos) 
  {
    return _lineToParse.find("<");
  }

  cout << "ERROR: Could not find opening bracket" << endl;
  return -1;
}

/**
 * To be used within parseLine(). Finds the close bracket in a given line.
 * @param _lineToParse is the line that will be searched.
 * @param startPosition is the position that the function will start searching at.
 * @return A size_t that corresponds to the open brackets location
 */
size_t Element::getCloseBracket(string& _lineToParse, int startPosition)
{
  int closeBracketPos = _lineToParse.find(">", startPosition);

  if (_lineToParse.find(" ", startPosition) == string::npos)
  {
    return closeBracketPos;
  } 
  else
  {
    int spacePos = _lineToParse.find(" ", startPosition);
    
    return (spacePos < closeBracketPos) ? spacePos : closeBracketPos;
  }
}

// ********************************* //
// GETTERS FOR PRIVATE CLASS MEMBERS //
// ********************************* //

string Element::getTagLine() const
{
  return intToString(m_tagLine);
}

string Element::getTagName() const
{
  return m_tagName;
}