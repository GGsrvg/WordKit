//
//  Paragraph.h
//
//  Created by GGsrvg on 02.12.2021.
//

#ifndef Paragraph_h
#define Paragraph_h

#include <string>
#include <vector>

#include "Element.h"
#include "Run.h"

namespace wordKit {
class ParagraphProperty: Encodable {
public:
    VAlignment verticalTextAlignment = VAAuto;
    HAlignment horizontalTextAlignment = HAStart;
    
    ParagraphProperty();
    ~ParagraphProperty() override;
    
    std::string encode() noexcept override;
};

class Paragraph: public Element {
public:
    Paragraph(std::shared_ptr<ParagraphProperty>, std::vector<std::shared_ptr<Run>>);
    Paragraph(std::shared_ptr<ParagraphProperty>, const std::vector<Run*>&);
    ~Paragraph() override;
    std::string encode() noexcept override;
private:
    std::shared_ptr<ParagraphProperty> property;
    std::vector<std::shared_ptr<Run>> runs;
};
}

#endif /* Paragraph_h */
