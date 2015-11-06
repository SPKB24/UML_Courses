/* File:   MusicLibraryReader.cpp
 * Author: Jesse M. Heines, heines@cs.uml.edu
 * Editor: Sohit Pal, sohitpal@outlook.com
 *
 * created by JMH on Feburary 13, 2012 at 12:40 PM
 * updated by JMH on September 30, 2015 at 4:04 PM
 * updated by JMH on October 21, 2015 at 9:22 PM to add attribute handling
 * updated by Sohit Pal on November 5. 2015 at 11:11 PM to add JSON Output function
 * updated by Sohit Pal on November 6, 2015 at 10:05 AM to add additional documentation
 */



#include "MusicLibraryReader.h"
#include "Element.h"

using namespace std ;


/**
 * the various parser states
 */
enum ParserState { UNKNOWN, STARTING_DOCUMENT, DIRECTIVE, 
    ELEMENT_OPENING_TAG, ELEMENT_CONTENT, ELEMENT_NAME_AND_CONTENT, ELEMENT_CLOSING_TAG,
    STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
    ERROR } ;
    

/**
 * Vector of names of elements as we descend into the XML hierarchy.
 */
vector<string> vecElementNames ;


/**
 * The root element of the XML document.
 */
Element* root ;


/**
 * The stack of elements as we descend into the XML hierarchy.
 */
vector<Element*> vecElementStack ;


/**
 * Display the contents of a vector of strings.
 * @param vec vector to display
 */
void ShowStack( vector<string> vec ) {
  cout << "*** Vector contains: " ;
  ostream_iterator<string> output( cout, " " ) ;  // see Deitel CPPHTP/8e p. 868 line 16
  copy( vec.begin(), vec.end(), output ) ;        // see Deitel CPPHTP/8e p. 869 line 56
  cout << endl ;
}


/**
 * Display the contents of the Element stack.
 */
void ShowElementStack() {
  cout << "*** Element stack contains: " ;
  for ( vector<Element*>::iterator it = vecElementStack.begin() ; 
        it != vecElementStack.end() ; it++ ) {
    cout << (*it)->getStrTagName() << " " ;
  }
  cout << endl ;
}


/**
 * Trim leading and trailing white space (spaces and tabs) from the string
 *    passed as an argument and return the trimmed string.
 * @param str string to trim
 * @return trimmed string
 */
string trim( string& str ) {
  // cout << "Trimming |" << str << "|" << endl ;
  while ( str[0] == ' ' || str[0] == '\t' ) {
    str.erase( str.begin() ) ;  // must use an iterator
  } 
  while ( str[str.length()-1] == ' ' || str[str.length()-1] == '\t' ) {
    str.erase( str.end()-1 ) ;  // must use an iterator
  } 
  return str ;
}


/**
 * This function is used during debugging to display the parser state.
 * @param ps the parser state
 */
void ShowState( ParserState ps ) {
  cout << "ParserState = " ;
  switch ( ps ) {
    case UNKNOWN : cout << "UNKNOWN" ; break ;
    case STARTING_DOCUMENT : cout << "STARTING_DOCUMENT" ; break ;
    case DIRECTIVE : cout << "DIRECTIVE" ; break ;
    case ELEMENT_OPENING_TAG : cout << "ELEMENT_OPENING_TAG" ; break ;
    case ELEMENT_CONTENT : cout << "ELEMENT_CONTENT" ; break ; 
    case ELEMENT_NAME_AND_CONTENT : cout << "ELEMENT_NAME_AND_CONTENT" ; break ;
    case ELEMENT_CLOSING_TAG : cout << "ELEMENT_CLOSING_TAG" ; break ;
    case STARTING_COMMENT : cout << "STARTING_COMMENT" ; break ;
    case IN_COMMENT : cout << "IN_COMMENT" ; break ;
    case ENDING_COMMENT : cout << "ENDING_COMMENT" ; break ;
    case ONE_LINE_COMMENT : cout << "ONE_LINE_COMMENT" ; break ;
    case ERROR : cout << "ERROR" ; break ;
    default : cout << "DEFAULT" ; break ;
  }
  cout << endl ;
}


