#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_leToken_textChanged(const QString &arg1);
    void on_btnCalculate_clicked();

private:
    QString generateMacPassword(QString);
    QString generateRandomNumber();
    QString generateResult(QString);
    int crc16(QByteArray);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
