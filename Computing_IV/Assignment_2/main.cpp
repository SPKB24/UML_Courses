/*
 * File:   main.cpp
 * Author: Sohit Pal
 *
 * Created on September 5, 2015, 6:14 PM
 */

#include <fstream>
#include <vector>
#include <iomanip>
#include "element.h"

using namespace std;

/**
 * Confirm that current line has an open tag before adding to vector
 * @param strLine: expects string keyword to search in string line
 * @return True or False based on if string contains open tag
 */
bool isOpenTag(string& strLine) 
{
  string closingSymbols[] = {"</", "<?", "<!"};

  for (string& arg : closingSymbols) 
  {
    if (strLine.find(arg) != string::npos) 
    {
      if (strLine.find("<") == strLine.find(arg))
      {
        return false;
      }
      else
      {
        return true;
      }
    }
  }

  return true;
}

// This following code was obtained from:
// https://piazza.com/class/icm9zfoyt6m5v0?cid=14
// It was written by Jesse Heines.
// I modified it as follows:
// 1. Changed (*it)->toString() to (*it)->printTagInfo()
void printAllTags(vector<Element*> vec)
{
  for (vector<Element*>::iterator it = vec.begin(); it != vec.end(); ++it) // THIS IS A GLOBAL (C++) PATTERN TO ITERATE THROUGH VECTORS
  {
    cout << setw(4) << (*it)->getTagLine() << " " << (*it)->getTagName() << endl;
  }
}

/**
 * Free the memory from the vector of element pointers
 * @param toDelete: vector to be deleted.
 */
void deleteVectorData(vector<Element*> &toDelete)
{
  cout << "DELETING VECTOR" << endl;

  for(Element* data : toDelete) 
  {
    delete data;
  }
  
  toDelete.clear();

  if (!toDelete.empty())
    cout << "Vector was deleted" << endl;
  else
    cout << "Vector was NOT deleted" << endl;
}

/*
 * @params expects file path to xml file via command line
 * @return default value 0
 */
int main(int argc, char** argv) 
{
  cout << "** Program Start **" << endl << endl;

  ifstream infile;

  int intLineCount = 0;     // Keep track of line number
  string strLine = "";      // Hold current line while parsing XML file
  vector<Element*> xmlData; // Will hold all tag names and tag lines

  // If argc has more than one arguments (first is default)
  if (argc > 1)
  {
    infile.open(argv[1], ifstream::in);

    do 
    {
      getline(infile, strLine);
      intLineCount++;

      if (isOpenTag(strLine))
      {
        xmlData.push_back(new Element(intLineCount, strLine));
      }

    } while (infile.good());

    printAllTags(xmlData);
    deleteVectorData(xmlData);    
  } 
  else
  {
    cout << "File Path was not provided." << endl;
  }

  return 0;
}
