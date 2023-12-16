//
// Created by Тимур Ахметзянов on 14.12.2023.
//

#pragma once
#include "header.h"

class Cell {
 public:
  Cell(): date_(0), deleted_(false) {}
  Cell(const std::string& num): num_(num), date_(0), deleted_(false) {}

  std::string getNum();
  size_t size();

  char& operator[](int idx);
  const char& operator[](int idx) const;

  friend Cell operator+(const Cell& cell1, const Cell& cell2);
  Cell& operator+=(const Cell& other);

 private:
  std::string num_;
  int date_;
  bool deleted_;
};
