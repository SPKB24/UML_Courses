/* 
 * File:   main.cpp
 * Author: Jesse Heines, heines@cs.uml.edu
 *
 * Created on November 23, 2015, 10:23 AM
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

// The following include directives are all needed as part of xerces api
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/dom/DOMTreeWalker.hpp>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <map>

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"

// The following include directives are for general use
#include <iostream>  // for cout and friends
#include <sstream>   // for string streams
#include <string>    // for the STL string class
#include <regex>     // for regular expressions

// Helpful code utilities written by Jesse M. Heines
#include "jmhUtilities.h"

using namespace std;
XERCES_CPP_NAMESPACE_USE

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  transcoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr 
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------

  XStr(const char* const toTranscode) {
    // Call the private transcoding method
    fUnicodeForm = XMLString::transcode(toTranscode);
  }

  ~XStr() {
    XMLString::release(&fUnicodeForm);
  }


  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------

  const XMLCh* unicodeForm() const {
    return fUnicodeForm;
  }

private:
  // -----------------------------------------------------------------------
  //  Private data members
  //
  //  fUnicodeForm
  //      This is the Unicode XMLCh format of the string.
  // -----------------------------------------------------------------------
  XMLCh* fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()
#define TRIM(str) jmhUtilities::trim(str)

static char* goutputfile = 0;
static char* gXPathExpression = 0;

// options for DOMLSSerializer's features
static XMLCh* gOutputEncoding = 0;

static bool gSplitCdataSections = true;
static bool gDiscardDefaultContent = true;
static bool gUseFilter = false;
static bool gFormatPrettyPrint = true;
static bool gWriteBOM = false;

// forward references
DOMDocument* setRootElement();
void ParseCommandString(string strUserEntry, DOMDocument* doc);
void ProcessAddCommand(string strUserEntry, DOMDocument* doc);
void ProcessAddElementCommand(string strUserEntry, DOMDocument* doc);
void ProcessAddAttributeCommand(string strUserEntry, DOMDocument* doc);
void PrintDOM(DOMDocument* doc);
bool addChildToParent(DOMDocument* doc, string parentName, string childName);
bool addAttrToElement(DOMDocument* doc, string elementName, string attrName, string attrValue);
DOMNode* checkElementExistence(DOMDocument* dox, string elemName);
void showGeneralHelp();


/**
 * The standard C++ main function.
 * @param argc number of command line arguments
 * @param argv array of command line arguments
 * @return 
 */
int main(int argc, char** argv) {

  // display program title
  cout << "=============================" << endl;
  cout << "Assignment No. 7 Starter Code" << endl;
  cout << "=============================" << endl;
  cout << endl;

  // Initialize the XML4C2 system.
  try { 
    XMLPlatformUtils::Initialize(); 
  }
  catch (const XMLException& toCatch) {
    char *pMsg = XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
            << "  Exception message:"
            << pMsg;
    XMLString::release(&pMsg);
    return 1;
  }
  
  DOMDocument* doc = setRootElement();
  
  //  // prompt the user to enter a command string
  //  // version 1 without using a regular expression
  //  while ( ! jmhUtilities::caseInsCompare( jmhUtilities::trim( strUserEntry ), "quit" ) ) {
  //    cout << "\nYour command: " ;
  //    getline( cin, strUserEntry ) ;
  //  }
  
  // string entered by the user in response to the command prompt
  string strUserEntry = "";
  
  // Show general commands to help with first time use
  cout << endl << "Welcome! Please take a look at the accepted commands." << endl;
  showGeneralHelp();
  
  // prompt the user to enter a command string
  // version 2 using a regular expression
  regex reQuit("\\s*quit\\s*", regex::icase);
  
  while (!regex_match(strUserEntry, reQuit)) {
    cout << "\nYour command: ";
    getline(cin, strUserEntry);

    
    // if the user didn't enter 'quit', go parse the command string
    if (!regex_match(strUserEntry, reQuit)) {
      ParseCommandString(strUserEntry, doc);
    }
  }

  return EXIT_SUCCESS;
}

