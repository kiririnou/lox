#include "expr.hpp"

std::string BinaryExpr::to_str()  {
    return std::format("BinaryExpr {{left: {}, op: {}, right: {}}}", (*left).to_str(), op.to_str(), right->to_str());
}
