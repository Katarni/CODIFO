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

  static std::string getNormalForm(const std::string& params, const std::string& values);

  static void getAns(const std::vector<std::pair<int, std::vector<int>>> &vars, int row, int col,
                     const std::vector<std::vector<Cell>> &table, std::set<int> got,
                     std::vector<std::string> current,
                     std::set<std::vector<std::string>> &answers, int& min_len, int crt_len);

  static void getAll(int i, int j, const std::vector<std::vector<Cell>> &table, std::set<int>& got);

 private:
  static std::string toLetterForm(const std::string& str);

  static void unitAdditionParams(std::string& num, int base);
  static void unitAdditionBinary(std::string& num);

  static bool isIncrease(const std::string& str);

  static char divisionByTwo(std::string& num);

  static std::string toBinaryString(std::string num);

  static bool existString(const std::string& str, const std::string& find);
};
