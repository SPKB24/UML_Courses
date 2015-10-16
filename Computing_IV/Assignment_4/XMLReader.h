/* 
 * File:    XMLReader.h
 * Author:  Sohit Pal
 * Contact: sohitpal@outlook.com
 *
 * Created on September 29, 2015, 05:40 PM
 * Updated on September 29, 2015, 10:13 PM 
 *  - Read through file and get ParserState for all lines
 * Updated on September 30, 2015, 10:37 PM
 *  - Added lots of error checking to avoid runtime errors
 *  - Cut some code blocks into separate functions for readability
 * Updated on October 16, 2015, 01:04 AM
 *  - Created tree from all XML open tags (very simply put)
 */

#ifndef XMLREADER_H
#define	XMLREADER_H

#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include "element.h"
#include "Attributes.h"
using namespace std;

/**
 * This will loop through the file and extract XML Data.
 * @param _fileName the path to the file which will be read
 */
int XMLReader( string _fileName );

/**
 * This function will print out all data specific to the parserState provided
 * @param _vecToPrint  vector all all elements
 * @param _lineState   ParserState of line from XML File
 * @param _lineNum     current line's number
 * @param _strLine     current line
 * @param _lastElement The tag name of the last opening tag
 */
void printXMLData( vector<Element*>& _vecToPrint, ParserState& _lineState,
        int _lineNum, string& _strLine, string _lastElement);

/**
 * This function will parse a line and return its parser state 
 * @param _strLine        Line read from XML file
 * @param _currentState   State of parser on entry into this function
 * @return State of parser on based on provided line
 */
ParserState GetXMLData( string _strLine, ParserState _currentState );

/**
 * Function to print out vector contents
 * @param _vecToPrint vector to be printed to standard output
 */
void printVector( vector<Element*>& _vecToPrint );

/**
 * Will find and return the last element in the vector (stack)
 * @param _vecElements vector of elements to search from
 * @return tag name of last element in vector (stack)
 */
string getLastElement( vector<Element*>& _vecElements );

/**
 * Will parse line and return tag name for closing tags
 * ** ONLY TO BE USED ON LINES WITH PARSER STATE = ELEMENT_CLOSING_TAG
 * @param _strLine line to be parsed
 * @return The tag name found in _strLine
 */
string getClosingTagName( string& _strLine );

/**
 * Will parse line and return tag content
 * ** ONLY TO BE USED ON LINES WITH PARSER STATE = ELEMENT_NAME_AND_CONTENT
 * @param _strLine line to be parsed
 * @return The tag content found in _strLine
 */
string getTagContent( string& _strLine );

/**
 * Will parse line and return a vector of attribute pointers
 * @param _strLine line to be parsed
 * @return vector of attribute pointers
 */
vector<Attributes*> getAttributes( string& _strLine );

/**
 * Function to split up a lines words by spaces
 * @param strLine line to be split up
 * @param delimeter character or string to split line up
 * @return vector<string>'s that contain individual words
 */
vector<string> split( string strLine, string delimeter );

/**
 * This function is used during debugging to display the parser state.
 * @param ps the parser state
 * 
 * // This following code was obtained from:
 * // https://teaching.cs.uml.edu/~heines/91.204/91.204-2015-16f/204-lecs/lecture08.jsp
 * // It was written by Jesse Heines.
 * // Changes made are as follows:
 * // 1. Changed some output formatting
 */
void ShowState( ParserState ps );

/**
 * Free the memory from the vector of element pointers
 * @param _toDelete: vector to be deleted.
 */
void deleteVectorData( vector<Element*>& _toDelete );

/**
 * Trim leading and trailing white space (spaces and tabs) from the 
 *    string passed as an argument and return the trimmed string.
 * @param str string to trim
 * @return trimmed string
 * 
 * // This following code was obtained from:
 * // https://teaching.cs.uml.edu/~heines/91.204/91.204-2015-16f/204-lecs/lecture03.jsp
 * // It was written by Jesse Heines.
 * // Changes made as are follows:
 * // 1. Changed function name from trim() to removeWhiteSpace()
 * // 2. Changed return type from string to void since we are passing reference 
 * //    as parameter
 */
void removeWhiteSpace( string& _str );

#endif	/* XMLREADER_H */

