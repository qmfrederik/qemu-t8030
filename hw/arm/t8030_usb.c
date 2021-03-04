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

#include "qemu/osdep.h"
#include "exec/address-spaces.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "hw/hw.h"
#include "hw/sysbus.h"
#include "hw/arm/t8030_usb.h"

#define REGION_SIZE 0000000000010000

static uint64_t t8030_usb_read(void *opaque, hwaddr offset, unsigned size)
{
    fprintf(stderr, ">>> t8030_usb: reading\n");
    return 0;
}

static void t8030_usb_write(void *opaque, hwaddr offset, uint64_t value, unsigned size)
{
    fprintf(stderr, ">>> t8030_usb: writing\n");
    return;
}

static const MemoryRegionOps t8030_usb_ops = {
    .read = t8030_usb_read,
    .write = t8030_usb_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void t8030_usb_realize(DeviceState *dev, Error **errp)
{
    fprintf(stderr, "t8030_usb_realize\n");

    T8030USBState *s  = T8030_USB(dev);
    SysBusDevice *sbd = SYS_BUS_DEVICE(dev);
    
    memory_region_init_io(&s->region, OBJECT(s), &t8030_usb_ops, s,
                          "t8030.usb.region", s->size);
    sysbus_init_mmio(sbd, &s->region);
}

DeviceState *t8030_usb_create(hwaddr addr, hwaddr size)
{
    fprintf(stderr, "t8030_usb_create for USB device in memory region 0x%lx - 0x%lx\n", addr, addr + size);

    DeviceState   *dev;
    SysBusDevice  *bus;
    T8030USBState *usb;

    dev = qdev_new(TYPE_T8030_USB);

    usb = T8030_USB(dev);
    usb->size = size;

    bus = SYS_BUS_DEVICE(dev);
    sysbus_realize_and_unref(bus, &error_fatal);
    sysbus_mmio_map(bus, 0, addr);

    return dev;
}

static void t8030_usb_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->desc = "T8030 USB";
    dc->realize = t8030_usb_realize;
}

static const TypeInfo t8030_usb_info = {
    .name          = TYPE_T8030_USB,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(T8030USBState),
    .class_init    = t8030_usb_class_init,
};

static void t8030_usb_register_types(void)
{
    type_register_static(&t8030_usb_info);
}

type_init(t8030_usb_register_types)