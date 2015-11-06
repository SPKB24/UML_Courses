/* File:   MusicLibraryReader.h
 * Author: Jesse M. Heines, heines@cs.uml.edu
 *
 * created by JMH on 2012-02-13 at 12:40 PM
 */

#ifndef _MUSICFILEREADER_H
#define	_MUSICFILEREADER_H

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>      // needed for floor function
#include <cstdlib>    // needed for EXIT_FAILURE and EXIT_SUCCESS
#include <iomanip>    // needed for setw

using namespace std ;

/**
 * Variable to dictate when the tree is on the root element
 */
const int gRootLevel = 1;

/**
 * Read the file passed as a parameter and process it by lines.  This is a
 *    rudimentary way of parsing the file.<br/>
 * @param strFileName name of file to read
 * @return status code
 */
int GetXMLData( string strFileName );

  /**
 * Read the file passed as a parameter and process it by lines.  This is a
 *    rudimentary way of parsing the file.
 * @param strFileName name of file to read.
 * @param strOutFile name of file to output JSON.
 * @return status code
 */
int ReadMusicLibrary_v2_1( string strFileName, string strOutFile) ;

#endif	/* _MUSICFILEREADER_H */