/**
 * This function is used during debugging to display get parser state as a string.
 * @param ps the parser state
 */
string GetParserState( ParserState ps ) {
  switch ( ps ) {
    case UNKNOWN : return "UNKNOWN" ; break ;
    case STARTING_DOCUMENT : return "STARTING_DOCUMENT" ; break ;
    case DIRECTIVE : return "DIRECTIVE" ; break ;
    case ELEMENT_OPENING_TAG : return "ELEMENT_OPENING_TAG" ; break ;
    case ELEMENT_CONTENT : return "ELEMENT_CONTENT" ; break ; 
    case ELEMENT_NAME_AND_CONTENT : return "ELEMENT_NAME_AND_CONTENT" ; break ;
    case ELEMENT_CLOSING_TAG : return "ELEMENT_CLOSING_TAG" ; break ;
    case STARTING_COMMENT : return "STARTING_COMMENT" ; break ;
    case IN_COMMENT : return "IN_COMMENT" ; break ;
    case ENDING_COMMENT : return "ENDING_COMMENT" ; break ;
    case ONE_LINE_COMMENT : return "ONE_LINE_COMMENT" ; break ;
    case ERROR : return "ERROR" ; break ;
    default : return "DEFAULT" ; break ;
  }
}


/**
 * This function parses a line read from the XML file and returns the appropriate
 *    data for that line.<br/>
 * N.B. Assumptions:<br/>
 * <ol>
 *   <li>The XML file being processed must be well-formed.</li>
 *   <li>There is at most one complete element per line.</li>
 *   <li>All element opening tags start on new lines.</li>
 *   <li>The element closing tag, if present, is the last thing on a line.</li>
 *   <li>If there is no element closing tag on the same line as an element</li>
 *            opening tag, there is no content on that line.</li>
 *   <li>Attributes and their values are ignored.</li>
 * </ol>
 * @param strLine        line read from XML file
 * @param strElementName name of element found
 * @param strContent     content of an element
 * @param nStartPos      position at which to start search
 * @param nEndPos        position at which search ended
 * @param currentState   state of parser on entry into this function
 * @return state of parser on exit from this function
 */
