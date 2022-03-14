//
//  Document.h
//
//  Created by GGsrvg on 02.12.2021.
//

#ifndef Document_h
#define Document_h
// standards
#include <iostream>
#include <cstdio>
#include <cstdlib>
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
#include "SectionProperty.h"

namespace wordKit {
/**
 * Document
 *
 * Have 2
 */
class Document {
public:
    
    std::shared_ptr<SectionProperty> property;

    /**
     Create new document by name.

     - Parameters:
        - path: where create file.
        - name: file name after save.
        - sectionProperty:

    - Sample:
        path="/Documents" and name="act_01.01.2021"
        the document is saved in the "Documents" folder with the name "act_01.01.2021"
     */
    explicit Document(const std::string& path, const std::string& name, std::shared_ptr<SectionProperty> sectionProperty);

    /**
     Create new document by name.

     - Parameters:
        - path: where create file.
        - name: file name after save.
     */
    explicit Document(const std::string& path, const std::string& name);
    
    ~Document();
    
    /**
     Remove all elements from body
     */
    void removeAllElements() noexcept;
    
    /**
     Append new elements to body
     */
    void appendElements(std::vector<std::shared_ptr<Element>>) noexcept;

    void appendElements(const std::vector<Element*>&) noexcept;

    /**
     Save on disk
     */
    void save();
private:
    struct zip_t *zip;
    std::string name;
    std::vector<std::shared_ptr<Element>> elements;
};
}

#endif /* Document_h */
