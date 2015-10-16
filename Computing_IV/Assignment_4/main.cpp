/*
 * File:    main.cpp
 * Author:  Sohit Pal
 * Contact: sohitpal@outlook.com
 *
 * Created on September 05, 2015, 06:14 PM
 * Updated on September 29, 2015, 05:00 PM 
 *  - Moved all parsing code to XMLReader.cpp/h. Simplified main().
 */

#include "element.h"
#include "XMLReader.h"

using namespace std;

/**
 * Check for command line argument and pass it to XMLReader to parse
 * @params expects file path to xml file via command line
 * @return default value 0
 */
int main(int argc, char** argv)
{
  cout << "** Program Start **" << endl << endl;

  // If filePath is provided in command line argument, read file
  if (argc > 1)
  {
    XMLReader(argv[1]);
  }
  else 
  {
    cerr << "ERROR: File Path was not provided." << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}