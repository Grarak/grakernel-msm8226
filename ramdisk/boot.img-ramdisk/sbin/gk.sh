#!/sbin/busybox sh

mount -o remount,rw /system
/sbin/busybox mount -t rootfs -o remount,rw rootfs

echo 2 > /sys/devices/system/cpu/sched_mc_power_savings

for i in /sys/block/*/queue/add_random;do echo 0 > $i;done

ln -s /res/synapse/uci /sbin/uci
/sbin/uci

[ -d /system/etc/init.d ] && /sbin/busybox run-parts /system/etc/init.d

/sbin/busybox mount -t rootfs -o remount,ro rootfs
mount -o remount,ro /system
