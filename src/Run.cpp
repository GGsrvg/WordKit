//
//  Run.cpp
//
//  Created by GGsrvg on 05.12.2021.
//

#include "Run.h"

#include <iostream>
#include <utility>

wordKit::Text::Text(std::string text): text(std::move(text)) {

}

wordKit::Text::~Text() = default;

std::string wordKit::Text::encode() noexcept {
    const std::string openKey = "<w:t>";
    const std::string closeKey = "</w:t>";
    return openKey + this->text + closeKey;
}

wordKit::RunProperty::RunProperty() = default;

wordKit::RunProperty::~RunProperty() = default;

std::string wordKit::RunProperty::encode() noexcept {
    std::string content;
    
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

wordKit::Run::Run(std::shared_ptr<wordKit::RunProperty> _property, std::vector<std::shared_ptr<Text>> _texts): property(std::move(_property)), texts(std::move(_texts)) {

}

wordKit::Run::Run(std::shared_ptr<wordKit::RunProperty> _property, const std::vector<Text*>& _texts): property(std::move(_property)), texts({}) {
    for (auto text: _texts) {
        this->texts.push_back(std::shared_ptr<Text>(text));
    }
}

wordKit::Run::~Run() = default;

std::string wordKit::Run::encode() noexcept {
    std::string content;
    
    for(const auto& text : texts) {
        content += text->encode();
    }
    
    const std::string propertyEncoded = this->property->encode();
    const std::string openKey = "<w:r>";
    const std::string closeKey = "</w:r>";
    std::string run = openKey + propertyEncoded + content + closeKey;
    return run;
}
