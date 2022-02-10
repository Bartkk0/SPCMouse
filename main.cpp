#include <iostream>
#include <hidapi/hidapi.h>
#include <cstdio> // printf
#include <cwchar> // wprintf
#include "MouseData.h"

#define MAX_STR 1024

void hexDump(const unsigned char *data, size_t length){
    for (size_t i = 0; i < length; ++i) {
        unsigned int d = data[i];
        printf("%02X",d);
    }
    printf("\n");
}

int main() {
    int res;
    hid_device *handle;
    wchar_t wstr[MAX_STR];

    res = hid_init();
    //handle = hid_open(0x3299, 0x4e52, nullptr);
    handle = hid_open_path("/dev/hidraw2");

//    hid_device_info* devices = hid_enumerate(0x3299, 0x4e52);
//    hid_device_info* cur_dev = devices;
//    while(cur_dev){
//        printf("%ls", cur_dev->serial_number);
//        cur_dev = cur_dev->next;
//    }
//    hid_free_enumeration(cur_dev);

    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
//    wprintf(L"Manufacturer String: %ls\n", wstr);

    // Read the Product String
    res = hid_get_product_string(handle, wstr, MAX_STR);
//    wprintf(L"Product String: %ls\n", wstr);

    // Read the Serial Number String
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
//    wprintf(L"Serial Number String: (%d) %ls\n", wstr[0], wstr);

    hid_set_nonblocking(handle, 1);

    auto *data = new LightingData;
    hexDump((unsigned char*)data, sizeof(LightingData));

//    data->effectType = EffectType::COLORFUL_STREAMING;
    hid_send_feature_report(handle, (unsigned char*)data, sizeof(*data));
}
