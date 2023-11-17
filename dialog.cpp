#include "dialog.h"
#include "ui_dialog.h"
#include <string.h>
#include <QTimer>
#include <QMessageBox>

char path[] = "/sys/bus/w1/devices/28-011820493bff/w1_slave";

Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog)
	{
		ui->setupUi(this);
		myTimer = new QTimer(this);
		connect(myTimer, SIGNAL(timeout()), this, SLOT(read_temp()));
		myTimer->start(1000);
		wiringPiSetup();
		pinMode(1, OUTPUT);
		if(wiringPiSetup() == -1)
			exit(1);
	}
	
Dialog::~Dialog()
{
	delete ui;
}

void Dialog::alarm()
{
	digitalWrite(1, 1);
	delay(300);
	digitalWrite(1, 0);
	delay(300);
}

void Dialog::ugasi()
{
	digitalWrite(1, 0);
}

void Dialog::read_temp()
{
	ui->lcdNumber->display(6);
	fp = fopen(path, "r");
	if(fp == NULL)
	{
		printf("Greska prilikom otvaranja\n");
	}


	for(int i = 0; i < 22; i++)
		fscanf(fp, "%s", str);
	
	ch = strchr(str, 't');
	ch += 2;

	if(fclose(fp))
	{
		printf("Greska prilikom zatvaranja\n");
	}

	c = atoi(ch);
	
	temp = (float)(c) / 1000.0;
	ui->lcdNumber->display(temp);

	if(temp > 25)
	{
		for(int i = 0; i < 4; i++)
		{
			alarm();
		}
	}
}

void Dialog::on_pushButton_clicked()
{
	fclose(fp);
}

void Dialog::on_checkBox_clicked(bool checked)
{
	if(checked)
	{
		QMessageBox::warning(this, "ALARM", "Visoka temperatura!");
		for(int i = 0; i < 5; i++)
		{
			alarm();
		}
	}
}

void Dialog::on_checkBox_3_clicked(bool checked)
{
	if(checked)
	{
		QMessageBox::information(this, "UPUTSTVO", "Alarm je automatski namesten na 25 stepeni. Mozete ga manuelno promeniti, tako sto cete oznaciti polje za paljenje alarma.);
	}
}
