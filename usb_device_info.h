/*#ifndef USBDEVICEINFO_H
#define USBDEVICEINFO_H

#include <QString>

struct UsbDeviceInfo {
    QString deviceID;  // USB\VID_8087&PID_0029...
    QString vendorID;  // VID (Üretici Kimliği)
    QString productID; // PID (Ürün Kimliği)
    QString deviceName; // Cihaz Adı

    UsbDeviceInfo(QString id, QString vid, QString pid, QString name)
        : deviceID(id), vendorID(vid), productID(pid), deviceName(name) {}
};

#endif // USBDEVICEINFO_H*/
#ifndef USB_DEVICE_INFO_H
#define USB_DEVICE_INFO_H

#include <QString>

class UsbDeviceInfo {
public:
    QString deviceID;
    QString vendorID;
    QString productID;
    QString deviceName;

    UsbDeviceInfo(); // Varsayılan constructor
    UsbDeviceInfo(QString devID, QString vid, QString pid, QString name);
};

#endif // USB_DEVICE_INFO_H
