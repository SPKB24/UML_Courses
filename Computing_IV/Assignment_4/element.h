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
#include <cstdlib>
#include <string>
#include <vector>
#include "Attributes.h"
using namespace std;

/**
 * The various parser states
 * 
 * // This following code was obtained from:
 * // https://teaching.cs.uml.edu/~heines/91.204/91.204-2015-16f/204-lecs/lecture08.jsp
 * // It was written by Jesse Heines.
 * // Changed made are as follows:
 * // 1. Added BLANK_LINE state to catch any blank lines
 */
enum ParserState { UNKNOWN, STARTING_DOCUMENT, DIRECTIVE,
    ELEMENT_OPENING_TAG, ELEMENT_CONTENT, ELEMENT_NAME_AND_CONTENT,
    ELEMENT_CLOSING_TAG, SELF_CLOSING_TAG,
    STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
    BLANK_LINE, ERROR } ;

class Element
{
  /**
   * This function will parse a line and get the Tag Name.
   * @param _lineToParse is the line that needs to be parsed.
   * @param _state the state of the line to parse.
   * @return Tag Name found in input parameter.
   */
  string parseLine(string& _lineToParse, ParserState _state);
  
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
  
  
  /** Store tag line number */
  int    m_tagLine;
  
  /** Store tag name */
  string m_tagName;
  
  /** Store level of element in Tree */
  int    m_treeLevel;
  
  /** Store pointers to children elements */
  vector<Element*> m_vecChildren;
  
  /** Store all attributes */
  vector<Attributes*> m_vecAttributes;
  
public:
  /**
   * Default Constructor
   */
  Element() {};
  
  /**
   * Custom Constructor
   * @param _lineNumber is the line number of the element.
   * @param _lineEntire is the entire line to be parsed within this function.
   * @param _treeLevel is the level of which the element is in the tree.
   * @param _state is the state of the inputted line
   *        (ELEMENT_OPENING_TAG or ELEMENT_NAME_AND_CONTENT)
   */
  Element(int _lineNumber, string _lineEntire, int _treeLevel, ParserState _state);
  
  /**
   * This function will add a child Element to vecChildren
   * @param _elementToAdd child element to be added to this->m_vecChildren
   */
  void addChild( Element* _elementToAdd );
  
/**
   * This function will add an attribute object to m_vecAttributes
   * @param _vecAttributes a vector of Attributes
   */
  void addAttribute( vector<Attributes*> _vecAttributes );
  
  /**
   * Getter Function
   * @return m_tagLine - variable storing tag line
   */
  string getTagLine() const;
  
  /**
   * Getter Function
   * @return m_tagName - variable storing tag name
   */
  string getTagName() const;
  
  /**
   * Getter Function
   * @return m_treeLevel - variable storing tree level
   */
  int getTreeLevel() const;
  
  /**
   * Getter Function
   * @return m_vecChildren
   */
  vector<Element*> getChildElements();
  
  /**
   * Getter Function
   * @return m_vecAttributes
   */
  vector<Attributes*> getAttributes();
  
};

#endif	/* ELEMENT_H */

