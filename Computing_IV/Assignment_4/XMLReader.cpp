#include "XMLReader.h"
#include "element.h"

void RecursivePrint( Element* root )
{
  vector<Element*> children = root->getChildElements();
  string spaces;
  
  // if ROOT ELEMENT
  if (root->getTreeLevel() == 0)
  {
    cout << "[" << root->getTreeLevel();
    cout << "] '" << root->getTagName();
    cout << "' has " << root->getChildElements().size() << " direct children " << endl;
  }
  
  for (Element* child : children)
  {
    spaces = "";
    
    for(int i = 0; i < child->getTreeLevel(); i++)
    {
      if (i == child->getTreeLevel() - 1)
      {
        spaces += "|||";
      }
      else
      {
        spaces += "|  ";
      }
    }
    
    cout << spaces << "[" << child->getTreeLevel();
    cout << "] '" << child->getTagName();
    
    if (child->getChildElements().size() == 1)
    {
      cout << "' has 1 direct child";
    }
    else
    {
      cout << "' has " << child->getChildElements().size() << " direct children";
    }
    
    int numAttributes = child->getAttributes().size();
    if (numAttributes > 0)
    {
      if (numAttributes == 1)
      {
        cout << " and " << numAttributes << " attribute { ";
      }
      else
      {
        cout << " and " << numAttributes << " attributes { ";
      }
      
      for ( Attributes* arg : child->getAttributes())
      {
        cout << arg->getAttributeInfo() << " ";
      }
      
      cout << "}";
    }
    
    cout << endl;
    
    RecursivePrint(child);
  }
}

/**
 * This will loop through the file and extract XML Data.
 * @param _fileName the path to the file which will be read
 */
int XMLReader(string _fileName)
{
  ifstream         infile;           // Input file stream for XML file to parse
  int              intLineCount = 0; // Keep track of line number
  string           strLine = "";     // Hold current line while parsing XML file
  vector<Element*> vecElementStack;  // Will hold all tag names and tag lines
  string previousElementName = "";   // The tag name of the previous element on the vector (stack)
  ParserState currentState = STARTING_DOCUMENT; // Will hold state of previously read line
  
  Element* rootElement = NULL;
  
  infile.open(_fileName, ifstream::in);
  
  if ( infile.fail() )
  {
    cerr << "Error opening '" << _fileName << "'" << endl ;
    return EXIT_FAILURE;
  }
  else
  {
    // Loop through the file
    do
    {
      // Increment line counter
      intLineCount++;
      
      // Read a new line from the file
      getline(infile, strLine);
      
      // Get tag name of previous open tag element (will return "" if none)
      previousElementName = getLastElement(vecElementStack);
      
      // Get state of newly read line
      currentState = GetXMLData(strLine, currentState);
      
      // Handle parser state specific actions
      if (currentState == ELEMENT_OPENING_TAG) //########################## HERE
      {
        Element* tempElement = new Element(intLineCount, strLine, vecElementStack.size(), currentState);
        tempElement->addAttribute(getAttributes(strLine));
        
        if (rootElement == NULL) // First time adding to the tree
        {
          rootElement = tempElement;
        }
        else
        {
          (vecElementStack[ vecElementStack.size() - 1 ])->addChild( tempElement );
        }
        
        vecElementStack.push_back(tempElement);
        previousElementName = getLastElement(vecElementStack);
      }
      else if (currentState == ELEMENT_CLOSING_TAG)
      {
        if (previousElementName != getClosingTagName(strLine))
        {
          // if open tag name != closing tag name
          cout << endl << "*******************************************" << endl;
          cout << "ERROR: Invalid closing tag at Line " << intLineCount << endl;
          cout << "REASON: " << previousElementName << " != " << getClosingTagName(strLine) << endl;
          cout << "ABORTING..." << endl;
          cout << "*******************************************" << endl;
          return EXIT_FAILURE;
        }
        
        vecElementStack.pop_back();
      }
      else if (currentState == ELEMENT_NAME_AND_CONTENT)
      {
        Element* tempElement = new Element(intLineCount, strLine, vecElementStack.size(), currentState);
        tempElement->addAttribute(getAttributes(strLine));
        
        (vecElementStack[ vecElementStack.size() - 1 ])->addChild( tempElement );
      }
      else if (currentState == ERROR)
      {
        removeWhiteSpace(strLine);
        
        cout << endl << "*******************************************" << endl;
        cout << "ERROR: Something went wrong!" << endl;
        cout << "~~ Line " << intLineCount << ": " << strLine << endl;
        cout << "ABORTING..." << endl;
        cout << "*******************************************" << endl;
        return EXIT_FAILURE;
      }
      
      printXMLData(vecElementStack, currentState, intLineCount, strLine, previousElementName);

      cout << endl;
      
    } while (infile.good());
    
    cout << endl << endl << endl << "TREE OUTPUT" << endl;
    cout << "********************************************************" << endl;
    
    RecursivePrint(rootElement);

    deleteVectorData(vecElementStack);
  }
}

