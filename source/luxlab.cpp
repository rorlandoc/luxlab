#include <array>
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "luxlab/tag.hpp"

constexpr std::array<int, 12> bytes_per_component = {1, 1, 2, 4, 8, 1,
                                                     1, 2, 4, 8, 4, 8};
const std::array<std::string, 12> type_names = {
    "UBYTE", "ASCII", "USHORT", "ULONG",    "URATIONAL", "BYTE",
    "UNDEF", "SHORT", "LONG",   "RATIONAL", "FLOAT",     "DOUBLE"};

std::vector<std::byte> read_file(const std::string &filename);
void decode_buffer(const std::vector<std::byte> &buffer);
void print_hex_table(const std::vector<std::byte> &buffer,
                     const std::string &filename);

// ----------------------------------------------------------------
// ----------------------------------------------------------------
// ----------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::vector<std::byte> buffer = read_file("file1.ARW");
  decode_buffer(buffer);
  print_hex_table(buffer, "file1.txt");
  return 0;
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------
void decode_buffer(const std::vector<std::byte> &buffer) {
  int endianess = 0; // 0 - unknown, 1 - little, 2 - big

  // TIFF header is 8 bytes long
  // 2 bytes - byte alignment
  // 2 bytes - always 0x002A
  // 4 bytes - offset to the first IFD
  fmt::print("\n### TIFF HEADER ###\n");

  // First two bytes indicate the byte alignment
  fmt::print(" - Byte alignment: ");
  if (buffer[0] == std::byte{0x49} && buffer[1] == std::byte{0x49}) {
    endianess = 1;
    fmt::print("Little Endian\n");
  } else if (buffer[0] == std::byte{0x4d} && buffer[1] == std::byte{0x4d}) {
    endianess = 2;
    fmt::print("Big Endian\n");
  } else {
    endianess = 0;
    fmt::print("Unknown\n");
    return;
  }

  // Next two bytes are always 0x002a
  fmt::print(" - Verify alignment: ");
  switch (endianess) {
  case 1:
    if (!(buffer[2] == std::byte{0x2a} && buffer[3] == std::byte{0x00})) {
      fmt::print("Failed ({:02X}{:02X})\n", buffer[3], buffer[2]);
      return;
    }
    fmt::print("Done\n");
    break;
  case 2:
    if (!(buffer[2] == std::byte{0x00} && buffer[3] == std::byte{0x2a})) {
      fmt::print("Failed ({:02X}{:02X})\n", buffer[2], buffer[3]);
      return;
    }
    fmt::print("Done\n");
    break;
  }

  // Next four bytes are the offset to the first IFD
  fmt::print(" - Offset to first IFD: ");
  std::string offset;
  int offset_value = 0;
  switch (endianess) {
  case 1:
    offset = fmt::format("0x{:02X}{:02X}{:02X}{:02X}", buffer[7], buffer[6],
                         buffer[5], buffer[4]);
    offset_value = (static_cast<int>(buffer[7]) << 24) +
                   (static_cast<int>(buffer[6]) << 16) +
                   (static_cast<int>(buffer[5]) << 8) +
                   static_cast<int>(buffer[4]);
    break;
  case 2:
    offset = fmt::format("0x{:02X}{:02X}{:02X}{:02X}", buffer[4], buffer[5],
                         buffer[6], buffer[7]);
    offset_value = (static_cast<int>(buffer[4]) << 24) +
                   (static_cast<int>(buffer[5]) << 16) +
                   (static_cast<int>(buffer[6]) << 8) +
                   static_cast<int>(buffer[7]);
    break;
  }
  fmt::print("{} bytes ({})\n", offset_value, offset);

  // First IFD is at the offset_value
  // offsets computed from the first byte of the TIFF header
  int ifd_count = 0;
  fmt::print("\n### IFD{} ###\n", ifd_count);

  // First 2 bytes - number of entries in the IFD
  fmt::print(" - Number of entries: ");
  int ifd_entries = 0;
  switch (endianess) {
  case 1:
    ifd_entries = (static_cast<int>(buffer[offset_value + 1]) << 8) +
                  static_cast<int>(buffer[offset_value]);
    break;
  case 2:
    ifd_entries = (static_cast<int>(buffer[offset_value]) << 8) +
                  static_cast<int>(buffer[offset_value + 1]);
    break;
  }
  fmt::print("{}\n", ifd_entries);

  fmt::print(
      " Tag    |    Type   | Number | Size [bytes] | Value or address \n");
  fmt::print(
      " -------|-----------|--------|--------------|------------------\n");
  int current_offset = offset_value + 2;
  switch (endianess) {
  case 1:
    for (int ientry = 0; ientry < ifd_entries; ++ientry) {
      // Tag
      fmt::print(" 0x{:02X}{:02X} | ", buffer[current_offset + 1],
                 buffer[current_offset]);
      current_offset += 2;

      // Type
      int type = (static_cast<int>(buffer[current_offset + 1]) << 8) +
                 static_cast<int>(buffer[current_offset]);
      if (!(type >= 1 && type <= 12)) {
        fmt::print("\nUnknown type\n");
        return;
      }
      fmt::print("{:<9} | ", type_names[type - 1]);
      current_offset += 2;

      // Number of components
      int components = (static_cast<int>(buffer[current_offset + 3]) << 24) +
                       (static_cast<int>(buffer[current_offset + 2]) << 16) +
                       (static_cast<int>(buffer[current_offset + 1]) << 8) +
                       static_cast<int>(buffer[current_offset]);
      fmt::print("{:>6d} | ", components);
      current_offset += 4;

      // Size in bytes
      int size = components * bytes_per_component[type - 1];
      fmt::print("{:>12d} | ", size);

      // Value
      if (size > 4) {
        int value_offset =
            (static_cast<int>(buffer[current_offset + 3]) << 24) +
            (static_cast<int>(buffer[current_offset + 2]) << 16) +
            (static_cast<int>(buffer[current_offset + 1]) << 8) +
            static_cast<int>(buffer[current_offset]);
        if (type == 2) {
          for (int ichar = 0; ichar < size; ++ichar) {
            fmt::print("{:c}", buffer[value_offset + ichar]);
          }
          fmt::print("\n");
        } else if (type == 5) {
          auto numerator =
              (static_cast<unsigned long>(buffer[value_offset + 3]) << 24) +
              (static_cast<unsigned long>(buffer[value_offset + 2]) << 16) +
              (static_cast<unsigned long>(buffer[value_offset + 1]) << 8) +
              static_cast<unsigned long>(buffer[value_offset]);
          auto denominator =
              (static_cast<unsigned long>(buffer[value_offset + 7]) << 24) +
              (static_cast<unsigned long>(buffer[value_offset + 6]) << 16) +
              (static_cast<unsigned long>(buffer[value_offset + 5]) << 8) +
              static_cast<unsigned long>(buffer[value_offset + 4]);
          fmt::print("{} / {}\n", numerator, denominator);
        } else {
          fmt::print("0x{:08X}\n", value_offset);
        }
      } else {
        int value = (static_cast<int>(buffer[current_offset + 3]) << 24) +
                    (static_cast<int>(buffer[current_offset + 2]) << 16) +
                    (static_cast<int>(buffer[current_offset + 1]) << 8) +
                    static_cast<int>(buffer[current_offset]);
        if (type == 4) {
          fmt::print("0x{:08X}\n", value);
        } else {
          fmt::print("{:<d}\n", value);
        }
      }
      current_offset += 4;
    }
    break;
  case 2:
    for (int ientry = 0; ientry < ifd_entries; ++ientry) {
      // Tag
      fmt::print(" 0x{:02X}{:02X} | ", buffer[current_offset],
                 buffer[current_offset + 1]);
      current_offset += 2;
      // Type
      fmt::print("0x{:02X}{:02X} | ", buffer[current_offset],
                 buffer[current_offset + 1]);
      current_offset += 2;
      // Number of components
      fmt::print("0x{:02X}{:02X}{:02X}{:02X} | ", buffer[current_offset],
                 buffer[current_offset + 1], buffer[current_offset + 2],
                 buffer[current_offset + 3]);
      current_offset += 4;
      // Value
      fmt::print("0x{:02X}{:02X}{:02X}{:02X}\n", buffer[current_offset],
                 buffer[current_offset + 1], buffer[current_offset + 2],
                 buffer[current_offset + 3]);
    }
    break;
  }
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------
std::vector<std::byte> read_file(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);

  file.seekg(0, std::ios::end);
  int length = file.tellg();

  file.seekg(0, std::ios::beg);
  std::vector<std::byte> buffer(length);

  file.read(reinterpret_cast<char *>(buffer.data()), length);
  buffer.resize(file.tellg());

  fmt::print("Read {:.2f} MB ({} bytes)\n", buffer.size() / (1024.0 * 1024.0),
             buffer.size());

  return buffer;
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------
void print_hex_table(const std::vector<std::byte> &buffer,
                     const std::string &filename) {
  std::ofstream file(filename, std::ios::trunc);
  file << fmt::format(
      "Offset      _0 _1 _2 _3 _4 _5 _6 _7 _8 _9 _A _B _C _D _E _F\n\n");

  int line = 0;
  int counter16 = 0;
  std::string hex;
  std::string ascii;
  for (const auto &byte : buffer) {
    int value = static_cast<int>(byte);
    hex += fmt::format("{:02x} ", value);
    ascii += fmt::format(
        "{}", (value >= 32 && value <= 126) ? static_cast<char>(value) : '.');

    counter16++;
    if (counter16 >= 16) {
      std::string offset = fmt::format("0x{:08X}", line * 16);
      offset.back() = '_';

      file << fmt::format("{}  {} {}\n", offset, hex, ascii);
      hex.clear();
      ascii.clear();
      counter16 = 0;
      ++line;
    }
  }
}
