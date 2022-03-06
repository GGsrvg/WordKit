//
//  Run.cpp
//  actGenerator
//
//  Created by GGsrvg on 05.12.2021.
//

#include "Run.h"

wordKit::Text::Text(std::string text): text(text) {
//    this->text = text;
}

wordKit::Text::~Text() {
}

std::string wordKit::Text::encode() {
    const std::string openKey = "<w:t>";
    const std::string closeKey = "</w:t>";
    return openKey + this->text + closeKey;
}

wordKit::RunProperty::RunProperty() {
    
}

wordKit::RunProperty::~RunProperty() {
    
}

std::string wordKit::RunProperty::encode() {
    std::string content = "";
    
    if(!font.empty()) {
        content += font;
    }
    if(isBold) {
        content += "<w:b w:val=\"true\"/>";
    }
    if(isItalics) {
        content += "<w:i w:val=\"true\"/>";
    }
    if(isCAPS) {
        content += "<w:caps w:val=\"true\"/>";
    }
    if(isStrike) {
        content += "<w:strike w:val=\"true\"/>";
    }
    if(isUnderline) {
        content += "<w:u w:val=\"single\"/>";
    }
    if(!color.empty()) {
        content += "<w:color w:val=\"" + color + "\"/>";
    }
    if(size > 0) {
        int sizeForDoc = size * 2;
        content += "<w:sz w:val=\"" + std::to_string(sizeForDoc) + "\"/>";
        content += "<w:szCs w:val=\"" + std::to_string(sizeForDoc) + "\"/>";
    }
    
    if(content.empty()) {
        return "";
    }
    
    const std::string openKey = "<w:rPr>";
    const std::string closeKey = "</w:rPr>";
    return openKey + content + closeKey;
}

wordKit::Run::Run(wordKit::RunProperty* _property, const std::vector<Text*> _texts): property(_property), texts(_texts) {
    
}

wordKit::Run::~Run() {
    delete this->property;
    
    for(auto text : texts)
        delete text;
    
    texts.clear();
}

std::string wordKit::Run::encode() {
    std::string content = "";
    
    for(auto text : texts) {
        content += text->encode();
    }
    
    const std::string property = this->property->encode();
    const std::string openKey = "<w:r>";
    const std::string closeKey = "</w:r>";
    const std::string run = openKey + property + content + closeKey;
    return run;
}
