#ifndef _ASP_VIRTUAL_BACKEND_HPP_
#define _ASP_VIRTUAL_BACKEND_HPP_

#include <string>
#include <vector>

#include <filesystem>

#include <unistd.h>

#include "command.hpp"
#include "job.hpp"

namespace asp {

class backend_interface;

class backend_interface {
public:
    backend_interface(int _in = STDIN_FILENO, int _out = STDOUT_FILENO, int _err = STDERR_FILENO)
     : _in(_in), _out(_out), _err(_err) {}
    backend_interface(const backend_interface&) = delete;
    backend_interface& operator=(const backend_interface&) = delete;
    virtual ~backend_interface() {}
    virtual int parse(const std::string&) = 0;
    virtual bool compile() = 0;
    virtual bool execute() = 0;
    virtual std::string build_information() = 0;
    virtual std::vector<std::string> build_tab_list(const std::string&) = 0;
protected:
    virtual void execute_command(const command&) = 0;
    virtual void execute_instruction(const std::vector<std::string>&) = 0;
    virtual void execute_builtin_instruction(const std::vector<std::string>&) = 0;
protected:
    const int _in;
    const int _out;
    const int _err;
};

};

#endif // _ASP_VIRTUAL_BACKEND_HPP_