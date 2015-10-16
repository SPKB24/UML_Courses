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
   * @param _lineEntire is the entire line to be parsed within this function.
   * @param _treeLevel is the level of which the element is in the tree.
   * @param _state is the state of the inputted line
   *        (ELEMENT_OPENING_TAG or ELEMENT_NAME_AND_CONTENT)
   */
Element::Element(int _lineNumber, string _lineContent, int _treeLevel, ParserState _state) 
                 : m_tagLine(_lineNumber), m_treeLevel(_treeLevel)
{
  // Parse lineContent here
  this->m_tagName = parseLine(_lineContent, _state);
}

 /**
   * This function will add a child Element to vecChildren
   * @param _elementToAdd child element to be added to this->m_vecChildren
   */
  void Element::addChild( Element* _elementToAdd )
  {
    cout << "Adding " << _elementToAdd->m_tagName << " as child of " << m_tagName << endl;
    m_vecChildren.push_back(_elementToAdd);
  }

/**
   * This function will add an attribute object to m_vecAttributes
   * @param _vecAttributes a vector of Attributes
   */
void Element::addAttribute( vector<Attributes*> _vecAttributes )
{
  for ( Attributes* arg : _vecAttributes )
  {
    this->m_vecAttributes.push_back(arg);
  }
}

/**
 * This function will parse a line and get the Tag Name.
 * @param _lineToParse is the line that needs to be parsed.
 * @param _state the state of the line to parse.
 * @return Tag Name found in input parameter.
 */
string Element::parseLine(string& _lineToParse, ParserState _state)
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

/**
   * Getter Function
   * @return m_tagLine - variable storing tag line
   */
string Element::getTagLine() const
{
  return intToString(m_tagLine);
}

/**
   * Getter Function
   * @return m_tagName - variable storing tag name
   */
string Element::getTagName() const
{
  return m_tagName;
}

/**
 * Getter Function
 * @return m_treeLevel - variable storing tree level
 */
int Element::getTreeLevel() const
{
  return m_treeLevel;
}

/**
 * Getter Function
 * @return m_vecChildren
 */
vector<Element*> Element::getChildElements()
{
  return m_vecChildren;
}
  
/**
   * Getter Function
   * @return m_vecAttributes
   */
vector<Attributes*> Element::getAttributes()
{
  return m_vecAttributes;
}
  