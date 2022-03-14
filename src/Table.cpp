//
//  Table.cpp
//
//  Created by GGsrvg on 12.12.2021.
//

#include "Table.h"

wordKit::TableProperty::TableProperty() {
    
}

std::string wordKit::TableProperty::encode() noexcept {
    std::string content = "";
    
    content += HAlignmentEncode(this->horizontalAlignment);
    
    // set borders only when border size > 0
    if(this->borderSize > 0 ) {
        auto sizeStr = std::to_string(this->borderSize);
        auto colorStr = this->borderColor;
        
        std::string contentBorder =
        "<w:top     w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />" +
        "<w:start   w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />" +
        "<w:bottom  w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />" +
        "<w:end     w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />" +
        "<w:insideH w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />" +
        "<w:insideV w:val=\"single\" w:sz=\"" + sizeStr + "\" w:space=\"0\" w:color=\"" + colorStr + "\" />";
        
        const std::string openKeyBorder = "<w:tblBorders>";
        const std::string closeKeyBorder = "</w:tblBorders>";
        content += openKeyBorder + contentBorder + closeKeyBorder;
    }
    if(this->caption.length() > 0 ) {
        content += "<w:tblCaption w:val=\"" + this->caption + "\"/>";
    }
    {
        std::string layout;
        
        if(this->isFixedLayout) {
            layout = "fixed";
        } else {
            layout = "autofit";
        }
        
        content += "<w:tblLayout w:type=\"" + layout + "\"/>";
    }
    if(this->width) {
        content += "<w:tblW w:type=\"dxa\" w:w=\"" + std::to_string(this->width) + "\"/>";
    }
    
    const std::string openKey = "<w:tblPr>";
    const std::string closeKey = "</w:tblPr>";
    return openKey + content + closeKey;
}

wordKit::TableGrid::TableGrid(std::vector<int> _widths) : widths(_widths) {

}

std::string wordKit::TableGrid::encode() noexcept {
    std::string content = "";

    for(auto width: this->widths) {
        content += "<w:gridCol w:w=\"" + std::to_string(width) + "\"/>";
    }

    const std::string openKey = "<w:tblGrid>";
    const std::string closeKey = "</w:tblGrid>";
    return openKey + content + closeKey;
}

wordKit::TableCellProperty::TableCellProperty() {
    
}

std::string wordKit::TableCellProperty::encode() noexcept {
    std::string content = "";
    
    if(this->width > 0) {
        std::string widthType;
        std::string postfix;
        
        if(this->isPercent) {
            widthType = "pct";
            postfix = "%";
        } else {
            widthType = "dxa";
            postfix = "";
        }
        
        std::stringstream stream;
        stream << std::fixed << std::setprecision(0) << this->width;
        std::string str_width = stream.str();
        
        content += "<w:tcW w:type=\"" + widthType + "\" w:w=\"" + str_width + postfix + "\"/>";
    }
    
    if(this->gridSpan > 1) {
        content += "<w:gridSpan w:val=\"" + std::to_string(this->gridSpan) + "\"/>";
    }
    
    content += "<w:vAlign w:val=\"" + wordKit::VAlignmentEncode(this->vAlignment) + "\"/>";
    
    if(!this->color.empty()) {
        content += R"(<w:shd w:val="clear" w:color="auto" w:fill=")" + this->color + "\"/>";
    }
    
    {
        std::string marginContent =
        "<w:top w:w=\"" + std::to_string(this->marginTop) + "\" w:type=\"dxa\"/> \
        <w:start w:w=\"" + std::to_string(this->marginStart) + "\" w:type=\"dxa\"/> \
        <w:end w:w=\"" + std::to_string(this->marginEnd) + "\" w:type=\"dxa\"/> \
        <w:bottom w:w=\"" + std::to_string(this->marginBottom) + R"(" w:type="dxa"/>)";
        
        const std::string marginOpenKey = "<w:tcMar>";
        const std::string marginCloseKey = "</w:tcMar>";
        content += marginOpenKey + marginContent + marginCloseKey;
    }
    
    const std::string openKey = "<w:tcPr>";
    const std::string closeKey = "</w:tcPr>";
    return openKey + content + closeKey;
}

wordKit::TableCell::TableCell(std::shared_ptr<TableCellProperty> _property, std::shared_ptr<Paragraph> _paragraph): property(std::move(_property)), paragraph(std::move(_paragraph)) {
    
}

wordKit::TableCell::~TableCell() = default;

std::string wordKit::TableCell::encode() noexcept {
    std::string content;
    
    content += this->property->encode();
    
    content += paragraph->encode();
    
    const std::string openKey = "<w:tc>";
    const std::string closeKey = "</w:tc>";
    return openKey + content + closeKey;
}

std::string wordKit::TableRowHeightRuleEncode(wordKit::TableRowHeightRule tableRowHeightRule) {
    switch (tableRowHeightRule) {
        case wordKit::HRAutomatic:
            return "auto";
        case wordKit::HRAtLeast:
            return "atLeast";
        case wordKit::HRExact:
            return "exact";
    }
}

wordKit::TableRowProperty::TableRowProperty() = default;

std::string wordKit::TableRowProperty::encode() noexcept {
    std::string content;
    
    {
        auto ruleStr = TableRowHeightRuleEncode(this->heightRule);
        auto heightStr = std::to_string(this->height);
        
        content += "<w:trHeight w:val=\"" + heightStr + "\" w:hRule=\"" + ruleStr + "\"/>";
    }
    
    const std::string openKey = "<w:trPr>";
    const std::string closeKey = "</w:trPr>";
    return openKey + content + closeKey;
}

wordKit::TableRow::TableRow(std::shared_ptr<TableRowProperty> _property, std::vector<std::shared_ptr<TableCell>> _cells): property(std::move(_property)), cells(std::move(_cells)) {
    
}

wordKit::TableRow::~TableRow() = default;

std::string wordKit::TableRow::encode() noexcept {
    std::string content;
    
    content += this->property->encode();
    
    for (const auto& cell : cells) {
        content += cell->encode();
    }
    
    const std::string openKey = "<w:tr>";
    const std::string closeKey = "</w:tr>";
    return openKey + content + closeKey;
}


wordKit::Table::Table(std::shared_ptr<TableProperty> _property, std::shared_ptr<TableGrid> _grid, std::vector<std::shared_ptr<TableRow>> _rows):
property(std::move(_property)), grid(std::move(_grid)), rows(std::move(_rows)) {
    
}

wordKit::Table::~Table() = default;

std::string wordKit::Table::encode() noexcept {
    std::string content;
    
    content += this->property->encode();
    content += this->grid->encode();

    for (auto row : rows) {
        content += row->encode();
    }
    
    const std::string openKey = "<w:tbl>";
    const std::string closeKey = "</w:tbl>";
    return openKey + content + closeKey;
}
