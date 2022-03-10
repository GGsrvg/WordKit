//
//  Paragraph.cpp
//
//  Created by GGsrvg on 05.12.2021.
//

#include "Paragraph.h"

wordKit::ParagraphProperty::ParagraphProperty() { }

wordKit::ParagraphProperty::~ParagraphProperty() { }

std::string wordKit::ParagraphProperty::encode() noexcept {
    std::string content = "";
    
    content += HAlignmentEncode(this->horizontalTextAligmment);
    
    const std::string openKey = "<w:pPr>";
    const std::string closeKey = "</w:pPr>";
    return openKey + content + closeKey;
}

wordKit::Paragraph::Paragraph(ParagraphProperty* _property, std::vector<Run*> _runs) : property(_property), runs(_runs) {
}

wordKit::Paragraph::~Paragraph() {
    delete this->property;
    
    for(auto run : runs)
        delete run;
    
    runs.clear();
}

std::string wordKit::Paragraph::encode() noexcept {
    std::string content = "";
    
    for (auto run : runs) {
        content += run->encode();
    }
    
    const std::string property = this->property->encode();
    const std::string openKey = "<w:p>";
    const std::string closeKey = "</w:p>";
    return openKey + property + content + closeKey;
}
