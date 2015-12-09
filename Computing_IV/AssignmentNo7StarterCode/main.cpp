/* 
 * File:   main.cpp
 * Author: Jesse Heines, heines@cs.uml.edu
 *
 * Created on November 23, 2015, 10:23 AM
 */

#include <iostream>  // for cout and friends
#include <sstream>   // for string streams
#include <string>    // for the STL string class
#include <regex>     // for regular expressions

#include "jmhUtilities.h"

using namespace std;

// forward references
void ParseCommandString( string strUserEntry ) ;
void ProcessAddCommand( string strUserEntry ) ;
void ProcessAddElementCommand( string strUserEntry ) ;
void ProcessAddAttributeCommand( string strUserEntry ) ;
void ProcessPrintCommand( string strUserEntry ) ;


/**
 * The standard C++ main function.
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 
 */
int main(int argc, char** argv) {
  
  // display program title
  cout << "=============================" << endl ;
  cout << "Assignment No. 7 Starter Code" << endl ;
  cout << "=============================" << endl ;
    
  // string entered by the user in response to the command prompt
  string strUserEntry = "" ;
  
//  // prompt the user to enter a command string
//  // version 1 without using a regular expression
//  while ( ! jmhUtilities::caseInsCompare( jmhUtilities::trim( strUserEntry ), "quit" ) ) {
//    cout << "\nYour command: " ;
//    getline( cin, strUserEntry ) ;
//  }
  
  // prompt the user to enter a command string
  // version 2 using a regular expression
  regex reQuit( "\\s*quit\\s*", regex::icase ) ;
  while( ! regex_match( strUserEntry, reQuit ) ) {
    cout << "\nYour command: " ;
    getline( cin, strUserEntry ) ;
    
    // if the user didn't enter 'quit', go parse the command string
    if ( ! regex_match( strUserEntry, reQuit ) ) {
      ParseCommandString( strUserEntry ) ;
    }
  }

  return EXIT_SUCCESS ;
}


/**
 * Check for a valid basic command.
 * @param strUserEntry command string entered by the user
 */
void ParseCommandString( string strUserEntry ) {
  // regular expressions for basic commands
  regex reBasicAddCommand( "\\s*add.*", regex::icase ) ;
  regex reBasicPrintCommand( "\\s*print.*", regex::icase ) ;
  regex reBasicHelpCommand( "\\s*help.*", regex::icase ) ;
  
  // test for each basic command in turn
  if ( regex_match( strUserEntry, reBasicAddCommand ) ) {
    ProcessAddCommand( strUserEntry ) ;
  } else if ( regex_match( strUserEntry, reBasicPrintCommand ) ) {
    ProcessPrintCommand( strUserEntry ) ;
  } else if ( regex_match( strUserEntry, reBasicHelpCommand ) ) {
    cout << "  Commands are:" << endl ;
    cout << "    add element parent_name element_name" << endl ;
    cout << "    add attribute parent_name attribute_name attribute_value" << endl ;
    cout << "    print" << endl ;
    cout << "    help (this command)" << endl ;
    cout << "    quit" << endl ;
  } else {
    cout << "  Invalid command.  Acceptable commands are 'add', 'print', 'help', and 'quit'." << endl ;
  }
}


/**
 * Handle an add command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddCommand( string strUserEntry ) {
  // regular expressions for the second parameter in the add command
  regex reAddElementCommand( "\\s*add\\s+element.*", regex::icase ) ;
  regex reAddAttributeCommand( "\\s*add\\s+attribute.*", regex::icase ) ;

  // test for each possible second parameter in turn
  if ( regex_match( strUserEntry, reAddElementCommand ) ) {
    ProcessAddElementCommand( strUserEntry ) ;
  } else if ( regex_match( strUserEntry, reAddAttributeCommand ) ) {
    ProcessAddAttributeCommand( strUserEntry ) ;
  } else {
    cout << "  Invalid add command: 2nd parameter must be 'element' or 'attribute'." << endl ;
  }
}


/**
 * Handle an add element command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddElementCommand( string strUserEntry ) {
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  // regular expression to pick out the name of the parent to which the new element is to be added 
  //    and the name of the new element itself
  regex reAddElementCmd( "^\\s*add\\s*element\\s(\\w+)\\s(\\w+)(.*)$", regex::icase ) ;
  
  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAddElementCmd ) ) {
    cout << "  You have specified that you want to add a new element named '" << what[2] 
         << "' to parent element '" << what[1] << "'." << endl ;
  } else {
    cout << "  Invalid 'add element' command." << endl ;
    cout << "    'add element' must be followed by two more parameters:" << endl ;
    cout << "      (1) the name of the parent to which the new element is to be added, and" << endl ;
    cout << "      (2) the name of the new element itself." << endl ;
  }
}


/**
 * Handle an add attribute command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddAttributeCommand( string strUserEntry ) {
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group
  // what[2] contains the second matched group
  // what[3] etc.
  
  // regular expression to pick out the name of the element to which the new attribute is to be added,
  //    the name of the new attribute, and the value of that attribute
  regex reAddAttributeCmd( "^\\s*add\\s*attribute\\s(\\w+)\\s(\\w+)\\s(\\w+)(.*)$", regex::icase ) ;
  
  // note that the following variant of the regex_match command requires a C string, not an STL string
  if ( regex_match( strUserEntry.c_str(), what, reAddAttributeCmd ) ) {
    cout << "  You have specified that you want to add a new attribute named '" << what[2] 
         << "' with a value of '" << what[3] << "' to element '"  << what[1] << "'." << endl ;
  } else {
    cout << "  Invalid 'add attribute' command." << endl ;
    cout << "    'add attribute' must be followed by three more parameters:" << endl ;
    cout << "      (1) the name of the element to which the new attribute to be added," << endl ;
    cout << "      (2) the name of the new attribute to be added, and " << endl ;
    cout << "      (3) the value of the new attribute to be added." << endl ;
  }
}


/**
 * Handle a print command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessPrintCommand( string strUserEntry ) {
  cout << "  ... add your code to handle a print command here ..." << endl ;
}
