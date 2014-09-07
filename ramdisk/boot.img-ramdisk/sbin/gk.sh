#!/sbin/busybox sh

/sbin/busybox mount -o remount,rw /system
/sbin/busybox mount -t rootfs -o remount,rw rootfs

cd /sbin

for i in $(./busybox --list)
do
	./busybox ln -s busybox $i
done

cd /

mv -f /res/sense44/* /

rm -rf /system/lib/modules/*
ln -s /lib/modules/* /system/lib/modules/

mv -f /res/wifi/prima/* /system/etc/firmware/wlan/prima
mv -f /res/wifi/*.conf /system/etc/wifi

[ -f /system/app/Synapse.apk ] || mv -f /res/synapse/Synapse.apk /system/app

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

mount -t rootfs -o remount,ro rootfs
mount -o remount,ro /system