/**
 * This function will print out all data specific to the parserState provided
 * @param _vecToPrint  vector all all elements
 * @param _lineState   ParserState of line from XML File
 * @param _lineNum     current line's number
 * @param _strLine     current line
 * @param _lastElement The tag name of the last opening tag
 */
void printXMLData( vector<Element*>& _vecToPrint, ParserState& _lineState, 
        int _lineNum, string& _strLine, string _lastElement )
{
  //if ( == ELEMENT_OPENING_TAG)
  if (1 == 1)
  {
    // Remove whitespace from the line
    removeWhiteSpace(_strLine);

    // Print line number and content
    cout << _lineNum << ". " << _strLine << endl;
    cout << "---------------------------------------------------------------------" << endl;

    // Print line parser state
    ShowState(_lineState);

    // Handle parser state specific actions
    if (_lineState == ELEMENT_OPENING_TAG)
    {    
      cout << "-- Adding '" << _lastElement << "' to Vector (Stack)" << endl;
      printVector(_vecToPrint);
    }
    else if (_lineState == ELEMENT_CLOSING_TAG)
    {
      cout << "-- Removing '" << _lastElement << "' from Vector (Stack)" << endl;
      printVector(_vecToPrint);
    }
    else if (_lineState == ELEMENT_NAME_AND_CONTENT || _lineState == SELF_CLOSING_TAG)
    {
      if (_lineState == ELEMENT_NAME_AND_CONTENT)
      {
        cout << "--   TAG NAME: '" << _lastElement << "'" << endl;
        cout << "--   TAG CONTENT: '" << getTagContent(_strLine) << "'" << endl;
      }

      cout << "-- Vector (Stack) unchanged" << endl;
    }
  }
}

/**
 * This function will parse a line and return its parser state 
 * @param _strLine        Line read from XML file
 * @param _currentState   State of parser on entry into this function
 * @return State of parser on based on provided line
 */
ParserState GetXMLData( string _strLine, ParserState _currentState )
{
  string symbols[] = {"<?", "<!--", "-->", "</", "<"};
  string lineType = "";
  ParserState valToReturn = UNKNOWN;
  
  for (string& arg : symbols)
  {
    if (_strLine.find(arg) != string::npos)
    {
      lineType = arg;
      break;
    }
  }
  
  // if NOT part of a comment
  if (_currentState != STARTING_COMMENT && _currentState != IN_COMMENT)
  {
    if (lineType == "<?")
    {
      if (_currentState == STARTING_DOCUMENT)
      {
        valToReturn = DIRECTIVE;
      }
    }
    else if (lineType == "<!--")
    {
      valToReturn = STARTING_COMMENT;
      
      if (_strLine.find("-->") != string::npos)
      {        
        valToReturn = ONE_LINE_COMMENT;
      }
    }
    else if (lineType == "</")
    {
      valToReturn = ELEMENT_CLOSING_TAG;
      
      // Check if ELEMENT_CLOSING_TAG
      int posOpenTag  = _strLine.find("<");
      int posCloseTag = _strLine.find("</");
      
      if (posCloseTag > posOpenTag)
      {
        valToReturn = ELEMENT_NAME_AND_CONTENT;
      }
    }
    else if (lineType == "<")
    {
      valToReturn = ELEMENT_OPENING_TAG;
      
      // This could possibly be a self closing tag. Let's confirm.
      if (_strLine.find("/>") != string::npos)
      {
        valToReturn = SELF_CLOSING_TAG;
      }
    }
    else
    {
      valToReturn = ERROR;
      
      if (_strLine.size() == 0)
      {
        valToReturn = BLANK_LINE;
      }
    }
  }
  else // it is either part of the comment or a comment end
  {
    valToReturn = IN_COMMENT;
    
    if (lineType == "-->")
    {
      valToReturn = ENDING_COMMENT;
    }
  }
  
  return valToReturn;
}

/**
 * Function to print out vector contents
 * @param _vecToPrint vector to be printed to standard output
 */
void printVector( vector<Element*>& _vecToPrint )
{
  cout << "-- Vector(Stack) contains:";
  
  if (_vecToPrint.size() > 0)
  {
    for (Element* arg : _vecToPrint)
    {
      cout << " " << arg->getTagName();
    }
  }
  else
  {
    cout << " {EMPTY}";
  }
  
  cout << endl;
}

/**
 * Will find and return the last element in the vector (stack)
 * @param _vecElements vector of elements to search from
 * @return tag name of last element in vector (stack)
 */
string getLastElement( vector<Element*>& _vecElements )
{
  string lastElementName = "";
  size_t vectorSize = _vecElements.size();
  
  if (vectorSize != 0)
  {
    lastElementName = _vecElements[ vectorSize -1 ]->getTagName();
  }
  
  return lastElementName;
}

/**
 * Will parse line and return tag name for closing tags
 * ** ONLY TO BE USED ON LINES WITH PARSER STATE = ELEMENT_CLOSING_TAG
 * @param _strLine line to be parsed
 * @return The tag name found in _strLine
 */
string getClosingTagName( string& _strLine )
{
  int posOpenTag    = _strLine.find("</");
  int posClosingTag = _strLine.find(">"); 
  
  posOpenTag += 2; // To accommodate for '</'
  
  return _strLine.substr(posOpenTag, (posClosingTag - posOpenTag));
}

