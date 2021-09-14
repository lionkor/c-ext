#include <c_ext.h>

int main(int argc, char** argv) {
    c::print("Hello, ", "world!");
    c::print_debug("invoked as ", argv[0]);
    auto maybe_file = c::file::open("abc.txt", c::file::mode::READ);
    if (!maybe_file) {
        c::print_error("yikes: ", maybe_file.message());
        return 0;
    }
    auto file = maybe_file.get();
}
