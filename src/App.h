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
  // Data Window
  void submitData();
  void loadData();

 private:
  std::vector<std::vector<std::string>> string_table_;
  std::vector<std::vector<Cell>> cell_table_;
  int number_, params_;

  // Data Window
  QWidget* data_window_;
  QLabel* data_header;
  QLineEdit* number_edit_;
  QLineEdit* params_edit_;
  QPushButton* submit_button_;
  QPushButton* data_load_;

  void openDataWindow();
};