ParserState GetXMLData( string strLine, string& strElementName, string& strContent, 
    int nStartPos, int& nEndPos, ParserState currentState ) {
  strContent = "" ;       // content of an element
  strElementName = "" ;   // name of element found
  nStartPos =             // position of an opening < character
      strLine.find( "<", nStartPos ) ;
  nEndPos =               // position of the corresponding closing > character
      strLine.find( ">", nStartPos ) ;    
  
//  // for debugging
//  if ( nStartPos != string::npos ) {
//    cout << "|" << strLine.substr( nStartPos, 4 ) << "|" << endl ;
//  }
  
  // closing > not found (string::npos is returned if the search string is not found)
  if ( nEndPos == string::npos ) {
    if ( currentState == STARTING_COMMENT || currentState == IN_COMMENT ) {
      strContent = strLine ;
      return IN_COMMENT ;
    } else if ( strLine.substr( nStartPos, 4 ).compare( "<!--" ) == 0 ) {
      return STARTING_COMMENT ;
    } else {
      strContent = strLine ;
      trim( strContent ) ;
      return UNKNOWN ;
    }
  
  // opening < not found
  } else if ( nStartPos == string::npos && nEndPos > 1 && 
              strLine.substr( nEndPos-2, 3 ).compare( "-->" ) == 0 ) {
    return ENDING_COMMENT ;
    
  // ? found after opening <, indicating a directive
  } else if ( strLine[nStartPos+1] == '?' ) {
    strContent = strLine.substr( nStartPos+2, ( nEndPos - nStartPos - 3 ) ) ;
    return DIRECTIVE ;

  // !-- found after opening <, indicating a comment
  } else if ( strLine.substr( nStartPos, 4 ).compare( "<!--" ) == 0 ) {
    strContent = strLine.substr( nStartPos+4, nEndPos - nStartPos - 6 ) ;
    trim( strContent ) ;
    return ONE_LINE_COMMENT ;

  // found element closing tag
  } else if ( strLine[nStartPos+1] == '/' ) {
    strElementName = strLine.substr( nStartPos+2, ( nEndPos - nStartPos - 2 ) ) ;
    
    // element name should match last entry pushed onto stack
    if ( strElementName.compare( vecElementNames.back() ) == 0 ) {
      vecElementNames.pop_back() ;
      return ELEMENT_CLOSING_TAG ;
    } else {
      strContent = "XML file is not well-formed.  Read element closing tag " + 
          strElementName + ", but last element pushed onto stack was " + 
          vecElementNames.back() + "." ;
      return ERROR ;
    }

  // found element opening tag
  } else {
    strElementName = strLine.substr( nStartPos+1, ( nEndPos - nStartPos - 1 ) ) ;
    
    // ignore any attributes found
    int posSpace = strElementName.find( " ", 0 ) ;
    if ( posSpace != string::npos ) {
      strElementName = strElementName.substr( 0, posSpace ) ;
    }
  
    // search for closing element tag on the same line
    int posClosingTag = strLine.find( "</" + strElementName + ">", nEndPos + 1 ) ;
    
    // closing tag found
    if ( posClosingTag != string::npos ) {
      strContent = strLine.substr( nEndPos + 1, posClosingTag - nEndPos - 1 ) ;
      trim( strContent ) ;
      return ELEMENT_NAME_AND_CONTENT ;
    
    // search for self-closing tag
    } else {
      posClosingTag = strLine.find( "/>", nStartPos + 1 ) ;
      
      if ( posClosingTag != string::npos ) {
        strContent = "" ;
        return ELEMENT_NAME_AND_CONTENT ;
    
      // closing tag not found
      } else {
        // push element name onto vector stack
        vecElementNames.push_back( strElementName ) ;
        return ELEMENT_OPENING_TAG ;
      }
    } 
  }
  
  // the line could not be interpreted
  return UNKNOWN ;
}


/**
 * Look for attributes on the current line and add them to the current element if found.
 * @param strLine the line to parse
 * @param elem    the element to which any found attributes will be added
 */
void ParseAttributes( string strLine, Element* elem ) {
  int nStartPos ;   // position of an opening < character
  int nEndPos ;     // position of the corresponding closing > character
  int nSpacePos ;   // position of a space in the tag that delimits attributes
  int nAnglePos ;   // position of a closing angle bracket in the tag that ends an attribute value
  int nQuotePos ;   // position of a quote in the tag that ends an attribute value
  int nEqualsPos ;  // position of an = sign
  string key ;      // key of a found attribute (the part before the = sign)
  string value ;    // value of a found attribute (the part after the = sign)

  // delineate the opening tag (remember that attributes can only be on opening tags)
  nStartPos = strLine.find( "<", nStartPos ) ;
  nEndPos = strLine.find( ">", nStartPos ) ;
  strLine = strLine.substr( nStartPos+1, nEndPos-nStartPos-1 ) ;
  trim( strLine ) ;   // always trim the string to account for double spaces

  // shorten strLine to remove the tag name
  nSpacePos = strLine.find( " " ) ;
  if ( nSpacePos != string::npos ) {
    strLine = strLine.substr( nSpacePos+1, strLine.length() ) ;
    trim( strLine ) ;   // always trim the string to account for double spaces
  }

  // extract all attributes as key/value pairs and add them to the element's map
  while ( strLine.find( "=" ) != string::npos ) {
    // find the = sign and extract the attribute key
    nEqualsPos = strLine.find( "=" ) ;
    key = strLine.substr( 0, nEqualsPos ) ;
    trim( key ) ;       // always trim the string to account for double spaces
    // shorten strLine to remove the key we just extracted
    strLine = strLine.substr( nEqualsPos+1, strLine.length() ) ;
    trim( strLine ) ;   // always trim the string to account for double spaces
    
    // extract the attribute value, which is terminated either by a space or a >
    nSpacePos = strLine.find( " " ) ;
    if ( nSpacePos != string::npos )
    {        
      value = strLine.substr( 0, nSpacePos ) ;
      // shorten strLine to remove the key we just extracted
      strLine = strLine.substr( nSpacePos+1, strLine.length() ) ;
      trim( strLine ) ;   // always trim the string to account for double spaces
    } 
    else 
    {                                 
      nAnglePos = strLine.find( ">" ) ;
      value = strLine.substr( 0, nAnglePos ) ;
    }
    trim( value ) ;   // always trim the string to account for double spaces
    // remove the enclosing double quotes
    value = value.substr( 1, value.length()-2 ) ;
    
    // Add the attribute as a key/value pair to the element's map
    elem->addAttribute( key, value ) ;
    // cout << "key = " << key << " | value = " << value << endl ;
  }
}


