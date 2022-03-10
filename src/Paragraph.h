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
    HAlignment horizontalTextAligmment = HAStart;
    
    ParagraphProperty();
    ~ParagraphProperty() override;
    
    std::string encode() noexcept override;
};

class Paragraph: public Element {
public:
    Paragraph(ParagraphProperty*, std::vector<Run*>);
    ~Paragraph();
    std::string encode() noexcept override;
private:
    ParagraphProperty* property;
    std::vector<Run*> runs;
};
}

#endif /* Paragraph_h */
