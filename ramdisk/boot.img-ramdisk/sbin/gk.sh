#!/system/bin/sh

mount -o rw,remount /system
mount -t rootfs -o rw,remount rootfs

mkdir -p /system/lib/modules/backup
mv -f /system/lib/modules/*.ko /system/lib/modules/backup
ln -s /lib/modules/* /system/lib/modules/

if [ ! -d /system/app/Synapse ]; then
	mkdir -p /system/app/Synapse
	cp -f /res/synapse/Synapse.apk /system/app/Synapse/Synapse.apk
fi

chmod 777 /res/synapse/uci
chmod 777 /res/synapse/*
chmod 777 /res/synapse/actions/*

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

mount -t rootfs -o ro,remount rootfs
mount -o ro,remount /system
