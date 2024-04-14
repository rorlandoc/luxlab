cmake_minimum_required(VERSION 3.20)

project(LuxLab
  VERSION 0.1.0
  DESCRIPTION "RAW photo editor and processor"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG develop)
FetchContent_MakeAvailable(fmt json)

add_executable(luxlab
  include/luxlab/rational.hpp
  include/luxlab/tag_data_format.hpp
  include/luxlab/tag.hpp
  include/luxlab/byte_order.hpp
  include/luxlab/directory_entry.hpp
  include/luxlab/ifd.hpp
  include/luxlab/tiff_header.hpp
  include/luxlab/reader.hpp

  source/luxlab/tag_data_format.cpp
  source/luxlab/tag.cpp
  source/luxlab/byte_order.cpp
  source/luxlab/directory_entry.cpp
  source/luxlab/ifd.cpp
  source/luxlab/tiff_header.cpp
  source/luxlab/reader.cpp

  source/luxlab.cpp)
target_link_libraries(luxlab PRIVATE fmt::fmt-header-only nlohmann_json::nlohmann_json)
target_include_directories(luxlab PRIVATE include)
