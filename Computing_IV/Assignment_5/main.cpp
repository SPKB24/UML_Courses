/* File:   main.cpp for project MusicLibraryReader_v2
 * Author: Jesse M. Heines, heines@cs.uml.edu
 *
 * created by JMH on February 13, 2010 at 12:35 PM
 */

#include <string>
#include <cstdlib>
#include <iostream>

#include "MusicLibraryReader.h"
// #include "GettysburgAddressReader.h"

using namespace std ;

/** The standard C++ main function.
 *  @param argc number of command line arguments
 *  @param argv array of pointers to command line arguments
 */
int main(int argc, char** argv) 
{
  // test for missing command line parameter
  if ( argc == 1 ) {
    // inform the user that a command line parameter is missing
    cout << "Usage: main xml-file-name" << endl << endl ;
    return EXIT_FAILURE ;
  }
  
  // process the input file
  ReadMusicLibrary_v2_1( argv[ 1 ], argv[ 2 ] ) ;
  
  // ReadGettysburgAddress( "GettysburgAddress.txt" ) ;

  // inform the user that the program executed to completion
  cout << endl << "~ Program Completed ~" << endl ;
  return EXIT_SUCCESS ;
}

