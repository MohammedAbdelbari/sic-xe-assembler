//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#include <vector>
#include <fstream>
#include "../headers/Assembler.h"
#include "../headers/OperationTable.h"
#include "../headers/validator.h"
#include "../headers/SymbolTable.h"
#include <regex>

Assembler *Assembler::instance = nullptr;
SymbolTable symbolTable;

Assembler *Assembler::getInstance() {

    if (instance == nullptr)
    {
        instance = new Assembler();
    }
    return instance;
}

void Assembler::execute(std::string fileName, std::map<std::string, std::string> options) {
    std::vector<Line> lines;
    std::string intermediateFile = executePass1(fileName, options, lines);
    executePass2(intermediateFile, lines);
}

Assembler::Assembler() {
    //TODO check if we want to add any functionality
}

std::string Assembler::executePass1(std::string fileName, std::map<std::string, std::string> options,
                                    std::vector<Line> &lines) {
    std::string intermediateFile;
    std::string lineString;
    std::ifstream file(fileName);
    int lineNumber = 0;
    while (std::getline(file, lineString)) {
        lineNumber++;
        std::transform(lineString.begin(), lineString.end(), lineString.begin(), toupper);
        int index = 0;
        std::string label;
        std::string operation;
        std::string operand;
        std::regex regex("\\s+");
        std::sregex_token_iterator iter(lineString.begin(), lineString.end(), regex, -1);
        std::sregex_token_iterator end;
        while(iter != end)
        {
            std::string cur = *iter;
            switch(index)
            {
                case 0:
                    label = cur;
                    symbolTable.push(label, locctr);
                    break;
                case 1:
                    if(OperationTable::getInstance()->contains(operation))
                    {
                        operation = cur;
                        break;
                    }// TODO: CHECK FOR DIRECTIVES AND POPULATE SYMBOL TABLE
                    else
                    {
                        // TODO: raise some error flag
                    }

                case 2:
                    operand = cur;
                    break;
                default:
                    index = -1;
                    break;
            }
            if(index == -1)
            {
                break;
            }
            iter++;
            index++;
        }
        
        Line line = Line(label, operation, operand);
        bool isValid = false;
        for(InstructionFormat format : OperationTable::getInstance()->getInfo(operation).supportedFormats)
        {
            if(validator::isValidLine(line, format))
            {
                isValid = true;
            }
        }
        if(isValid)
        {
            lines.push_back(line);
            // TODO: Add line to intermediate file
        }
        else
        {
            // TODO: raise some error flag
        }
    }

    return intermediateFile;
}

void Assembler::executePass2(std::string intermediateFileName, std::vector<Line> &lines) {
    //TODO implement this method
}