/**
 * Read the file passed as a parameter and process it by lines.  This is a
 *    rudimentary way of parsing the file.<br/>
 * This function is the most advanced version developed so far.  It is not the
 *    version required for Assignment No. 1, so it is not used in this project.
 *    It is kept here solely for reference.
 * @param strFileName name of file to read
 * @return status code
 */
int GetXMLData( string strFileName ) {
  // convert the string type to a standard C string for use in the infile function
  char* pcharFileName = new char [strFileName.size() + 1] ;
  strcpy( pcharFileName, strFileName.c_str() ) ;
  
  // open the input file
  ifstream infile( pcharFileName ) ;

  char pLine[256] ;         // line read from the file, note that a char* (not a 
                            //    string) is required by the getline method
  string strLine ;          // string version of the line read (pLine) so that
                            //    we can work with the data as an STL type
  string strContent ;       // name of element specified on line
  string strElementName ;   // name of element specified on line
  int nParsePos ;           // position at which parsing ended
  ParserState currentState = STARTING_DOCUMENT ;
                            // parser state before reading next line
  ParserState newState ;    // type of element read by the parser
  int nLine = 0 ;           // line counter
  Element* ptrElemCurrent = NULL;
                            // pointer to the current element being processed
  
  // process file
  while ( infile.getline( pLine, 256 ) != NULL ) {
    strLine = pLine ;   // convert char* to string
    cout << "\n" << ++nLine << ": " << trim( strLine ) << endl 
         << "*** Current Parser State = " << GetParserState( currentState ) << endl
         << "*** " << flush ;

    newState = GetXMLData( strLine, strElementName, strContent, 0, nParsePos, currentState ) ;
    switch ( newState ) {
      
      case DIRECTIVE :
        cout << "Found Directive = " << strContent << endl ; break ;
      
      case STARTING_COMMENT :
        cout << "Found Starting Comment" << endl ; break ;
      
      case IN_COMMENT :
        cout << "Found Comment Line" << endl ; break ;
      
      case ENDING_COMMENT :
        cout << "Found Ending Comment" << endl ; break ;
      
      case ONE_LINE_COMMENT :
        cout << "One-Line Comment Text = " << strContent << endl ; break ;
      
      case ELEMENT_OPENING_TAG :
        cout << "Element Opened = " << strElementName << endl ; 
        // ShowStack( vecElementNames ) ;
        if ( ptrElemCurrent == NULL ) {
          root = new Element( strElementName, nLine ) ;
          ptrElemCurrent = root ;
          // we are opening but not closing an element, so we need to push it on the stack
          vecElementStack.push_back( root ) ;
          // find the attributes on the line and add them to the root element
          ParseAttributes( strLine, root ) ;
        } else {
          Element* ptrElemNew = new Element( strElementName, nLine, strContent ) ;
          ptrElemCurrent->addChild( ptrElemNew ) ;
          ptrElemCurrent = ptrElemNew ;
          // we are opening but not closing an element, so we need to push it on the stack
          vecElementStack.push_back( ptrElemNew ) ;
          // find the attributes on the line and add them to the new element
          ParseAttributes( strLine, ptrElemNew ) ;
        }
        ShowElementStack() ;
        break ;
      
      case ELEMENT_NAME_AND_CONTENT :
        cout << "Element Name = " << strElementName << endl ; 
        cout << "*** Element Content = " << ( strContent.length() == 0 ? "{empty}" : strContent ) << endl ; 
        // if ( currentState == STARTING_DOCUMENT ) {
        if ( ptrElemCurrent == NULL ) {
          root = new Element( strElementName, nLine, strContent ) ;
          ptrElemCurrent = root ;
          // find the attributes on the line and add them to the root element
          ParseAttributes( strLine, ptrElemCurrent ) ;
        } else {
          Element* ptrElemNew = new Element( strElementName, nLine, strContent ) ;
          ptrElemCurrent->addChild( ptrElemNew ) ;
          // find the attributes on the line and add them to the new element
          ParseAttributes( strLine, ptrElemNew ) ;
        }
        break ;
      
      case ELEMENT_CLOSING_TAG :
        cout << "Element Closed = " << strElementName << endl ; 
        // ShowStack( vecElementNames ) ;
        // remove the last element on the stack
        vecElementStack.pop_back() ;
        ShowElementStack() ;
        // reset the current element to be the last one on the stack
        // note that end() returns an iterator referring to the *past-the-end* element 
        //    in the vector, so we have to subtract 1 from this result
        ptrElemCurrent = *(vecElementStack.end()-1) ;
        break ;
      
      case ERROR :
        cout << "ERROR: " << strContent << endl ;
        return EXIT_FAILURE ;

      default :
        cout << "Unknown Line Read = " << strContent << endl ; break ;
    }
    currentState = newState ;
    
    cout << "*** New Parser State = " << GetParserState( newState ) << endl ;

        // if ( strElementName.compare( "release-list" ) == 0 ) break ;
  }
  
  // close the input file
  infile.close() ;
  delete[] pcharFileName ;

  // return the status code
  return EXIT_SUCCESS ;
}

