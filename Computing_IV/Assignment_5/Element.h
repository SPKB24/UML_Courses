/* 
 * File:   Element.h
 * Author: Jesse M. Heines, heines@cs.uml.edu
 *
 * created by JMH on January 20, 2012 at 9:10 AM
 * updated by JMH on February 13, 2012 at 1:10 PM
 * updated by JMH on October 21, 2015 at 9:22 PM to add attribute handling
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std ;

/**
 * This class represents an element in the XML file.  It has been expanded from the
 * version used in Assignment No. 1 to include elements need for Assignment No. 2.
 * @author Jesse M. Heines, <a href="mailto:heines@cs.uml.edu">heines@cs.uml.edu</a>
 * @version 2.01, 2012-02-13
 */
class Element {

private:

  /** name of element extracted from an element opening tag */
  string strTagName ;

  /** line number at which the element opening tag was found */
  int nLineNo ;
  
  /** the textual content of the element */
  string strContent ;
  
  /** vector of children */
  vector<Element*> vecChildren ;
  
  /** map of attribute name/value pairs */
  map<string,string> mapAttributes ;
  
public:

  /**
   * Default constructor, which initializes data members to placeholder values.
   */
  Element();

  /**
   * Two-parameter constructor.
   * @param strElementName name of element extracted from an element opening tag
   * @param nLineNo line number at which the element opening tag was found
   */
  Element( string strElementName, int nLineNo ) ;
  
  /**
   * Three-parameter constructor.
   * @param strElementName name of element extracted from an element opening tag
   * @param nLineNo line number at which the element opening tag was found
   * @param strContent textual content contained in the element
   */
  Element( string strElementName, int nLineNo, string strContent ) ;

  /** NetBeans-supplied copy constructor. */
  Element(const Element& orig) ;
  
  /** NetBeans-supplied destructor. */
  virtual ~Element() ;
  
	/**
   * Get the line number at which the current element was found.
   * @return line number at which the current element was found
   */
  int getNLineNo() const ;

	/**
   * Set the line number at which the current element was found.
   */
  void setNLineNo( int nLineNo ) ;

  /**
   * Get the tag name of the element found.
   * @return tag name of the element found
   */
  string getStrTagName() const ;

	/**
   * Set the tag name of the element found.
   */
  void setStrTagName( string strTagName ) ;

  /**
   * Get the textual content contained in the element.
   * @return textual content contained in the element
   */
  string getStrContent() const ;

  /**
   * Set the textual content contained in the element.
   * @param strContent the content to set, read from the XML file
   */
  void setStrContent( string strContent ) ;

  /**
   * Get the vector of children of the current element.
   * @return the vector of children of this element
   */
  vector<Element*> getVecChildren() const ;

  /**
   * Add a child to the vector of children.
   * @param elemChild the child to add
   */
  void addChild( Element* elemChild ) ;

  /**
   * Represent the object's information as a string in a reasonable format.
   * @return a string representing the object
   */
  string toString() ;
  
  /**
   * Add an attribute to the element.
   * @param key   the attribute's key string (to the left of the = sign)
   * @param value the attribute's value string (to the right of the = sign)
   */
  void addAttribute( string key, string value ) ;
  
  /**
   * Get the map containing the attributes for this element.
   * @return the map of attributes for this element
   */
  map<string,string> getMapAttributes() ;

} ;

#endif	/* ELEMENT_H */

