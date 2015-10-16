/* 
 * File:   Attributes.cpp
 * Author: Sohit
 * 
 * Created on October 13, 2015, 9:51 PM
 */

#include "Attributes.h"

/**
 * Default Constructor
 */
Attributes::Attributes()
{
  // Do Nothing
}

/**
 * Custom Constructor
 * @param attrName Attribute Name
 * @param attrContent Attribute Content
 */
Attributes::Attributes(string _name, string _content)
{
  strip(_content, "\"");

  this->m_attributeName = _name;
  this->m_attributeContent = _content;
}

/**
 * Custom Constructor
 * @param _attributes vector of strings as input.
 */
Attributes::Attributes(vector<string> _attributes)
{
  if (_attributes.size() != 2)
  {
    cout << "ERROR: ATTRIBUTE NOT WORKING" << endl;
    cout << "ATT SIZE = " << _attributes.size() << endl;
  }

  strip(_attributes[1], "\"");

  this->m_attributeName = _attributes[0];
  this->m_attributeContent = _attributes[1];
}

/**
 * Function to easily convert all Attribute information into string
 * @return Attribute name and content as formatted string
 */
string Attributes::getAttributeInfo()
{
  return (this->m_attributeName + string(":'") + this->m_attributeContent + string("'"));
}

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
void Attributes::strip(string& str, string delimiter)
{
  while (str.find(delimiter, 0) != string::npos)
  {
    str.erase(str.begin() + str.find(delimiter, 0));
  }
}