/**
 * This function shows the data for all the children of a given Element.  It is 
 * called recursively when a child Element itself has children.
 * @param elem the current Element to process
 */
void ShowChildData( Element& elem, int level )
{
  //  cout << "\nelem.getStrTagName = "  << elem.getStrTagName() << endl ;
  //  cout << "elem.getVecChildren().size() = "  << elem.getVecChildren().size() << endl ;
  for ( int k = 0 ; k < elem.getVecChildren().size() ; k++ ) 
  {
    Element* ptrChildElement = elem.getVecChildren().at( k ) ;
    cout << "\n Child tag name = " << ptrChildElement->getStrTagName() << endl ;
    cout << "   Child line # = " << ptrChildElement->getNLineNo() << endl ;
    cout << "    Child level = " << level << endl ;
    cout << "  Child content = " << 
        ( ptrChildElement->getStrContent().length() == 0 ? 
            "{empty}" : ptrChildElement->getStrContent() ) << endl ;
    cout << "Direct children = " << ptrChildElement->getVecChildren().size() << endl ;
    cout << "     Attributes = " << ptrChildElement->getMapAttributes().size() << endl ;
    
    // display attributes
    // http://www.cprogramming.com/tutorial/stl/stlmap.html
    // note that you must only call elem.getMapAttributes() once, or you get two 
    //    *different* iterators, and iterator it will never be equal to the .end()
    map<string,string> mapAttributes = ptrChildElement->getMapAttributes() ;
    if ( ! mapAttributes.empty() ) 
    {
      map<string,string>::iterator it = mapAttributes.begin() ;
      for ( int k = 1 ; it != mapAttributes.end() ; k++, it++ ) 
      {
        cout << "         Attribute #" << k << ": Key = " << it->first 
             << " and Value = " << it->second << endl ;
      }
    }
    
    // recurse through children
    if ( ptrChildElement->getVecChildren().size() != 0 ) 
    {
      ShowChildData( *ptrChildElement, level + 1 ) ;
    }
  }
}

