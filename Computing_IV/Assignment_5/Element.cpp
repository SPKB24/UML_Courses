/* 
 * File:   Element.cpp
 * Author: Jesse M. Heines, heines@cs.uml.edu
 * 
 * created on January 20, 2012 at 9:10 AM
 * updated on February 13, 2012 at 1:10 PM
 * updated by JMH on October 21, 2015 at 9:22 PM to add attribute handling
 */

#include "Element.h"

#include <string>
#include <vector>
#include <stdio.h>  // for itoa

/**
 * NetBeans-supplied copy constructor.
 * @param orig the original object to copy.
 */
Element::Element( const Element& orig ) {
}

/**
 * NetBeans-supplied destructor.
 */
Element::~Element() {
}

/**
 * Default constructor, which initializes data members to placeholder values.
 */
Element::Element() {
  this->strTagName = "" ;   // empty tag name
  this->nLineNo = -1 ;      // placeholder
  this->strContent = "" ;   // empty content
  // note that it is not necessary to initialize the vector of children
  // note that it is not necessary to initialize the map of attributes
} ;

/**
 * Two-parameter constructor.
 * @param strElementName name of element extracted from an element opening tag
 * @param nLineNo line number at which the element opening tag was found
 */
Element::Element( string strElementName, int nLineNo ) {
  this->strTagName = strElementName ;
  this->nLineNo = nLineNo ;
  this->strContent = "" ;   // empty content
  // note that it is not necessary to initialize the vector of children
  // note that it is not necessary to initialize the map of attributes
}

/**
 * Three-parameter constructor.
 * @param strElementName name of element extracted from an element opening tag
 * @param nLineNo line number at which the element opening tag was found
 * @param strContent textual content contained in the element
 */
Element::Element( string strElementName, int nLineNo, string strContent ) {
  this->strTagName = strElementName ;
  this->nLineNo = nLineNo ;
  this->strContent = strContent ;   // empty content
  // note that it is not necessary to initialize the vector of children
  // note that it is not necessary to initialize the map of attributes
}

/**
 * Represent the object's information as a string in a reasonable format.
 * @return a string representing the object
 */
string Element::toString() {
  // the following way to convert numbers to strings is "standard-compliant"
  //    see http://cplusplus.com/reference/clibrary/cstdlib/itoa/
  
  // convert the line number to a string
  char cstrLineNo[8] ;
  sprintf( cstrLineNo, "%d", nLineNo ) ;
  string strLineNo = cstrLineNo ;

  // convert the vector size (number of children) to a string
  char cstrVecSize[8] ;
  sprintf( cstrVecSize, "%d", vecChildren.size() ) ;
  string strVecSize = cstrVecSize ;
  
  return "Element \"" + strTagName + "\" was found at line " + strLineNo + 
      ( strContent.length() == 0 ? " with no content" : 
      " containing \"" + strContent + "\"" ) + " and " + 
      ( vecChildren.size() == 0 ? "no children." : 
        strVecSize + " direct child" + ( vecChildren.size() == 1 ? "" : "ren" ) + "." ) ;
}

/**
 * Get the line number at which the current element was found.
 * @return line number at which the current element was found
 */
int Element::getNLineNo() const {
  return Element::nLineNo;
}

/**
 * Set the line number at which the current element was found.
 */
void Element::setNLineNo( int nLineNo ) {
  this->nLineNo = nLineNo ;
}

/**
 * Get the tag name of the element found.
 * @return tag name of the element found
 */
string Element::getStrTagName() const {
  return Element::strTagName;
}

/**
 * Set the tag name of the element found.
 */
void Element::setStrTagName( string strTagName ) {
  this->strTagName = strTagName ;
}

/**
 * Get the textual content contained in the element.
 * @return textual content contained in the element
 */
string Element::getStrContent() const {
  return Element::strContent;
}

/**
 * Set the textual content contained in the element.
 * @param strContent the content to set, read from the XML file
 */
void Element::setStrContent( string strContent ) {
  this->strContent = strContent;
}

/**
 * Get the vector of children of the current element.
 * @return the vector of children of this element
 */
vector<Element*> Element::getVecChildren() const {
  return Element::vecChildren;
}

/**
 * Add a child to the vector of children.
 * @param elemChild the child to add
 */
void Element::addChild( Element* elemChild ) {
  this->vecChildren.push_back( elemChild ) ;
}

/**
 * Add an attribute to the element.
 * @param key   the attribute's key string (to the left of the = sign)
 * @param value the attribute's value string (to the right of the = sign)
 */
void Element::addAttribute( string key, string value ) {
  this-> mapAttributes.insert( pair<string,string>( key, value ) ) ;
}
  
/**
 * Get the map containing the attributes for this element.
 * @return the map of attributes for this element
 */
map<string,string> Element::getMapAttributes() {
  return mapAttributes ;
}
