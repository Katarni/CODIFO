//
// Created by Тимур Ахметзянов on 14.12.2023.
//

#include "Cell.h"

Cell& Cell::operator+=(const Cell &other) {
  *this = *this + other;
  return *this;
}

Cell operator+(const Cell& cell1, const Cell& cell2) {
  return {cell1.num_ + cell2.num_};
}

size_t Cell::size() {
  return num_.size();
}

const char& Cell::operator[](int idx) const {
  return num_[idx];
}

char& Cell::operator[](int idx) {
  return num_[idx];
}

std::string Cell::getNum() {
  return num_;
}