#!/bin/sh

rm -f kernel.zip
rm -f ramdisk.lzo
find -name "*~" -exec rm -f {} \;
find -name ".DS_Store" -exec rm -f {} \;

build () {
	cd boot.img-ramdisk
	find . | cpio -o -H newc | lzop > ../ramdisk.lzo
	cd ..
	./mkbootimg-$1 --kernel zImage --base 0x00000000 --ramdisk_offset 0x02008000 --tags_offset 0x01e00000 --pagesize 2048 --cmdline "console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=31 ehci-hcd.park=3 zswap.enabled=0 zswap.compressor=snappy" --ramdisk ramdisk.lzo --dt dt.img -o boot.img
}

./dtbToolCM -s 2048 -d "htc,project-id = <" -o dt.img -p ../scripts/dtc/ ../arch/arm/boot/

if [ -e ~/.bash_profile ]; then
	build darwin
else
	build linux
fi

mv -v boot.img out/
cd out
zip -r kernel.zip META-INF boot.img
mv -v kernel.zip ../
cd ..
adb push kernel.zip /sdcard/
