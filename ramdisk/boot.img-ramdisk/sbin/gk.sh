#!/sbin/busybox sh

/sbin/busybox mount -o remount,rw /system
/sbin/busybox mount -t rootfs -o remount,rw rootfs

cd /sbin

for i in $(./busybox --list)
do
	./busybox ln -s busybox $i
done

cd /

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

/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

/sbin/busybox mount -t rootfs -o remount,ro rootfs
mount -o remount,ro /system
