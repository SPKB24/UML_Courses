
/*
 * File:  CreateDOMDocument_JMH_v01.cpp
 * Jesse M. Heines, UMass Lowell Computer Science, heines@cs.uml.edu
 * Adapted from Xerces C++ API for XML examples CreateDOMDocument and DOMPrint.
 * Modifications copyright (c) 2015 by Jesse M. Heines.  All rights reserved.
 *   May be freely copied or excerpted for educational purposes with credit
 *   to the author.
 * updated by JMH on November 8, 2015 at 10:16 PM
 */


/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: CreateDOMDocument.cpp 676796 2008-07-15 05:04:13Z dbertoni $
 */

/*
 * This sample illustrates how you can create a DOM tree in memory.
 * It then prints the count of elements in the tree.
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
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

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"

#include <xercesc/dom/DOMTreeWalker.hpp>

#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  transcoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr {
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


// ---------------------------------------------------------------------------
//  Local data
//
//  gXmlFile
//      The path to the file to parser. Set via command line.
//
//  gDoNamespaces
//      Indicates whether namespace processing should be done.
//
//  gDoSchema
//      Indicates whether schema processing should be done.
//
//  gSchemaFullChecking
//      Indicates whether full schema constraint checking should be done.
//
//  gDoCreate
//      Indicates whether entity reference nodes needs to be created or not
//      Defaults to false
//
//  gOutputEncoding
//      The encoding we are to output in. If not set on the command line,
//      then it is defaults to the encoding of the input XML file.
//
//  gSplitCdataSections
//      Indicates whether split-cdata-sections is to be enabled or not.
//
//  gDiscardDefaultContent
//      Indicates whether default content is discarded or not.
//
//  gUseFilter
//      Indicates if user wants to plug in the DOMPrintFilter.
//
//  gValScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
// ---------------------------------------------------------------------------
// not used, as reported by -Wall   static char* gXmlFile            = 0;
// not used, as reported by -Wall   static bool  gDoNamespaces       = false;
// not used, as reported by -Wall   static bool  gDoSchema           = false;
// not used, as reported by -Wall   static bool  gSchemaFullChecking = false;
// not used, as reported by -Wall   static bool  gDoCreate           = false;

static char* goutputfile = 0;
static char* gXPathExpression = 0;

// options for DOMLSSerializer's features
static XMLCh* gOutputEncoding = 0;

static bool gSplitCdataSections = true;
static bool gDiscardDefaultContent = true;
static bool gUseFilter = false;
static bool gFormatPrettyPrint = true;
static bool gWriteBOM = false;

void PrintDOM(DOMDocument* doc) {

  // retval was used in a previous version of this function that returned an int
  // it is no longer used, but has been kept for future use
  // in this case, however, the second statement below is required to avoid a compiler warning
  int retval = 0; // function return value
  retval = retval; // to avoid warning that retval is not used

  // If the parse was successful, output the document data from the DOM tree
  // if (!errorsOccured && !errReporter->getSawErrors())
  // {
  DOMPrintFilter *myFilter = 0;

  try {
    // get a serializer, an instance of DOMLSSerializer
    XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSSerializer *theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer();
    DOMLSOutput *theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput();

    // set user specified output encoding
    theOutputDesc->setEncoding(gOutputEncoding);

    // plug in user's own filter
    if (gUseFilter) {
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
    if (goutputfile) {
      myFormTarget = new LocalFileFormatTarget(goutputfile);
    } else {
      myFormTarget = new StdOutFormatTarget();
    }
    theOutputDesc->setByteStream(myFormTarget);

    // get the DOM representation
    // DOMDocument *doc = parser->getDocument();

    //
    // do the serialization through DOMLSSerializer::write();
    //
    if (gXPathExpression != NULL) {
      XMLCh* xpathStr = XMLString::transcode(gXPathExpression);
      DOMElement* root = doc->getDocumentElement();
      try {
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
      } catch (const DOMXPathException& e) {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
        retval = 4;
      } catch (const DOMException& e) {
        XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
                << XERCES_STD_QUALIFIER endl
                << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
        retval = 4;
      }
      XMLString::release(&xpathStr);
    } else {
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

  } catch (const OutOfMemoryException&) {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    retval = 5;
  } catch (XMLException& e) {
    XERCES_STD_QUALIFIER cerr << "An error occurred during creation of output transcoder. Msg is:"
            << XERCES_STD_QUALIFIER endl
            << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
    retval = 4;
  }
  // }
}


// ---------------------------------------------------------------------------
//  main
// ---------------------------------------------------------------------------

int main(int argC, char*[]) {
  // Initialize the XML4C2 system.
  try {
    XMLPlatformUtils::Initialize();
  } catch (const XMLException& toCatch) {
    char *pMsg = XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
            << "  Exception message:"
            << pMsg;
    XMLString::release(&pMsg);
    return 1;
  }

  // Watch for special case help request
  int errorCode = 0;
  if (argC > 1) {
    XERCES_STD_QUALIFIER cout << "\nUsage:\n"
            "    CreateDOMDocument\n\n"
            "This program creates a new DOM document from scratch in memory.\n"
            "It then prints the count of elements in the tree.\n"
            << XERCES_STD_QUALIFIER endl;
    errorCode = 1;
  }
  if (errorCode) {
    XMLPlatformUtils::Terminate();
    return errorCode;
  }

  {
    //  Nest entire test in an inner block.
    //  The tree we create below is the same that the XercesDOMParser would
    //  have created, except that no whitespace text nodes would be created.

    // <company>
    //     <product>Xerces-C</product>
    //     <category idea='great'>XML Parsing Tools</category>
    //     <developedBy>Apache Software Foundation</developedBy>
    // </company>

    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));

    if (impl != NULL) {
      try {
        // current date and time
        // http://stackoverflow.com/questions/997946/c-get-current-time-and-date
        // This code is originally by JMH, simply changed XML File author name 
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        // http://www.cplusplus.com/reference/clibrary/ctime/strftime/
        strftime(buf, sizeof (buf), "Updated by Sohit at %B %d, %Y at %I:%M %p", &tstruct);

        DOMDocument* doc = impl->createDocument(
                0, // root element namespace URI.
                X("Human"), // root element name
                0); // document type object (DTD).

        DOMElement* elemRoot = doc->getDocumentElement();

        DOMComment* comm = doc->createComment(X("Information about a Human - Sohit Pal"));
        elemRoot->appendChild(comm);

        DOMElement* elem = doc->createElement(X("TimeStamp"));
        elemRoot->appendChild(elem);
        elem->setAttribute(X("AttrName"), X("AttrValue"));
        DOMText* text = doc->createTextNode(X(buf));
        elem->appendChild(text);

        ///* Begin listing information about self *///

        /* NAME */
        // create parent
        elem = doc->createElement(X("Name"));
        elemRoot->appendChild(elem);
        elem->setAttribute(X("hasName"), X("true"));
        elem->setAttribute(X("areYouSure"), X("true"));
        elem->setAttribute(X("really"), X("true"));
        // - first name
        DOMElement* elem2 = doc->createElement(X("first"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Sohit"));
        elem2->appendChild(text);
        elem2->setAttribute(X("hasFirstName"), X("true"));
        // - middle name
        elem2 = doc->createElement(X("middle"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("N/A"));
        elem2->appendChild(text);
        elem2->setAttribute(X("hasMiddleName"), X("false"));
        // - last name
        elem2 = doc->createElement(X("last"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Pal"));
        elem2->appendChild(text);
        elem2->setAttribute(X("hasLastName"), X("true"));
        /* END NAME */

        /* AGE */
        elem = doc->createElement(X("Age"));
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("20"));
        elem->appendChild(text);
        elem->setAttribute(X("scale"), X("years"));
        elem->setAttribute(X("is21"), X("false"));
        elem->setAttribute(X("isAlmost21"), X("close"));
        /* END AGE */

        /* GENDER */
        elem = doc->createElement(X("Gender"));
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("male"));
        elem->appendChild(text);
        /* END GENDER */

        /* SSN */
        elem = doc->createElement(X("SocialSecurityNumber"));
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("xxx-xx-xxxx"));
        elem->appendChild(text);
        elem->setAttribute(X("real"), X("false"));
        elem->setAttribute(X("isImportant"), X("true"));
        elem->setAttribute(X("isDigits"), X("Sure"));
        /* END SSN */

        /* BIRTHDATE */
        // create parent
        elem = doc->createElement(X("BirthDate"));
        elemRoot->appendChild(elem);
        // - month
        elem2 = doc->createElement(X("month"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("March"));
        elem2->appendChild(text);
        // - day
        elem2 = doc->createElement(X("day"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("2"));
        elem2->appendChild(text);
        // - month
        elem2 = doc->createElement(X("year"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("1995"));
        elem2->appendChild(text);
        /* END BIRTHDATE */

        /* TOP 3 COLORS */
        // create parent
        elem = doc->createElement(X("TopColors"));
        elemRoot->appendChild(elem);
        // - color 1
        elem2 = doc->createElement(X("Color1"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Blue"));
        elem2->appendChild(text);
        // - color 2
        elem2 = doc->createElement(X("Color2"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Black"));
        elem2->appendChild(text);
        // - color 3
        elem2 = doc->createElement(X("Color2"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Green"));
        elem2->appendChild(text);
        /* END COLORS */

        /* ARTIST - RAP*/
        elem = doc->createElement(X("Artist"));
        elemRoot->appendChild(elem);
        text = doc->createTextNode(X("Tech N9ne"));
        elem->appendChild(text);
        elem->setAttribute(X("genre"), X("rap"));
        /* END ARTIST */

        /* SOCIAL MEDIA */
        // create parent
        elem = doc->createElement(X("Social"));
        elemRoot->appendChild(elem);
        // - child -> Facebook
        elem2 = doc->createElement(X("Facebook"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Link To Facebook HERE"));
        elem2->appendChild(text);
        // - child -> GitHub
        elem2 = doc->createElement(X("GitHub"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Link To GitHub HERE"));
        elem2->appendChild(text);
        // - child -> Twitter
        elem2 = doc->createElement(X("Twitter"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Link To Twitter HERE"));
        elem2->appendChild(text);
        // - child -> Personal
        elem2 = doc->createElement(X("Personal"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("http://www.sohitpal.com"));
        elem2->appendChild(text);
        /* EXIT SOCIAL MEDIA */


        /* SPORTS */
        // create parent
        elem = doc->createElement(X("Sports"));
        elemRoot->appendChild(elem);
        // - child
        elem2 = doc->createElement(X("Basketball"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Los Angeles Lakers"));
        elem2->appendChild(text);
        // - child
        elem2 = doc->createElement(X("Baseball"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("Boston Red Sox"));
        elem2->appendChild(text);
        // - child
        elem2 = doc->createElement(X("Football"));
        elem->appendChild(elem2);
        text = doc->createTextNode(X("New England Patriots"));
        elem2->appendChild(text);
        /* EXIT SPORTS */

        //
        // Now count the number of elements in the above DOM tree.
        //

        const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
        XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
                << " elements.\n" << XERCES_STD_QUALIFIER endl;

        PrintDOM(doc); // added by JMH
        std::cout << "\n------------------------------" << std::endl;

        // JMH: http://www.ibm.com/developerworks/xml/library/x-xercc2/
        // JMH: but note that a DOMTreeWalker* is returned, not a DOMTreeWalker
        // JMH: this was learned by using NetBeans autocomplete

        // JMH: Note that SHOW_ATTRIBUTE is meaningful only when creating an DOMNodeIterator or
        // DOMTreeWalker with an attribute node as its root; in this case, it means that the attribute
        // node will appear in the first position of the iteration or traversal. Since attributes are
        // never children of other nodes, they do not appear when traversing over the document tree.
        //   -- http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNodeFilter.html

        // JMH: See http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNode.html#6237ede96be83ff729807688e4f638c5
        // for table of values of nodeName, nodeValue, and attributes for given node types

        // create a walker to visit all text nodes
        // DOMTreeWalker* walker = doc->createTreeWalker(elemRoot, DOMNodeFilter::SHOW_TEXT, NULL, true) ;
        DOMTreeWalker* walker = doc->createTreeWalker(elemRoot, DOMNodeFilter::SHOW_ALL, NULL, true);

        /** If true, simply means that current DOMNode is a child of an element */
        bool isPartOfGreaterGood = false;

        /** Will hold top level root parent to all nodes */
        DOMNode* rootElement = NULL;

        for (DOMNode* current = walker->nextNode(); current != 0; current = walker->nextNode()) {
          // Get root element on first loop
          if (!rootElement) {
            rootElement = current->getParentNode();
          }

          // note: this leaks memory!
          // std::cout << current->getNodeValue() << std::endl ; // .transcode();s
          // JMH: the following was found in DOMPrint.cpp
          // JMH: see also http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNode.html
          // std::cout << current->getNodeType() << " | " ;
          // JMH: see http://xerces.apache.org/xerces-c/apiDocs-3/classXMLString.html for equals()
          if (!XMLString::equals(XMLString::transcode(current->getNodeName()), "#text")) {
            // If direct child, isPartOfGreaterGood will be false
            if (rootElement != current->getParentNode()) {
              isPartOfGreaterGood = true;
            } else {
              isPartOfGreaterGood = false;
            }

            // If comment, otherwise element
            if (XMLString::equals(XMLString::transcode(current->getNodeName()), "#comment")) { // Comments
              std::cout << "COMMENT: ";
            } else { // Elements
              if (isPartOfGreaterGood) {
                std::cout << std::endl << "--- ";
              } else {
                std::cout << std::endl << std::endl << "-----------------------------------------" << std::endl;
              }

              // Print out Node Name
              std::cout << XMLString::transcode(current->getNodeName());
            }
          }

          // If Node value exists, print it out
          if (current->getNodeValue() != NULL) {
            if (isPartOfGreaterGood) {
              std::cout << " => \"" << XMLString::transcode(current->getNodeValue()) << "\"";
            } else {
              std::cout << "\n- \"" << XMLString::transcode(current->getNodeValue()) << "\"";
            }
          }

          // Initialize map with current nodes attributes
          // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNode.html
          DOMNamedNodeMap *map = current->getAttributes();

          // If map has attributes, print them out
          // see http://xerces.apache.org/xerces-c/apiDocs-3/classDOMNamedNodeMap.html
          if (map != NULL && map->getLength() != 0) {
            std::cout << std::endl;

            if (isPartOfGreaterGood) {
              std::cout << "    ";
            } else {
              std::cout << "- ";
            }

            for (unsigned int k = 0; k < map->getLength(); k++) {
              std::cout << "|" <<
                      XMLString::transcode(map->item(k)->getNodeName()) << ":\"" <<
                      XMLString::transcode(map->item(k)->getNodeValue()) << "\"";
            }
            std::cout << "|";
          }
        }
        std::cout << std::endl;

        doc->release();
      } catch (const OutOfMemoryException&) {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        errorCode = 5;
      } catch (const DOMException& e) {
        XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
        errorCode = 2;
      } catch (...) {
        XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
        errorCode = 3;
      }
    }// (inpl != NULL)
    else {
      XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
      errorCode = 4;
    }
  }

  XMLPlatformUtils::Terminate();
  return errorCode;
}