/**
 * Function to easily get string of spaces to format JSON file
 * @param _treeLevel the level of the element in the tree to dictate number of spaces needed
 * @return string of correct number of spaces
 */
string getSpaces( int _treeLevel )
{
  string spaces = "";
  
  for ( int i = 0 ; i < _treeLevel - 1 ; i++ )
  {
    spaces += "  ";
  }
  
  return spaces;
}

/**
 * This will convert a tree of elements into a JSON file and output to 
 *  a file path.
 * @param elem      the root of the tree
 * @param treeLevel the level of the current element
 * @param outFile   the file to output the JSON file to
 */
void XML_TO_JSON( Element* elem, int treeLevel, ofstream& outFile )
{
  // Print open bracket for root element
  if (treeLevel == gRootLevel) {
    outFile << "{" << endl;
  }
  
  // vecChildren will hold the children of the current element
  vector<Element*> vecChildren = elem->getVecChildren();
  
  // numChildren will hold the number of children of the current element 
  int numChildren = vecChildren.size();
  
  // mapAttributes will hold all of the attributes of the current element
  map<string,string> mapAttributes;
  
  // Begin looping over all direct children
  for ( int k = 0 ; k < numChildren; k++ )
  {
    // ptrChildElement will point to each child element each loop
    Element* ptrChildElement = vecChildren.at( k );

    // Print out name and tag name of element
    outFile << getSpaces( treeLevel + 1 ) << "\"" << ptrChildElement->getStrTagName() << "\"" << " : ";
  
    // If element doesn't have content
    //    print open bracket for its attributes
    // else
    //    print out its content
    if(ptrChildElement->getStrContent().length() == 0) {
      outFile << "{";
    }
    else {
      outFile << "\"" <<  ptrChildElement->getStrContent() << "\"";
      
      // if not last child, print comma at the end
      if (k != numChildren - 1) {
        outFile << ",";
      }
    }
    
    outFile << endl;
    
    /* DISPLAY ATTRIBUTES */
    mapAttributes = ptrChildElement->getMapAttributes();
    
    if ( !mapAttributes.empty() )
    {
      // map iterator
      map<string,string>::iterator it;
      
      // counter to keep track of current attribute number
      int counter = 0;
      
      // maxCount to keep track of size, and make sure we don't put comma after last element
      int maxCount = mapAttributes.size() - 1;
      
      // For each attribute, print out name and content
      for ( it = mapAttributes.begin(); it != mapAttributes.end() ; it++ , counter++ ) 
      {
        outFile << getSpaces( treeLevel + 2 ) << "\"" << it->first  << "\"" << " : " << "\"" << it->second  << "\""; 
        
        // If not last attribute in map, add comma to the end
        if (counter != maxCount) {
          outFile << "," << endl;
        }
      }
      
      // if ptrChildrenElement does not have children
      //     print out closing bracket
      // else
      //     print out comma at end
      if( ptrChildElement->getVecChildren().size() == 0) {
        outFile << endl << getSpaces( treeLevel + 1 ) << "}," << endl;   
      }
      else {
        outFile << "," << endl;
      }
    }
    
    // Recurse through children of current element
    if ( ptrChildElement->getVecChildren().size() != 0 )
    {
      // Recursive loop
      XML_TO_JSON( ptrChildElement, treeLevel + 1, outFile );
      
      // Print out closing bracket after finished with current element's children
      outFile << getSpaces(treeLevel + 1) << "}";
      
      // if not last child, print comma
      if (k != numChildren - 1)
        outFile << ",";
      
      outFile << endl;
    }
  }
  
  // Print closing bracket for root element
  if (treeLevel == gRootLevel) {
    outFile << "}" << endl;
  }
}


/**
 * This function prints the XML tree as required by Assignment No. 4.  
 * It is called recursively when a child Element itself has children.
 * @param elem the current Element to process
 * @param level the indentation level
 */
