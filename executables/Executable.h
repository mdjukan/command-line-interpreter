#pragma once
#include "../Token.h"
#include <iostream>
#include <string>
#include <vector>

class Executable {
    protected:
    bool m_owns_in      = false;
    std::istream* m_in  = &std::cin;
    bool m_owns_out     = false;
    std::ostream* m_out = &std::cout;
    std::string m_instruction;

    private:
    std::size_t m_instr_start;
    std::size_t m_instr_end;

    public:
    Executable(const std::string instruction, const std::vector<Token>& tokens);
    virtual ~Executable();
    virtual void execute()      = 0;
    virtual std::string usage() = 0;
    void incorrect_usage_error();
    void set_in(std::istream* in);
    bool in_redirected();
    void set_out(std::ostream* out);
    bool out_redirected();
    bool writes_to_file();
    void redirect_in(const std::string& file_path);
    void redirect_out(const std::string& file_path);
    void redirect_out_app(const std::string& file_path);
    void handle_redirects(const std::string& instruction, std::vector<Token> tokens);
};
