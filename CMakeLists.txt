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
FetchContent_MakeAvailable(fmt)

add_executable(luxlab
  include/luxlab/rational.hpp
  include/luxlab/tag_data_format.hpp
  include/luxlab/tag_type.hpp
  include/luxlab/byte_order.hpp
  include/luxlab/tag.hpp
  include/luxlab/ifd.hpp
  include/luxlab/exif.hpp
  include/luxlab/tiff_header.hpp
  include/luxlab/raw_image.hpp

  source/luxlab/tag_data_format.cpp
  source/luxlab/tag_type.cpp
  source/luxlab/byte_order.cpp
  source/luxlab/tag.cpp
  source/luxlab/ifd.cpp
  source/luxlab/exif.cpp
  source/luxlab/tiff_header.cpp
  source/luxlab/raw_image.cpp

  source/luxlab.cpp)
target_link_libraries(luxlab PRIVATE fmt::fmt-header-only)
target_include_directories(luxlab PRIVATE include)