DOMDocument* setRootElement()
{
  DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));
  
  // Get user input to create root element
  cout << "What would you like to call your root element?: ";
  string userRootName = "";
  
  // Allow any alphabetical letter with any case, but limited to one word
  regex rootName("\\s*([a-z]*|[A-Z]*)+\\s*");
  getline(cin, userRootName);
  
  // while user in inputting invalid statements, keep asking them to fix it
  while (!regex_match(userRootName, rootName) || userRootName == ""){
    cout << "ERROR: You have entered an invalid root name. Please enter 1 word as a root name." << endl;
    cout << "\tex. 'root'" << endl << endl;
    cout << "What would you like to call your root element?: ";
    getline(cin, userRootName);
  }
  
  // trim string of any white space characters
  userRootName = TRIM(userRootName);
  
  cout << "You have successfully set '" << userRootName << "' as your root name!" << endl; 
  
  // Once recieved valid input, create root and add it to DOMDocument
  DOMDocument* doc = impl->createDocument(
    0, // root element namespace URI.
    X(userRootName.c_str()), // root element name
    0); // document type object (DTD).
  
  return doc;
}

/**
 * Check for a valid basic command.
 * @param strUserEntry command string entered by the user
 */
void ParseCommandString(string strUserEntry, DOMDocument* doc) {
  // regular expressions for basic commands
  regex reBasicAddCommand("\\s*add.*", regex::icase);
  regex reBasicPrintCommand("\\s*print.*", regex::icase);
  regex reBasicHelpCommand("\\s*help.*", regex::icase);

  // test for each basic command in turn
  if (regex_match(strUserEntry, reBasicAddCommand)) {
    ProcessAddCommand(strUserEntry, doc);
  } else if (regex_match(strUserEntry, reBasicPrintCommand)) {
    //ProcessPrintCommand(strUserEntry, doc);
    PrintDOM(doc);
  } else if (regex_match(strUserEntry, reBasicHelpCommand)) {
    showGeneralHelp();
  } else {
    cout << "  Invalid command." << endl;
    showGeneralHelp();
  }
}

/**
 * Handle an add command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddCommand(string strUserEntry, DOMDocument* doc) {
  
  // regular expressions for the second parameter in the add command
  regex reAddElementCommand("\\s*add\\s+element.*", regex::icase);
  regex reAddAttributeCommand("\\s*add\\s+attribute.*", regex::icase);

  // test for each possible second parameter in turn
  if (regex_match(strUserEntry, reAddElementCommand)) {
    ProcessAddElementCommand(strUserEntry, doc);
  } else if (regex_match(strUserEntry, reAddAttributeCommand)) {
    ProcessAddAttributeCommand(strUserEntry, doc);
  } else {
    cout << "  Invalid add command: 2nd parameter must be 'element' or 'attribute'." << endl;
  }
}

/**
 * Handle an add element command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddElementCommand(string strUserEntry, DOMDocument* doc) {
  
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group  (name of parent element)
  // what[2] contains the second matched group (name of new element)
  // what[3] etc.

  // regular expression to pick out the name of the parent to which the new element is to be added 
  //    and the name of the new element itself
  regex reAddElementCmd("^\\s*add\\s*element\\s(\\w+)\\s(\\w+)(.*)$", regex::icase);

  // note that the following variant of the regex_match command requires a C string, not an STL string
  if (regex_match(strUserEntry.c_str(), what, reAddElementCmd))
  {
    // This function will add what[2] as a child of what[1]
    addChildToParent(doc, what[1], what[2]);
  } 
  else
  {
    cout << "  Invalid 'add element' command." << endl;
    cout << "    'add element' must be followed by two more parameters:" << endl;
    cout << "      (1) the name of the parent to which the new element is to be added, and" << endl;
    cout << "      (2) the name of the new element itself." << endl;
  }
}

/**
 * Handle an add attribute command entered by the user
 * @param strUserEntry command string entered by the user
 */
