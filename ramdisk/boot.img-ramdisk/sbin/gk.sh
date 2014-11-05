#!/system/bin/sh

mount -o remount,rw /system
mount -t rootfs -o remount,rw rootfs

mkdir -p /system/lib/modules/backup
mv -f /system/lib/modules/*.ko /system/lib/modules/backup
ln -s /lib/modules/* /system/lib/modules/

[ -f /system/app/Synapse.apk ] || cp -f /res/synapse/Synapse.apk /system/app

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

mount -t rootfs -o remount,ro rootfs
mount -o remount,ro /system