void ShowXMLTree( Element& elem, int level ) 
{
  
  // indent appropriately
  for (int k = 0 ; k < level ; k++ ) 
  {
    cout << ". " ;
  }
  
  // display data for the current element
  cout << elem.toString() << endl ;
  
  // display attributes
  // http://www.cprogramming.com/tutorial/stl/stlmap.html
  // note that you must only call elem.getMapAttributes() once, or you get two 
  //    *different* iterators, and iterator it will never be equal to the .end()
//  map<string,string> mapAttributes = elem.getMapAttributes() ;
//  if ( ! mapAttributes.empty() ) 
//  {
//    map<string,string>::iterator it = mapAttributes.begin() ;
//    for ( int k = 1 ; it != mapAttributes.end() ; k++, it++ ) 
//    {
//      cout << setw( 2*level + 4 ) << " " ;
//      cout << "Attribute #" << k << ": Key = " << it->first 
//           << " and Value = " << it->second << endl ;
//    }
//  }
//
//
//   for ( vector<Element*>::iterator it = (elem.getVecChildren()).begin() ; 
//         it != (elem.getVecChildren()).end() ; it++ ) {
//     ShowXMLTree( **it, level + 1 ) ;
//   }
//  
  //// This version works because it calls getVecChildren just once and then 
  //// gets the beginning and ending pointers of the same vector that was 
  //// returned as a result of that single call.
  vector<Element*> vecChildren = elem.getVecChildren() ;
  for ( vector<Element*>::iterator it = vecChildren.begin() ; 
        it != vecChildren.end() ; it++ ) 
  {
    ShowXMLTree( **it, level + 1 ) ;
  }
}

void printFile( string strFileName )
{
  ifstream fileToPrint;
  fileToPrint.open(strFileName);
  
  string line;
  
  while (getline(fileToPrint, line))
    cout << line << endl;
}

/**
 * This is the code for 91.204 Assignment No. 2.  It reads the file passed as a 
 *    parameter, parses each line to build an Element tree, and then displays 
 *    the resultant tree in three formats.  
 * @param strFileName name of file to read
 * @return status code
 */
int ReadMusicLibrary_v2_1( string strFileName , string strOutFile )
{
  bool showJSON = false;
    
  GetXMLData( strFileName ) ;
  
  //if(showJSON)
  //{ 
    // show the raw data in the XML tree
    cout << "\n============================================================\n" << endl ;
    cout << "  Root tag name = " << root->getStrTagName() << endl ;
    cout << "    Root line # = " << root->getNLineNo() << endl ;
    cout << "     Root level = 0" << endl ;
    cout << "   Root content = " << 
        ( root->getStrContent().length() == 0 ? 
            "{empty}" : root->getStrContent() ) << endl ;
    cout << "Direct children = " << root->getVecChildren().size() << endl ;
    cout << "     Attributes = " << root->getMapAttributes().size() << endl ;
    // display attributes
    // http://www.cprogramming.com/tutorial/stl/stlmap.html
    // note that you must only call elem.getMapAttributes() once, or you get two 
    //    *different* iterators, and iterator it will never be equal to the .end()
    map<string,string> mapAttributes = root->getMapAttributes() ;
    if ( ! mapAttributes.empty() )
    {
      map<string,string>::iterator it = mapAttributes.begin() ;
      for ( int k = 1 ; it != mapAttributes.end() ; k++, it++ )
      {
        cout << "         Attribute #" << k << ": Key = " << it->first 
             << " and Value = " << it->second << endl ;
      }
    }
  
  // show the XML tree as required by Assignment No. 2
  cout << "\nTREE OUTPUT ================================================\n" << endl ;
  ShowXMLTree( *root, 0 ) ;
  
  cout << "\nJSON OUTPUT ================================================\n" << endl ;
  ofstream outputFile;
  outputFile.open("outputFile.txt");
  
  XML_TO_JSON( root, 1, outputFile );
  
  outputFile.close();
  printFile("outputFile.txt");
  
  // return the status code
  return EXIT_SUCCESS ;
}