void ProcessAddAttributeCommand(string strUserEntry, DOMDocument* doc) {
  
  // the what variable is actually an array that will be populated by the regex_match function
  //    when matched groups are found
  cmatch what;
  // what[0] contains the entire matched string
  // what[1] contains the first matched group  (name of element to add to)
  // what[2] contains the second matched group (name of new attribute to be added)
  // what[3] etc.                              (value of new attribute to be added)

  // regular expression to pick out the name of the element to which the new attribute is to be added,
  //    the name of the new attribute, and the value of that attribute
  regex reAddAttributeCmd("^\\s*add\\s+attribute\\s(\\w+)\\s(\\w+)\\s(\\w+)(.*)$", regex::icase);

  // note that the following variant of the regex_match command requires a C string, not an STL string
  if (regex_match(strUserEntry.c_str(), what, reAddAttributeCmd)) 
  {    
    // This function will add what[2] and what[3] as an attribute of element what[1]
    addAttrToElement(doc, what[1], what[2], what[3]);
    
  } else {
    cout << "  Invalid 'add attribute' command." << endl;
    cout << "    'add attribute' must be followed by three more parameters:" << endl;
    cout << "      (1) the name of the element to which the new attribute to be added," << endl;
    cout << "      (2) the name of the new attribute to be added, and " << endl;
    cout << "      (3) the value of the new attribute to be added." << endl;
  }
}

void PrintDOM(DOMDocument* doc)
{
  // retval was used in a previous version of this function that returned an int
  // it is no longer used, but has been kept for future use
  // in this case, however, the second statement below is required to avoid a compiler warning
  int retval = 0; // function return value
  retval = retval; // to avoid warning that retval is not used

  // If the parse was successful, output the document data from the DOM tree
  // if (!errorsOccured && !errReporter->getSawErrors())
  // {
  DOMPrintFilter *myFilter = 0;

  try 
  {
    // get a serializer, an instance of DOMLSSerializer
    XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSSerializer *theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer();
    DOMLSOutput *theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput();

    // set user specified output encoding
    theOutputDesc->setEncoding(gOutputEncoding);

    // plug in user's own filter
    if (gUseFilter) 
    {
      // even we say to show attribute, but the DOMLSSerializer
      // will not show attribute nodes to the filter as
      // the specs explicitly says that DOMLSSerializer shall
      // NOT show attributes to DOMLSSerializerFilter.
      //
      // so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
      // same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
      //
      myFilter = new DOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT |
              DOMNodeFilter::SHOW_ATTRIBUTE |
              DOMNodeFilter::SHOW_DOCUMENT_TYPE);
      theSerializer->setFilter(myFilter);
    }

    // plug in user's own error handler
    DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
    DOMConfiguration* serializerConfig = theSerializer->getDomConfig();
    serializerConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

    // set feature if the serializer supports the feature/mode
    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
      serializerConfig->setParameter(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
      serializerConfig->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
      serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);

    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTBOM, gWriteBOM))
      serializerConfig->setParameter(XMLUni::fgDOMWRTBOM, gWriteBOM);

    //
    // Plug in a format target to receive the resultant
    // XML stream from the serializer.
    //
    // StdOutFormatTarget prints the resultant XML stream
    // to stdout once it receives any thing from the serializer.
    //
    XMLFormatTarget *myFormTarget;
    if (goutputfile) 
    {
      myFormTarget = new LocalFileFormatTarget(goutputfile);
    }
    else 
    {
      myFormTarget = new StdOutFormatTarget();
    }
    theOutputDesc->setByteStream(myFormTarget);

    // get the DOM representation
    // DOMDocument *doc = parser->getDocument();

    //
    // do the serialization through DOMLSSerializer::write();
    //
    if (gXPathExpression != NULL)
    {
      XMLCh* xpathStr = XMLString::transcode(gXPathExpression);
      DOMElement* root = doc->getDocumentElement();
      try
      {
        DOMXPathNSResolver* resolver = doc->createNSResolver(root);
        DOMXPathResult* result = doc->evaluate(
                xpathStr,
                root,
                resolver,
                DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,
                NULL);

        XMLSize_t nLength = result->getSnapshotLength();
        for (XMLSize_t i = 0; i < nLength; i++) {
          result->snapshotItem(i);
          theSerializer->write(result->getNodeValue(), theOutputDesc);
        }

        result->release();
        resolver->release();
      } 
      catch (const DOMXPathException& e)
      {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
        retval = 4;
      }
      catch (const DOMException& e)
      {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
        retval = 4;
      }
      XMLString::release(&xpathStr);
    }
    else 
    {
      theSerializer->write(doc, theOutputDesc);
    }

    theOutputDesc->release();
    theSerializer->release();

    //
    // Filter, formatTarget and error handler
    // are NOT owned by the serializer.
    //
    delete myFormTarget;
    delete myErrorHandler;

    if (gUseFilter)
      delete myFilter;

  } 
  catch (const OutOfMemoryException&)
  {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    retval = 5;
  } 
  catch (XMLException& e) 
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during creation of output transcoder. Msg is:"
            << XERCES_STD_QUALIFIER endl
            << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
    retval = 4;
  }
  // }
}

