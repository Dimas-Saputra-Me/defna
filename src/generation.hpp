#pragma once

#include "./parser.hpp"

class Generator {
    public:
        inline explicit Generator(NodeExit root)
            : m_root(move(root)) 
        {

        }

        [[nodiscard]] string generate() const 
        {
            stringstream output;
            output << "global _start\n_start:\n";
            output << "    mov rax, 60\n";
            output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";
            output << "    syscall\n";
            return output.str();
        }

    private:
        const NodeExit m_root;

};