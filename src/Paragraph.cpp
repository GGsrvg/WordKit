//
//  Paragraph.cpp
//
//  Created by GGsrvg on 05.12.2021.
//

#include <WordKit/Paragraph.h>

#include <utility>

wordKit::ParagraphProperty::ParagraphProperty() = default;

wordKit::ParagraphProperty::~ParagraphProperty() = default;

std::string wordKit::ParagraphProperty::encode() noexcept {
    std::string content;
    
    content += HAlignmentEncode(this->horizontalTextAlignment);
    
    const std::string openKey = "<w:pPr>";
    const std::string closeKey = "</w:pPr>";
    return openKey + content + closeKey;
}

wordKit::Paragraph::Paragraph(std::shared_ptr<wordKit::ParagraphProperty> _property, std::vector<std::shared_ptr<Run>> _runs)
: property(std::move(_property)), runs(std::move(_runs)) {

}

wordKit::Paragraph::Paragraph(std::shared_ptr<wordKit::ParagraphProperty> _property, const std::vector<Run*>& _runs)
: property(std::move(_property)), runs({}) {
    for (auto run: _runs) {
        this->runs.push_back(std::shared_ptr<Run>(run));
    }
}

wordKit::Paragraph::~Paragraph() = default;

std::string wordKit::Paragraph::encode() noexcept {
    std::string content;
    
    for (const auto& run : runs) {
        content += run->encode();
    }
    
    const std::string property = this->property->encode();
    const std::string openKey = "<w:p>";
    const std::string closeKey = "</w:p>";
    return openKey + property + content + closeKey;
}
