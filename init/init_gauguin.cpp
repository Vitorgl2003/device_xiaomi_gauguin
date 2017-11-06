/*
 * Copyright (c) 2021, The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

void property_override(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);

    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_gauguin() {
    property_override("ro.build.fingerprint", "Xiaomi/gauguin_global/gauguin:11/RKQ1.200826.002/V12.5.2.0.RJSMIXM:user/release-keys");
    property_override("ro.product.brand", "Xiaomi");
    property_override("ro.product.device", "gauguin");
    property_override("ro.product.model", "M2007J17G");
    property_override("ro.product.marketname", "Mi 10T Lite");
    property_override("ro.boot.product.hardware.sku", "nfc");
}

void load_gauguinpro() {
    property_override("ro.build.fingerprint", "Redmi/gauguinpro/gauguinpro:11/RKQ1.200826.002/V12.5.3.0.RJSCNXM:user/release-keys");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "gauguinpro");
    property_override("ro.product.model", "M2007J17C");
    property_override("ro.product.marketname", "Redmi Note 9 Pro");
    property_override("ro.boot.product.hardware.sku", "nfc");
}

void load_gauguininpro() {
    property_override("ro.build.fingerprint", "Xiaomi/gauguininpro/gauguininpro:11/RKQ1.200826.002/V12.0.1.0.RJSINXM:user/release-keys");
    property_override("ro.product.brand", "Xiaomi");
    property_override("ro.product.device", "gauguininpro");
    property_override("ro.product.model", "M2007J17I");
    property_override("ro.product.marketname", "Mi 10i");
}

void vendor_load_properties() {
    std::string region = android::base::GetProperty("ro.boot.hwc", "");

    if (region.find("CN") != std::string::npos)
        load_gauguinpro();
    else if (region.find("INDIA") != std::string::npos)
        load_gauguininpro();
    else if (region.find("GLOBAL") != std::string::npos)
        load_gauguin();
}

/* From Magisk@jni/magiskhide/hide_utils.c */
static const char *cts_prop_key[] = {
	"ro.boot.verifiedbootstate",
	"ro.boot.flash.locked",
	"ro.boot.selinux",
	"ro.boot.veritymode",
	"ro.boot.warranty_bit",
	"ro.warranty_bit",
	"ro.debuggable",
	"ro.secure",
	"ro.build.type",
	"ro.build.tags",
	"ro.build.selinux",
	NULL
};

static const char *cts_prop_value[] = {
	"green",
	"1",
	"enforcing",
	"enforcing",
	"0",
	"0",
	"0",
	"1",
	"user",
	"release-keys",
	"1",
	NULL
};

static void workaround_cts_properties() {
	// Hide all sensitive props
	for (int i = 0; cts_prop_key[i]; ++i) {
		property_override(cts_prop_key[i], cts_prop_value[i]);
	}
}

/* Workaround CTS */
    workaround_cts_properties();
