// Copyright (c) Jeremiah Z. Griffin <nokurn@gmail.com>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
// SOFTWARE.

#include "Evaluator.hpp"
#include <cmath>
#include <stdexcept>

Evaluator::Evaluator(std::deque<Node> nodes)
    : _nodes{std::move(nodes)}
{
}

double Evaluator::evaluate()
{
    while (!_nodes.empty()) {
        step();
    }

    return _operands.top();
}

void Evaluator::step()
{
    auto& n = _nodes.front();
    switch (n.kind) {
        case NodeKind::Number:
            stepNumber(std::get<double>(n.value));
            break;

        case NodeKind::Operator:
            stepOperator(std::get<OperatorKind>(n.value));
            break;
    }

    _nodes.pop_front();
}

void Evaluator::stepNumber(double v)
{
    _operands.push(v);
}

void Evaluator::stepOperator(OperatorKind k)
{
    switch (k) {
        case OperatorKind::Add:
            stepAdd();
            break;

        case OperatorKind::Subtract:
            stepSubtract();
            break;

        case OperatorKind::Multiply:
            stepMultiply();
            break;

        case OperatorKind::Divide:
            stepDivide();
            break;

        case OperatorKind::Power:
            stepPower();
            break;

        default:
            throw std::runtime_error{"Unknown evaluation operator"};
    }
}

void Evaluator::stepAdd()
{
    if (_operands.size() < 2) {
        throw std::runtime_error{"Insufficient operands for addition"};
    }

    auto y = _operands.top();
    _operands.pop();

    auto x = _operands.top();
    _operands.pop();

    _operands.push(x + y);
}

void Evaluator::stepSubtract()
{
    if (_operands.size() < 2) {
        throw std::runtime_error{"Insufficient operands for subtraction"};
    }

    auto y = _operands.top();
    _operands.pop();

    auto x = _operands.top();
    _operands.pop();

    _operands.push(x - y);
}

void Evaluator::stepMultiply()
{
    if (_operands.size() < 2) {
        throw std::runtime_error{"Insufficient operands for multiplication"};
    }

    auto y = _operands.top();
    _operands.pop();

    auto x = _operands.top();
    _operands.pop();

    _operands.push(x * y);
}

void Evaluator::stepDivide()
{
    if (_operands.size() < 2) {
        throw std::runtime_error{"Insufficient operands for division"};
    }

    auto y = _operands.top();
    _operands.pop();

    auto x = _operands.top();
    _operands.pop();

    _operands.push(x / y);
}

void Evaluator::stepPower()
{
    if (_operands.size() < 2) {
        throw std::runtime_error{"Insufficient operands for power"};
    }

    auto y = _operands.top();
    _operands.pop();

    auto x = _operands.top();
    _operands.pop();

    _operands.push(std::pow(x, y));
}
