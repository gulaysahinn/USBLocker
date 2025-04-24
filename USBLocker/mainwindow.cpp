#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), usbDetector(new UsbDetector(this)), usbBlocker(new UsbBlocker(this)) {
    ui->setupUi(this);
    loadUsbDevices();
    connect(ui->blockButton, &QPushButton::clicked, this, &MainWindow::blockSelectedDevice);
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::loadUsbDevices() {
    QVector<UsbDeviceInfo> devices = usbDetector->getConnectedUsbDevices();
    ui->usbListWidget->clear();
    for (const auto &device : devices) {
        ui->usbListWidget->addItem(device.deviceID);
    }
}

void MainWindow::blockSelectedDevice() {
    QListWidgetItem *item = ui->usbListWidget->currentItem();
    if (item) {
        usbBlocker->disableUsbDevice(item->text());
    }
}
