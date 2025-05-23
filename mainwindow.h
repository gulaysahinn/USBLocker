#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usb_detector.h"
#include "usb_blocker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadUsbDevices();
    void blockSelectedDevice();

private:
    Ui::MainWindow *ui;
    UsbDetector *usbDetector;
    UsbBlocker *usbBlocker;
};

#endif // MAINWINDOW_H
