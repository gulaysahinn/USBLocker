#include "usb_device_info.h"

// Constructor'ı doğru isimle tanımla
UsbDeviceInfo::UsbDeviceInfo() {}

// Overloaded Constructor
UsbDeviceInfo::UsbDeviceInfo(QString devID, QString vid, QString pid, QString name)
    : deviceID(devID), vendorID(vid), productID(pid), deviceName(name) {}
