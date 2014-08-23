/*
 * Author: Willi Ye <williye97@gmail.com>
 *
 * Copyright 2014 Willi Ye
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/battery_control.h>

/*
 * 0 - 0MA
 * 1 - 2MA
 * 2 - 100MA
 * 3 - 200MA
 * 4 - 300MA
 * 5 - 400MA
 * 6 - 500MA
 * 7 - 900MA
 * 8 - 1100MA
 * 9 - 1500MA
 * 10 - 1600MA
 */

static int getNumber(int voltage) {
	
	int ret;

	switch (voltage) {
		default:
		case 0:
			ret = 0;
			break;
		case 2:
			ret = 1;
			break;
		case 100:
			ret = 2;
			break;
		case 200:
			ret = 3;
			break;
		case 300:
			ret = 4;
			break;
		case 400:
			ret = 5;
			break;
		case 500:
			ret = 6;
			break;
		case 900:
			ret = 7;
			break;
		case 1100:
			ret = 8;
			break;
		case 1500:
			ret = 9;
			break;
		case 1600:
			ret = 10;
			break;
	}
	return ret;
}

static int getVoltage(int number) {

	int ret;

	switch (number) {
		default:
		case 0:
			ret = 0;
			break;
		case 1:
			ret = 2;
			break;
		case 2:
			ret = 100;
			break;
		case 3:
			ret = 200;
			break;
		case 4:
			ret = 300;
			break;
		case 5:
			ret = 400;
			break;
		case 6:
			ret = 500;
			break;
		case 7:
			ret = 900;
			break;
		case 8:
			ret = 1100;
			break;
		case 9:
			ret = 1500;
			break;
		case 10:
			ret = 1600;
			break;
	}
	return ret;
}

/*
 * 9VAC
 */
static ssize_t vac_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(vac_limit));
}

static ssize_t vac_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of 9vac to %d\n", getVoltage(value));
		vac_limit = getVoltage(value);
	}

	return count;
}

/*
 * AC
 */
static ssize_t ac_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(ac_limit));
}

static ssize_t ac_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of ac to %d\n", getVoltage(value));
		ac_limit = getVoltage(value);
	}

	return count;
}

/*
 * MHL_AC
 */
static ssize_t mhl_ac_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(mhl_ac_limit));
}

static ssize_t mhl_ac_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of mhl_ac to %d\n", getVoltage(value));
		mhl_ac_limit = getVoltage(value);
	}

	return count;
}

/*
 * UNKNOWN_USB
 */
static ssize_t unknown_usb_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(unknown_usb_limit));
}

static ssize_t unknown_usb_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of unknown_usb to %d\n", getVoltage(value));
		unknown_usb_limit = getVoltage(value);
	}

	return count;
}

/*
 * USB
 */
static ssize_t usb_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(usb_limit));
}

static ssize_t usb_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of usb to %d\n", getVoltage(value));
		usb_limit = getVoltage(value);
	}

	return count;
}

/*
 * Wireless
 */
static ssize_t wireless_limit_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf) {
	return sprintf(buf, "%d\n", getNumber(wireless_limit));
}

static ssize_t wireless_limit_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t count) {

	int value;

	sscanf(buf, "%d", &value);
	if (value > -1 && value < 11) {
		pr_info("set voltage of wireless to %d\n", getVoltage(value));
		wireless_limit = getVoltage(value);
	}

	return count;
}

static struct kobj_attribute vac_attribute = __ATTR(vac, 0666, vac_limit_show, vac_limit_store);
static struct kobj_attribute ac_attribute = __ATTR(ac, 0666, ac_limit_show, ac_limit_store);
static struct kobj_attribute mhl_ac_attribute = __ATTR(mhl_ac, 0666, mhl_ac_limit_show, mhl_ac_limit_store);
static struct kobj_attribute unknown_usb_attribute = __ATTR(unknown_usb, 0666, unknown_usb_limit_show, unknown_usb_limit_store);
static struct kobj_attribute usb_attribute = __ATTR(usb, 0666, usb_limit_show, usb_limit_store);
static struct kobj_attribute wireless_attribute = __ATTR(wireless, 0666, wireless_limit_show, wireless_limit_store);

static struct attribute *battery_control_attrs[] = {
	&vac_attribute.attr,
	&ac_attribute.attr,
	&mhl_ac_attribute.attr,
	&unknown_usb_attribute.attr,
	&usb_attribute.attr,
	&wireless_attribute.attr,
	NULL,
};

static struct attribute_group battery_control_attr_group = {
	.attrs = battery_control_attrs,
};

static struct kobject *battery_control_kobj;

int battery_control_init(void)
{
	int ret;

	battery_control_kobj =
		kobject_create_and_add("battery_control", kernel_kobj);

	if (!battery_control_kobj) {
		pr_err("%s battery_control_kobj create failed!\n", __FUNCTION__);
		return -ENOMEM;
        }

	ret = sysfs_create_group(battery_control_kobj, &battery_control_attr_group);

	if (ret) {
		pr_info("%s sysfs create failed!\n", __FUNCTION__);
		kobject_put(battery_control_kobj);
	}

	return ret;
}

void battery_control_exit(void) {
	if (battery_control_kobj != NULL)
		kobject_put(battery_control_kobj);
}

module_init(battery_control_init);
module_exit(battery_control_exit);
