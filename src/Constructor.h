//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "header.h"

class Constructor {
 public:
  static std::vector<std::vector<std::string>> constructTable(int number, int params);

 private:
  static std::string toLetterForm(const std::string& str);

  static void unitAdditionParams(std::string& num, int base);
  static void unitAdditionBinary(std::string& num);

  static bool isIncrease(const std::string& str);
};
