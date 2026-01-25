#pragma once
#include <string>
#include <vector>
#include <regex>
#include <sstream>

/*
A mask template is used to add templated fields to a teletext page.
A mask template can be used in a preprocessor to add data fields to a teletext page.

A mask template can be used to make templated forms which only allow users to modify specified fields.

*/

// Parsed structure for easier access
struct MaskLine
{
  int row;
  int col;
  int size;
  std::string name;
  std::string alignment; // Optional: LEFT, CENTRE, RIGHT
  std::string type;      // Optional: STRING, NUMBER
  bool isValid;
};

class MaskTemplate {
private:
  std::vector<std::string> masks;

public:
  // Adds a mask string if it matches the format
  // Format: MS,<row>,<col>,<size>,<name>[,<ALIGN>][,<TYPE>]
  bool AddMask(std::string mask) {
    // Regex validation matching <number>,<number>,<number>,<string>[,<string>[,<string>]]
    std::regex pattern("^(\\d+),(\\d+),(\\d+),([^,]+)(?:,([^,]+)(?:,([^,]+))?)?$");
    if (std::regex_match(mask, pattern))
    {
      masks.push_back(mask);
      return true;
    }
    return false;
  }

  // Returns all masks joined by newlines
  std::string WriteMask()
  {
    std::ostringstream oss;
    for (size_t i = 0; i < masks.size(); ++i) {
      oss << "MS," << masks[i];
      if (i < masks.size() - 1)
      {
        oss << "\n";
      }
    }
    return oss.str();
  }

  // Clears all stored masks
  void ClearMask() {
    masks.clear();
  }

  // Returns the number of stored masks
  size_t GetMaskCount() const {
    return masks.size();
  }

  // Parses and returns a specific line by index
  MaskLine GetMaskLine(size_t index) const
  {
    if (index >= masks.size()) return {0, 0, 0, "", "", "", false};

    std::string line = masks[index];
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ','))
    {
      parts.push_back(item);
    }

    MaskLine result;
    result.isValid = true;

    // Basic fields (guaranteed by regex check in AddMask)
    // MS is parts[0]
    try
    {
      result.row = std::stoi(parts[1]);
      result.col = std::stoi(parts[2]);
      result.size = std::stoi(parts[3]);
    } catch (...) {
      return {0, 0, 0, "", "", "", false};
    }
    result.name = parts[4];

    // Optional fields logic
    for (size_t i = 5; i < parts.size(); ++i)
    {
      std::string part = parts[i];
      if (part == "LEFT" || part == "CENTRE" || part == "RIGHT")
      {
        result.alignment = part;
      }
      else if (part == "STRING" || part == "NUMBER")
      {
        result.type = part;
      }
    }

    return result;
  }
};
