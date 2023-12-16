//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "Cell.h"

class Constructor {
 public:
  static std::vector<std::vector<Cell>> constructTable(const std::string& number, int params);

 private:
  static std::string toLetterForm(const std::string& str);

  static void unitAdditionParams(std::string& num, int base);
  static void unitAdditionBinary(std::string& num);

  static bool isIncrease(const std::string& str);

  static char divisionByTwo(std::string& num);

  static std::string toBinaryString(std::string num);
};
