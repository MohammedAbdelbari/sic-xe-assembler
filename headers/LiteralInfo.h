#ifndef SIC_XE_ASSEMBLER_LITERALINFO_H
#define SIC_XE_ASSEMBLER_LITERALINFO_H
#include <string>
#include "enums.h"

class LiteralInfo {

public:
    std::string literal;
    LiteralType literalType;
    bool resolved;
    std::string label;
};
#endif //SIC_XE_ASSEMBLER_LITERALINFO_H