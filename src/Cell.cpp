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

const std::string &Cell::getNum() const {
  return num_;
}

void Cell::setNum(const std::string &num) {
  num_ = num;
}

int Cell::getDate() const {
  return date_;
}

void Cell::setDate(int date) {
  date_ = date;
}

bool Cell::isDeleted() const {
  return deleted_;
}

void Cell::setDeleted(bool deleted) {
  deleted_ = deleted;
}
