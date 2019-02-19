#pragma once

#include <functional>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>

class Element {
public:      
    struct operationState {
        // A list of the operations we do at each execution level, for example, one level includes addition and subtraction. This is iterated through in order to carry out calculations following the correct order.
        static const std::vector<std::vector<char>> opLevels;

        // A vec of shared_ptrs to our actual elements that comprise the function.
        std::vector<std::shared_ptr<Element>> data;

        // Stores the values passed into the function call for any and all variables in the expression e.g. the current value of x
        std::map<char, float> variableValues;

        // Where we are in the element vec (index)
        unsigned int scanPosition = 0;

        // This takes values from operationState::opLevels - represents which operations we're currently concerned with.
        std::vector<char> executionLevel;
    };

    virtual std::string toString() const noexcept;

    virtual float call(operationState* opState) const noexcept;

    static float binaryOperation(float val, operationState* opState) noexcept;
};

// Stores numeric values, currently only as floats.
class NumericElement : public Element {
private:
    float _data;
public:
    NumericElement(float source) : _data(source) {};

    std::string toString() const noexcept override;

    float call(operationState* opState) const noexcept override;
};

// The Element type that represents an operator (+, -, ^, sin()) in our function. Currently only does one character ops.
class OperatorElement : public Element {
private:
    char _data;
public:
    OperatorElement(char source) : _data(source) {};

    std::string toString() const noexcept override;

    // TODO: Gotta get cleaned up.
    float call(operationState* opState) const noexcept override;
};

// Represents any constants or variables in a Function. Takes values from opState->variableValues.
class VariableElement : public Element {
private:
    char _data;
	bool _sign;
public:
    VariableElement(char source, bool sign) : _data(source), _sign(sign) {};

    std::string toString() const noexcept override;

    float call(operationState* opState) const noexcept override;
};
