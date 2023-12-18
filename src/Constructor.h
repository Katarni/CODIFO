//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "Cell.h"

class Constructor {
 public:
  static std::vector<std::vector<Cell>> constructTable(const std::string& number, int params);

  static std::vector<std::pair<int, int>> checkOutZeros(const std::vector<std::vector<Cell>>& table);

  static std::vector<std::pair<int, int>> checkOutDuplicates(const std::vector<std::vector<Cell>>& table);

  static std::vector<std::pair<int, int>> checkOutBiggest(const std::vector<std::vector<Cell>>& table);

 private:
  static std::string toLetterForm(const std::string& str);

  static void unitAdditionParams(std::string& num, int base);
  static void unitAdditionBinary(std::string& num);

  static bool isIncrease(const std::string& str);

  static char divisionByTwo(std::string& num);

  static std::string toBinaryString(std::string num);
};
