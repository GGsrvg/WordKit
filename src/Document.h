//
//  Document.h
//  actGenerator
//
//  Created by GGsrvg on 02.12.2021.
//

#ifndef Document_h
#define Document_h
// standarts
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>
// third party 
#include <zip.h>
#include <pugixml.hpp>
// own
#include "Element.h"
#include "Paragraph.h"
#include "Run.h"
#include "Table.h"

namespace wordKit {
class SectionProperty: public Encodable {
public:
    int width = 11907;
    int height = 16839;
    bool isVertical = true;
    
    int marginLeft = 1134;
    int marginTop = 1134;
    int marginRight = 1134;
    int marginBottom = 1134;
    int marginHeader = 0;
    int marginFooter = 0;
    int marginGutter = 0;
    
    SectionProperty();
    std::string encode();
};

class Document {
public:
    
    SectionProperty* property = new SectionProperty();
    
    /**
     Create new document by name in memory.
     
     - Parameters:
        - path: where create file.
        - fileName: file name.
     */
    Document(std::string path);
    
    ~Document();
    
    /**
     Remove all elements from body
     */
    void removeAllElements();
    
    /**
     Append new elements to body
     */
    void appendElements(std::vector<Element*> elements);
    
    /**
     Save on disk
     */
    void save() throw();
private:
    // is also file name
    struct zip_t *zip;
    std::string name;
    std::vector<Element*> elements;
};
}

#endif /* Document_h */
