#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "luxlab/raw_image.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fmt::print("Usage: {} <raw_file_name>\n", argv[0]);
        return 1;
    }

    luxlab::RawImage image{argv[1]};
    json j = image;

    // fmt::print("{}\n", image);
    fmt::print("{}\n", j.dump(4));

    return 0;
}