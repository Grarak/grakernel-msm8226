#!/sbin/busybox sh

mount -o remount,rw /system
/sbin/busybox mount -t rootfs -o remount,rw rootfs

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

/sbin/busybox mount -t rootfs -o remount,ro rootfs
mount -o remount,ro /system
