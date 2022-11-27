//
// Created by GGsrvg on 08.03.2022.
//

#include <WordKit/SectionProperty.h>

wordKit::SectionProperty::SectionProperty() = default;

std::string wordKit::SectionProperty::encode() noexcept {
    std::string content;

    {
        std::string orientation;
        if(isVertical) {
            orientation = "portrait";
        } else {
            orientation = "landscape";
        }

        content +=
                "<w:pgSz w:h=\"" + std::to_string(height) +
                "\" w:w=\"" + std::to_string(width) +
                "\" w:orient=\"" + orientation + "\"/>";
    }
    {

        content +=
                "<w:pgMar w:left=\"" + std::to_string(marginLeft) +
                "\" w:top=\"" + std::to_string(marginTop) +
                "\" w:right=\"" + std::to_string(marginRight) +
                "\" w:bottom=\"" + std::to_string(marginBottom) +
                "\" w:header=\"" + std::to_string(marginHeader) +
                "\" w:footer=\"" + std::to_string(marginFooter) + "\"/>";
//        "\" w:gutter=\"" + std::to_string(marginGutter) + "\"/>";
    }

    const std::string openKey = "<w:sectPr>";
    const std::string closeKey = "</w:sectPr>";
    return openKey + content + closeKey;
}