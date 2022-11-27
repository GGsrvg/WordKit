//
// Created by GGsrvg on 08.03.2022.
//

#ifndef SectionProperty_h
#define SectionProperty_h


#include "Element.h"

namespace wordKit {
/**
 * SectionProperty
 *
 * Created with default value for A4 documents.
 *
 * OOXML does not define pages--only paragraphs and text.
 * However, it does enable the storing of certain information important to page composition,
 * such as page size, page orientation, borders and margins.
 * It does this through the use of the section.
 * A section is a grouping of paragraphs that have a specific set of properties
 * used to define the pages on which the text will appear.
 *
 * A section's properties are stored in a sectPr element.
 * For all sections except the last section,
 * the sectPr element is stored as a child element of the last paragraph in the section.
 * For the last section, the sectPr is stored as a child element of the body element.
 * The following sample shows two sections--the first in portrait orientation and the second in landscape.
 */
class SectionProperty : public Encodable {
public:
    /// Specifies the page width in twentieths of a point.
    int width = 11907;
    /// Specifies the page height in twentieths of a point.
    int height = 16839;
    /// Specifies the page orientation. Possible values are landscape and portrait.
    bool isVertical = true;

    int marginLeft = 1134;
    int marginTop = 1134;
    int marginRight = 1134;
    int marginBottom = 1134;
    int marginHeader = 0;
    int marginFooter = 0;
    int marginGutter = 0;

    SectionProperty();

    std::string encode() noexcept override;
};
}

#endif /* SectionProperty_h */
