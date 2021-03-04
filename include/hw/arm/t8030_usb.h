/*
 * iPhone 11 - t8030 USB
 *
 * Copyright (c) 2021 Frederik Carlier (frederik.carlier@quamotion.mobi)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef T8030_USB_H
#define T8030_USB_H

typedef struct T8030USBState {
    SysBusDevice parent;
    hwaddr size;
    MemoryRegion region;
} T8030USBState;

DeviceState *t8030_usb_create(hwaddr addr, hwaddr size);

#define TYPE_T8030_USB "t8030.usb"

#define T8030_USB(obj) \
    OBJECT_CHECK(T8030USBState, (obj), TYPE_T8030_USB)

#endif /* T8030_USB_H */
