#pragma once

#include <array>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace c {

struct exception : std::runtime_error {
    exception(const std::string& msg, const std::string& context = "") noexcept;
    virtual const char* what() const noexcept;

private:
    std::string full_msg;
};

template<class T>
struct err final {
    err() { }
    static err make_error(const std::string& e) {
        err res;
        res.m_error = e;
        res.m_ok = false;
        return res;
    }
    static err make_value(const T& v) {
        err res;
        res.m_maybe_value = v;
        res.m_ok = true;
        return res;
    }
    operator bool() const { return m_ok; }
    const T& get() const {
        if (!m_ok) {
            throw exception("can't get() value on error");
        }
        return m_maybe_value.value();
    }
    T& get() {
        if (!m_ok) {
            throw exception("can't get() value on error");
        }
        return m_maybe_value.value();
    }
    bool ok() const { return m_ok; }
    const std::string& message() const {
        if (m_ok) {
            throw exception("can't get message() on non-error");
        }
        return m_error;
    }

private:
    bool m_ok;
    std::string m_error;
    std::optional<T> m_maybe_value;
};

namespace impl {
    void write_raw_ign_err(const std::string& str, FILE* file);
    template<typename... Args>
    void print(const std::string& str) {
        write_raw_ign_err(str, stdout);
        write_raw_ign_err("\n", stdout);
    }
    template<typename... Args>
    void print(const std::string& str, Args&&... args) {
        write_raw_ign_err(str, stdout);
        print(std::forward<Args>(args)...);
    }
}

template<typename... Args>
void print(Args&&... args) {
    impl::print(std::forward<Args>(args)...);
}
template<typename... Args>
void print_error(Args&&... args) {
    impl::write_raw_ign_err("(error) ", stdout);
    impl::print(std::forward<Args>(args)...);
}
template<typename... Args>
void print_debug(Args&&... args) {
#if !defined(NDEBUG)
    impl::write_raw_ign_err("(debug) ", stdout);
    impl::print(std::forward<Args>(args)...);
#endif // not defined NDEBUG
}
template<typename... Args>
void print_warning(Args&&... args) {
    impl::write_raw_ign_err("(warning) ", stdout);
    impl::print(std::forward<Args>(args)...);
}

struct file {
    ~file() {
        (void)close();
    }

    enum class mode {
        READ,
        READ_WRITE,
        TRUNCATE_WRITE,
        TRUNCATE_READ_WRITE,
        APPEND_WRITE,
        APPEND_READ_WRITE
    };

    static err<file> open(const std::string& filename, mode mode, bool binary = false);
    mode file_mode() const { return m_mode; }
    bool is_valid() const { return bool(m_handle); }
    [[nodiscard]] bool close();

private:
    FILE* m_handle { nullptr };
    std::filesystem::path m_current_path;
    enum mode m_mode;
};

}
