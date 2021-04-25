#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_find_dialog.h"

class find_dialog : public QMainWindow
{
    Q_OBJECT

public:
    find_dialog(QWidget *parent = Q_NULLPTR);

private slots:
	void on_findPushButton_clicked();
	void on_fileLineEdit_editingFinished();
	void on_keyLineEdit_editingFinished();

private:
    Ui::find_dialogClass ui;
	std::string file_name_;
	std::string needle_;
};
