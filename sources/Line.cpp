/**
 * @file Line.cpp
 * The file containing the line class implementation.
 */
#include "../headers/Line.h"
#include <iomanip>

Line::Line() {

}

Line::Line(std::string label, std::string operation, std::string operand, std::string comment) {
    this->label = label;
    this->operand = operand;
    this->operation = operation;
    this->comment = comment;
    this->error = nullptr;
    this->lineType = LineType::ASSEMBLY_STATEMENT;
    this->isIndexed = false;
}

Line::Line(std::string comment) {
    this->comment = comment;
    this->error = nullptr;
    this->lineType = LineType::COMMENT;
    this->isIndexed = false;
}

std::ostream &operator<<(std::ostream &stream, const Line &line) {
    if (line.getLineType() == LineType::ASSEMBLY_STATEMENT) {
        stream << std::hex << std::uppercase << std::setw(4) << std::left << line.locCtr << "\t";
        stream << std::setw(6) << std::left << line.label << "\t";
        stream << std::setw(6) << std::left << line.operation << "\t";
        if (line.isIndexed) {
            std::string indexedOperand = line.operand;
            indexedOperand.append(",X");
            stream << std::setw(16) << std::left << indexedOperand;
        } else {
            stream << std::setw(16) << std::left << line.operand;
        }
        stream << "\t" << std::setw(30) << std::left << line.comment;
        stream << "\t" << line.objCode;
    } else {
        stream << line.comment;
    }
    return stream;
}

Line::~Line() {
//    if (error != nullptr)
//        delete error;
}

LineType Line::getLineType() const {
    return this->lineType;
}





