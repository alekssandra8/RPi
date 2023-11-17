#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QMessageBox>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

#define LED 1

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
	Q_OBJECT
	
public:
	Dialog(QWidget *parent = nullptr);
	~Dialog();
	
	void alarm();
	void ugasi();

private slots:

	void read_temp();
	
	void on_pushButton_clicked();
	
	void on_checkBox_3_clicked(bool checked);
	
	void on_checkBox_clicked(bool checked);
	
private:
	Ui::Dialog *ui;
	FILE *fp;
	int c;
	float temp;
	char str[100];
	char* ch;
	float nula = 0;
	
	QTimer* myTimer;
	QLCDNumber* myNumber;
}
#endif //DIALOG_H
