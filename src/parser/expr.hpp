#pragma once

#include "lexer/token.hpp"
#include "utils/utils.hpp"

#include <memory>

template<typename... Base>
struct Visitor : Base... {
    using Base::operator()...;
};

template<typename... T>
Visitor(T...) -> Visitor<T...>;

struct BinaryExpr;
struct GroupExpr;
struct LiteralExpr;
struct UnaryExpr;

template<class T>
struct IVisitor {
   virtual T visit(const BinaryExpr& be) = 0; 
   virtual T visit(const GroupExpr& ge) = 0;
   virtual T visit(const LiteralExpr& le) = 0;
   virtual T visit(const UnaryExpr& ue)  = 0;
};

struct IExpr {
    virtual ~IExpr() = default;
    virtual std::string accept(IVisitor<std::string>& visitor) const = 0;
};

struct BinaryExpr : public IExpr {
    std::unique_ptr<IExpr> left;
    Token op;
    std::unique_ptr<IExpr> right;

    BinaryExpr(std::unique_ptr<IExpr> left, Token op, std::unique_ptr<IExpr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::string accept(IVisitor<std::string>& visitor) const override {
        return visitor.visit(*this);
    }
};

struct GroupExpr : public IExpr {
    std::unique_ptr<IExpr> expr;

    GroupExpr(std::unique_ptr<IExpr> expr): expr(std::move(expr)) {}

    std::string accept(IVisitor<std::string>& visitor) const override {
        return visitor.visit(*this);
    }
};

struct LiteralExpr : public IExpr {
    Type value;

    LiteralExpr(Type value): value(value) {}

    std::string accept(IVisitor<std::string>& visitor) const override {
        return visitor.visit(*this);
    }

    std::string to_str() const {
        return std::visit(Visitor{
            [](const std::monostate&) -> std::string {
                return "nil";
            },
            [](const double d) -> std::string {
                return std::format("{}", d);
            },
            [](const std::string& s) -> std::string {
                return s;
            }
        }, value);
    }
};

struct UnaryExpr : public IExpr {
    Token op;
    std::unique_ptr<IExpr> right;

    UnaryExpr(Token op, std::unique_ptr<IExpr> right)
        : op(op), right(std::move(right)) {}

    std::string accept(IVisitor<std::string>& visitor) const override {
        return visitor.visit(*this);
    }
};

struct AstPrintVisitor : public IVisitor<std::string> {
    std::string print(const IExpr& expr) {
        return expr.accept(*this);
    }

    // Don't work
    // Don't need???
    // template<class Args>
    // std::string parenthesize(const std::string& name, Args args) {
    //     return std::format("{} {}", name, args->accept(*this)); 
    // }
    //
    // template<class... Args>
    // std::string parenthesize(const std::string& name, Args&&... args) {
    //     std::string str = std::format("({} {})", name, (args->accept(*this), ...));
    //     return str;
    // }

    std::string visit(const BinaryExpr& be) override {
        // return parenthesize(be.op.lexeme, be.left.get(), be.right.get());
        return std::format("({} {} {})",
                be.op.to_str(),
                be.left->accept(*this),
                be.right->accept(*this));
    }

    std::string visit(const GroupExpr& ge) override {
        return std::format("(group {})", ge.expr->accept(*this));
    }

    std::string visit(const LiteralExpr& le) override {
        return std::format("{}", le.to_str());
    }

    std::string visit(const UnaryExpr& ue) override {
        return std::format("({} {})",
                ue.op.to_str(),
                ue.right->accept(*this));
    }
};
