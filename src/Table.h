//
//  Table.hpp
//
//  Created by GGsrvg on 12.12.2021.
//

#ifndef Table_hpp
#define Table_hpp

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Element.h"
#include "Paragraph.h"

namespace wordKit {
class TableProperty: Encodable {
public:
    HAlignment horizontalAlignment = HAStart;
    
    // Borders properties
    int borderSize = 0;
    std::string borderColor = "000000";
    
    std::string caption;
    
    /**
     Specifies the method of laying out the contents of the table.
     
     Possible values are:
        - true: fixed - Uses the preferred widths on the table items
        to generate the final sizing of the table.
        The width of the table is not changed regardless of the contents of the cells.
        - false: autofit - Uses the preferred widths on the table items
        to generat the sizing of the table, but then uses the contents
        of each cell ot determine the final column widths.
     
     If pct or auto is specified, the value is ignored.
     */
    bool isFixedLayut = true;
    
    int width = 0;
    
    TableProperty();
    
    std::string encode() noexcept override;
};

class TableGrid: Encodable {
public:
    std::vector<int> widths;

    explicit TableGrid(std::vector<int>);
    std::string encode() noexcept override;
};

class TableCellProperty: Encodable {
public:
    float width = 0;
    
    // TODO: enum http://officeopenxml.com/WPtableCellProperties-Width.php
    bool isPercent = false;
    
    int gridSpan = 1;
    
    VAlignment vAlignment = VAlignment::VACenter;
    
    // when is empty do not set color
    std::string color;
    
    int marginTop = 0;
    int marginStart = 0;
    int marginEnd = 0;
    int marginBottom = 0;
    
    TableCellProperty();
    std::string encode() noexcept override;
};

class TableCell: Encodable {
public:
    TableCell(TableCellProperty*, Paragraph*);
    ~TableCell() override;
    std::string encode() noexcept override;
    
private:
    TableCellProperty* property;
    Paragraph* paragraph;
};

enum TableRowHeightRule {
    /// default value--height is determined based on the height of the contents, so the value is ignored
    HRAutomatic,
    /// height should be at least the value specified
    HRAtLeast,
    /// height should be exactly the value specified
    HRExact
};

std::string TableRowHeightRuleEncode(TableRowHeightRule tableRowHeightRule);

class TableRowProperty: Encodable {
public:
    
    TableRowHeightRule heightRule = HRAtLeast;
    int height = 0;
    
    TableRowProperty();
    std::string encode() noexcept override;
};

class TableRow: Encodable {
public:
    TableRow(TableRowProperty*, std::vector<TableCell*>);
    ~TableRow() override;
    std::string encode() noexcept override;
private:
    TableRowProperty* property;
    std::vector<TableCell*> cells;
};

class Table: public Element {
public:
    Table(TableProperty*, TableGrid*, std::vector<TableRow*>);
    ~Table() override;
    std::string encode() noexcept override;
private:
    TableProperty* property;
    TableGrid* grid;
    std::vector<TableRow*> rows;
};
}
#endif /* Table_hpp */
