//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "App.h"

App::App() {
  data_window_ = new QWidget();
  data_window_->setFixedSize(400, 250);
  data_window_->setStyleSheet("QWidget { background: #fff; }");

  number_edit_ = new QLineEdit(data_window_);
  number_edit_->resize(350, 25);
  number_edit_->move(25, 30);
  number_edit_->setPlaceholderText("Номер функции");
  number_edit_->setStyleSheet("QLineEdit { color: #000;"
                              "border-radius: 8px;"
                              "padding-left: 5px;"
                              "background: #ebd7f5; }");

  params_edit_ = new QLineEdit(data_window_);
  params_edit_->resize(150, 25);
  params_edit_->move(25, 70);
  params_edit_->setPlaceholderText("Кол-во переменных");
  params_edit_->setStyleSheet("QLineEdit { color: #000;"
                              "border-radius: 8px;"
                              "padding-left: 5px;"
                              "background: #ebd7f5; }");

  send_button_ = new QPushButton(data_window_);

  data_window_->show();
}

void App::sendData() {

}
