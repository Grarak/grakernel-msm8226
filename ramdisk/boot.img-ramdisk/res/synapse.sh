#!/bin/bash

adb shell su -c "killall com.af.synapse"
adb shell su -c "rm -rf /data/local/tmp/synapse"
adb push synapse /data/local/tmp/synapse
adb shell su -c "mount -o remount,rw /"
adb shell su -c "rm -rf /res/synapse"
adb shell su -c "mkdir -p /res/synapse"
adb shell su -c "mv -f /data/local/tmp/synapse/* /res/synapse"
adb shell su -c "/sbin/uci"
adb shell am start -n com.af.synapse/com.af.synapse.MainActivity