bool addChildToParent(DOMDocument* doc, string parentName, string childName)
{
  // Get node that has same name as parentName
  DOMNode* parentNode = checkElementExistence(doc, parentName);
  
  // Make sure parent node actually exists.
  if (parentNode == NULL)
  {
    cout << "Sorry. The parent element '" << parentName << "' hasn't been created yet." << endl;
    return false;
  }
 
  // If element with same name as childName exists, DO NOT ADD CHILD TO PARENT
  // No ambiguous element names allowed!
  if (!checkElementExistence(doc, childName))
  {
    // if child node hasn't been taken yet, create it and add as child to parentNode
    cout << "Adding '" << childName << "' as a child of '" << parentName << "'!" << endl;
    
    // Add child to parentNode
    DOMElement* childElement = doc->createElement(X(childName.c_str()));
    parentNode->appendChild(childElement);
  }
  else
  {
    // If child node has already been created, inform user
    cout << "Sorry. The child name '" << childName << "' already exists." << endl;
    return false;
  }
  
  return true;
}

bool addAttrToElement(DOMDocument* doc, string elementName, string attrName, string attrValue)
{
  // Get node that has same name as parentName
  DOMElement* elementNode = dynamic_cast<DOMElement*>(checkElementExistence(doc, elementName));
  
  // Make sure parent node actually exists.
  if (elementNode == NULL)
  {
    cout << "Sorry. The parent element '" << elementName << "' hasn't been created yet." << endl;
    return false;
  }
  
  // NOW MAKE SURE THAT ATTRIBUTE NAME DOSEN'T EXISTS FOR THAT NODE ONLY
  DOMNamedNodeMap *map = elementNode->getAttributes();
  
  if (map != NULL && map->getLength() != 0) {
    for (unsigned int k = 0; k < map->getLength(); k++) {
      if (XMLString::equals(XMLString::transcode(map->item(k)->getNodeName()), attrName.c_str())) {
        
        // At this point we know that an attribute exists...
        cout << "Sorry. An attribute with name '" << attrName << "' already exists." << endl;
        return false;
      }
    }
  }
 
  // if we get past this, we are all set to add.
  elementNode->setAttribute(X(attrName.c_str()), X(attrValue.c_str()));
  cout << "Added (" << attrName << "=\"" << attrValue << "\") as an attribute to '" << elementName << "'" << endl;
  return true;
}

DOMNode* checkElementExistence(DOMDocument* doc, string elemName)
{  
  // Get tree root element
  DOMElement* elemRoot = doc->getDocumentElement();
  
  // create tree walker starting at elemRoot
  DOMTreeWalker* walker = doc->createTreeWalker(elemRoot, DOMNodeFilter::SHOW_ALL, NULL, true);
  
  // walk through each node in the tree
  for (DOMNode* current = walker->getCurrentNode(); current != 0; current = walker->nextNode())
  {
    // compare name of current node with elemName
    if (XMLString::equals(XMLString::transcode(current->getNodeName()), elemName.c_str()))
      return current;
  }
  
  return NULL;
}

void showGeneralHelp()
{
  cout << endl << "  Commands are:" << endl;
  cout << "  - add element <parent_name> <element_name>" << endl;
  cout << "  - add attribute <parent_name> <attribute_name> <attribute_value>" << endl;
  cout << "  - print" << endl;
  cout << "  - help (this command)" << endl;
  cout << "  - quit" << endl;
}