#!/system/xbin/busybox sh

mount -o rw,remount /
mount -o rw,remount /system

mkdir -p /system/lib/modules/backup
mv -f /system/lib/modules/*.ko /system/lib/modules/backup
ln -s /lib/modules/* /system/lib/modules/

if [ ! -d /system/app/Synapse ]; then
	mkdir -p /system/app/Synapse
	cp -f /res/synapse/Synapse.apk /system/app/Synapse/Synapse.apk
fi

chmod 755 /res/synapse/uci
chmod 755 /res/synapse/*
chmod 755 /res/synapse/actions/*

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

mount -o ro,remount /system
mount -o ro,remount /
