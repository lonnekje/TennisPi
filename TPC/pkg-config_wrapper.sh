#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/opt/qtrpi/raspbian/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/opt/qtrpi/raspbian/sysroot/usr/lib/pkgconfig:/opt/qtrpi/raspbian/sysroot/usr/share/pkgconfig:/opt/qtrpi/raspbian/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
