#include "c_ext.h"
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <exception>
#include <filesystem>
#include <stdexcept>

static std::string quoted(const std::string& str) {
    return "\"" + str + "\"";
}

c::err<c::file> c::file::open(const std::string& filename, mode mode, bool binary) {
    bool exists = std::filesystem::exists(filename);
    std::string c_mode;
    switch (mode) {
    case c::file::mode::READ:
        if (!exists) {
            return err<file>::make_error("file does not exist, cannot open for read: " + quoted(filename));
        }
        c_mode = "r";
        break;
    case c::file::mode::READ_WRITE:
        if (!exists) {
            return err<file>::make_error("file does not exist, cannot open for read: " + quoted(filename));
        }
        c_mode = "r+";
        break;
    case c::file::mode::TRUNCATE_WRITE:
        c_mode = "w";
        break;
    case c::file::mode::TRUNCATE_READ_WRITE:
        c_mode = "w+";
        break;
    case c::file::mode::APPEND_WRITE:
        c_mode = "a";
        break;
    case c::file::mode::APPEND_READ_WRITE:
        c_mode = "a+";
        break;
    }
    if (binary) {
        c_mode += "b";
    }

    c::file file;
    file.m_handle = fopen(filename.c_str(), c_mode.c_str());
    if (!file.m_handle) {
        auto str = std::string(std::strerror(errno));
        return err<c::file>::make_error("fopen " + quoted(filename) + " failed: " + str);
    }
    return err<c::file>::make_value(file);
}

bool c::file::close() {
    if (m_handle) {
        auto ret = fclose(m_handle);
        if (ret != 0) {
            return false;
        }
        m_handle = nullptr;
    }
    return true;
}

void c::impl::write_raw_ign_err(const std::string& str, FILE* file) {
    std::fwrite(str.data(), sizeof(std::string::value_type), str.size(), file);
}

c::exception::exception(const std::string& msg, const std::string& context) noexcept
    : std::runtime_error(msg)
    , full_msg(msg) {
    if (!context.empty()) {
        full_msg += ": \"" + context + "\"";
    }
    c::print_error(full_msg);
}

const char* c::exception::what() const noexcept {
    return full_msg.c_str();
}
