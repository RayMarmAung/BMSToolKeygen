#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::generateMacPassword(QString mac)
{
    QByteArray data = mac.toUtf8();
    int num = crc16(data);
    QString result = QString("%0").arg(num * 7, 4, 16);
    return result.mid(result.length()-4,4).toUpper();
}
QString MainWindow::generateRandomNumber()
{
    int num = ui->cbCompany->currentIndex();
    QString result = QString("%1").arg(num, 2, 16, QChar('0')).toUpper();
    return result;
}
QString MainWindow::generateResult(QString token)
{
    QByteArray data = token.toUtf8();
    int num = crc16(data);
    QString chksum = QString("%0").arg(num, 4, 16, QChar('0'));
    chksum = chksum.mid(chksum.length()-2, 2).toUpper();
    return token + chksum;
}
int MainWindow::crc16(QByteArray data)
{
    int num = data.length();
    bool flag = num > 0;
    int result = 0;
    if (flag)
    {
        uint16_t num2 = 0xFFFF;
        for (int i = 0; i < num; i++)
        {
            num2 ^= (uint16_t)data[i];
            for (int j = 0; j < 8; j++)
                num2 = (((num2 & 1) != 0)? ((uint16_t)(num2 >> 1 ^ 40961)) : ((uint16_t)(num2 >> 1)));
        }
        uint8_t b = (uint8_t)((num2 & 65280) >> 8);
        uint8_t b2 = (uint8_t)(num2 & 0xFF);
        result = (int)b * 256 + (int)b2;
    }
    return result;
}

void MainWindow::on_leToken_textChanged(const QString &txt)
{
    ui->btnCalculate->setDisabled(true);
    ui->leCode->clear();
    ui->leToken->setText(txt.toUpper());
    if (txt.length() == 12)
        ui->btnCalculate->setEnabled(true);
}
void MainWindow::on_btnCalculate_clicked()
{
    ui->leCode->setText(generateResult(generateMacPassword(ui->leToken->text()) + generateRandomNumber()));
}
