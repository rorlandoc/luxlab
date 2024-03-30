#include <fmt/format.h>

#include "luxlab/raw_image.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fmt::print("Usage: {} <raw_file_name>\n", argv[0]);
        return 1;
    }

    luxlab::RawImage image{argv[1]};
    fmt::print("{}\n", image);

    return 0;
}