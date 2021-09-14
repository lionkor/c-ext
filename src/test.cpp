#include <c_ext.h>

int main(int argc, char** argv) {
    auto maybe_file = c::file::open("abc.txt", c::file::mode::READ);
    if (!maybe_file) {
        c::print_error("yikes: ", maybe_file.message());
        return 0;
    }
    auto file = maybe_file.get();
}
