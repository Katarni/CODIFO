//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "Constructor.h"


class App : public QMainWindow {
 Q_OBJECT

 public:
  App();

 private slots:
  // Data Window
  void submitData();
  void loadData();

  // Constructor Window
  void nextStep();
  void prevStep();

 private:
  std::vector<std::vector<Cell>> table_;
  std::string number_;
  int params_;

  // Data Window
  QWidget* data_window_;
  QLabel* data_header;
  QLineEdit* number_edit_;
  QLineEdit* params_edit_;
  QPushButton* submit_button_;
  QPushButton* data_load_;

  void openDataWindow();
  void closeDataWindow();

  // Constructor Window
  int cell_width_, cell_height_;
  QWidget* constructor_window_;
  QWidget* constructor_bar_;
  QPushButton* forward_button_;
  QPushButton* back_button_;
  QLabel* constructor_number_holder;
  QLabel* constructor_params_holder;
  QLabel* table_label_;
  QScrollArea* table_scroll_area_;

  std::vector<std::vector<QLabel*>> cells_;

  void openConstructorWindow();
  void closeConstructorWindow();

  void createTable();
  void showTable();
};