/**
 * Will parse line and return tag content
 * ** ONLY TO BE USED ON LINES WITH PARSER STATE = ELEMENT_NAME_AND_CONTENT
 * @param _strLine line to be parsed
 * @return The tag content found in _strLine
 */
string getTagContent( string& _strLine )
{  
  int posLeftEndPoint  = _strLine.find(">");
  int posRightEndPoint = _strLine.find("</");
  
  posLeftEndPoint += 1; // To accommodate for '>'
          
  return _strLine.substr(posLeftEndPoint, (posRightEndPoint - posLeftEndPoint));
}

/**
 * Will parse line and return a vector of attribute pointers
 * @param _strLine line to be parsed
 * @return vector of attribute pointers
 */
vector<Attributes*> getAttributes( string& _strLine )
{  
  vector<Attributes*> vecAttributes;
  string strippedLine;
  
  removeWhiteSpace(_strLine);
  
  int openBracket  = _strLine.find("<") + 1;
  int closeBracket = _strLine.find(">", openBracket);

  strippedLine = _strLine.substr(openBracket, (closeBracket - openBracket));
  
  if (strippedLine.find(" ") == string::npos)
  {
    return vecAttributes;
  }
  
  vector<string> stringSplit = split(strippedLine, " ");
  
  for (string arg : stringSplit)
  {
    if (arg.find("=") != string::npos)
    {
      vecAttributes.push_back(new Attributes(split(arg, "=")));
    }
  }
  return vecAttributes;
}

/**
 * Function to split up a lines words by spaces
 * @param strLine line to be split up
 * @param delimeter character or string to split line up
 * @return vector<string>'s that contain individual words
 */
vector<string> split( string strLine, string delimeter )
{
  vector<string> vecSplitItems;
  
  int leftBound = 0;
  int spacePos = strLine.find(delimeter); // 8

  while( spacePos != string::npos )
  {    
    if (strLine.find("\"") != string::npos)
    {
      int qStart = strLine.find("\"", leftBound);
      int qEnd   = strLine.find("\"", qStart + 1);
      
      if (spacePos > qStart && spacePos < qEnd)
      {
        spacePos = strLine.find(delimeter, qEnd);
      }
    }
    
    if (spacePos == string::npos)
    {
      break;
    }
    
    vecSplitItems.push_back(strLine.substr(leftBound, (spacePos - leftBound)));
    strLine.erase(leftBound, (spacePos - leftBound + 1));

    spacePos = strLine.find(" ", leftBound);
  }

  if (spacePos < strLine.size())
  {
    vecSplitItems.push_back( strLine.substr( leftBound, (spacePos - leftBound + 1 )));
  }
  else
  {
    vecSplitItems.push_back( strLine.substr( leftBound, (strLine.size() - leftBound + 1 )));
  }

  return vecSplitItems;
}

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
void ShowState( ParserState ps )
{
  cout << "PARSER STATE: ";
  switch ( ps )
  {
    case UNKNOWN : cout << "UNKNOWN" ; break ;
    case STARTING_DOCUMENT : cout << "STARTING_DOCUMENT" ; break ;
    case DIRECTIVE : cout << "DIRECTIVE" ; break ;
    case ELEMENT_OPENING_TAG : cout << "ELEMENT_OPENING_TAG" ; break ;
    case ELEMENT_CONTENT : cout << "ELEMENT_CONTENT" ; break ;
    case ELEMENT_NAME_AND_CONTENT : cout << "ELEMENT_NAME_AND_CONTENT" ; break ;
    case ELEMENT_CLOSING_TAG : cout << "ELEMENT_CLOSING_TAG" ; break ;
    case SELF_CLOSING_TAG : cout << "SELF_CLOSING_TAG" ; break ;
    case STARTING_COMMENT : cout << "STARTING_COMMENT" ; break ;
    case IN_COMMENT : cout << "IN_COMMENT" ; break ;
    case ENDING_COMMENT : cout << "ENDING_COMMENT" ; break ;
    case ONE_LINE_COMMENT : cout << "ONE_LINE_COMMENT" ; break ;
    case BLANK_LINE : cout << "BLANK_LINE" ; break ;
    case ERROR : cout << "ERROR" ; break ;
    default : cout << "UNKNOWN" ; break ;
  }
  cout << endl ;
}

/**
 * Free the memory from the vector of element pointers
 * @param _toDelete: vector to be deleted.
 */
void deleteVectorData(vector<Element*>& _toDelete)
{
  // if not empty, loop through and delete all elements
  for(Element* data : _toDelete) 
  {
    delete data;
  }
  
  _toDelete.clear();
}


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
void removeWhiteSpace( string& str )
{
  // cout << "Trimming |" << str << "|" << endl ;  // for debugging
  while ( str[0] == ' ' || str[0] == '\t' ) {
    str.erase( str.begin() ) ;  // must use an iterator
  }
  while ( str[str.length()-1] == ' ' || str[str.length()-1] == '\t' ) {
    str.erase( str.end()-1 ) ;  // must use an iterator
  }
}