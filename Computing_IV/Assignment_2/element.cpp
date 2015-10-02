/* 
 * File:   element.cpp
 * Author: Sohit Pal
 * 
 * Created on September 10, 2015, 9:39 AM
 */

#include "element.h"
#include <sstream>
using namespace std;

int getIntLength(int tagLine) {
  int length = 1;

  while (tagLine > 9) {
    length++;
    tagLine /= 10;
  }

  return length;
}

string intToString(int arg) {
  std::stringstream toString;
  toString << arg;
  return toString.str();
}

Element::Element(int _lineNumber, string _lineContent) : m_tagLine(_lineNumber) 
{
  // Parse lineContent here
  this->m_tagName = parseLine(_lineContent);
}

string Element::parseLine(string& _lineToParse) {
  int start = getOpenBracket(_lineToParse) + 1;
  int end = getCloseBracket(_lineToParse, start);

  return _lineToParse.substr(start, (end - start));
}

size_t Element::getOpenBracket(string& _lineToParse) {
  if (_lineToParse.find("<") != string::npos) {
    return _lineToParse.find("<");
  }

  cout << "ERROR: Could not find opening bracket" << endl;
  return -1;
}

size_t Element::getCloseBracket(string& _lineToParse, int startPosition) {
  int closeBracketPos = _lineToParse.find(">", startPosition);

  if (_lineToParse.find(" ", startPosition) == string::npos) {
    return closeBracketPos;
  } else {
    int spacePos = _lineToParse.find(" ", startPosition);

    if (spacePos < closeBracketPos) {
      return spacePos;
    }

    return closeBracketPos;
  }
}

string Element::getTagLine() const {
  return intToString(m_tagLine);
}

string Element::getTagName() const {
  return m_tagName;
}