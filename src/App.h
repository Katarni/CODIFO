//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "Cell.h"


class App : public QMainWindow {
 Q_OBJECT

 public:
  App();

 private slots:
  void sendData();

 private:
  std::vector<std::vector<Cell>> table_;
  int number_, params_;

  // Data Window
  QWidget* data_window_;
  QLabel* date_header;
  QLabel* data_description;
  QLineEdit* number_edit_;
  QLineEdit* params_edit_;
  QPushButton* send_button_;
};