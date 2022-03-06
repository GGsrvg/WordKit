//
//  Element.h
//  actGenerator
//
//  Created by GGsrvg on 02.12.2021.
//

#ifndef Element_h
#define Element_h

#include <string>


//class NewVAlignment {
//public:
//    static const NewVAlignment Top;
//    static const NewVAlignment Center;
//    static const NewVAlignment Bottom;
//
//    const std::string rawValue;
//    NewVAlignment(std::string _rawValue);
//};

namespace wordKit {

template<typename FUNCTION>

auto dsl(FUNCTION f) {
    return f();
}

enum VAlignment {
    VAAuto,
    VABaseline,
    /// For table cell - Specifies that the text should be vertically aligned to the bottom margin.
    VABottom,
    /// For table cell - Specifies that the text should be vertically aligned to the center of the cell.
    VACenter,
    /// For table cell - Specifies that the text should be vertically aligned to the top margin.
    VATop
};

enum HAlignment {
    /// justification to the left margin for left-to-right documents
    HAStart,
    /// justification to the right margin for left-to-right documents.
    HAEnd,
    /// center the text.
    HACenter,
    /// justify text between both margins equally, but inter-character spacing is not affected.
    HABoth,
    /// justify text between both margins equally, and both inter-word and inter-character spacing are affected.
    HADistribute
};

std::string VAlignmentEncode(VAlignment verticalAlignment);

std::string HAlignmentEncode(HAlignment horizontalAlignment);

/**
 Every object intherits from Encodable
 */
class Encodable {
public:
    virtual std::string encode() {
        return "ERROR";
    }
    virtual ~Encodable() {
        
    }
};

class Element: public Encodable {
public:
    Element() { }
    virtual ~Element() { }
};
}

#endif /* Element_h */
