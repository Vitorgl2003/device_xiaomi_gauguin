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
/* From Magisk@native/jni/magiskhide/hide_utils.c */
static const char *cts_prop_key[] =
        { "ro.boot.vbmeta.device_state", "ro.boot.verifiedbootstate", "ro.boot.flash.locked",
          "ro.boot.veritymode", "ro.boot.warranty_bit", "ro.warranty_bit",
          "ro.debuggable", "ro.secure", "ro.build.type", "ro.build.tags",
          "ro.vendor.boot.warranty_bit", "ro.vendor.warranty_bit",
          "vendor.boot.vbmeta.device_state", nullptr };
static const char *cts_prop_val[] =
        { "locked", "green", "1",
          "enforcing", "0", "0",
          "0", "1", "user", "release-keys",
          "0", "0",
          "locked", nullptr };
static const char *cts_late_prop_key[] =
        { "vendor.boot.verifiedbootstate", nullptr };
static const char *cts_late_prop_val[] =
        { "green", nullptr };
static void workaround_cts_properties() {
	// Hide all sensitive props
	for (int i = 0; cts_prop_key[i]; ++i) {
		property_override(cts_prop_key[i], cts_prop_val[i]);
	}
	for (int i = 0; cts_late_prop_key[i]; ++i) {
		property_override(cts_late_prop_key[i], cts_late_prop_val[i]);
	}
}

static const char *build_keys_props[] =
{
    "ro.build.tags",
    "ro.odm.build.tags",
    "ro.product.build.tags",
    "ro.system.build.tags",
    "ro.system_ext.build.tags",
    "ro.vendor.build.tags",
    nullptr
};

void load_gauguin() {
    property_override("ro.product.mod_device", "gauguin_global");
    property_override("ro.build.fingerprint", "Xiaomi/gauguin_global/gauguin:11/RKQ1.200826.002/V12.5.2.0.RJSMIXM:user/release-keys");
    property_override("ro.product.brand", "Xiaomi");
    property_override("ro.product.device", "gauguin");
    property_override("ro.product.model", "M2007J17G");
    property_override("ro.product.marketname", "Mi 10T Lite");
    property_override("ro.boot.product.hardware.sku", "nfc");
}
void load_gauguinpro() {
    property_override("ro.product.mod_device", "gauguin_global");
    property_override("ro.build.fingerprint", "Redmi/gauguinpro/gauguinpro:11/RKQ1.200826.002/V12.5.3.0.RJSCNXM:user/release-keys");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.device", "gauguinpro");
    property_override("ro.product.model", "M2007J17C");
    property_override("ro.product.marketname", "Redmi Note 9 Pro");
    property_override("ro.boot.product.hardware.sku", "nfc");
}
void load_gauguininpro() {
    property_override("ro.product.mod_device", "gauguin_in_global");
    property_override("ro.build.fingerprint", "Xiaomi/gauguininpro/gauguininpro:11/RKQ1.200826.002/V12.0.1.0.RJSINXM:user/release-keys");
    property_override("ro.product.brand", "Xiaomi");
    property_override("ro.product.device", "gauguininpro");
    property_override("ro.product.model", "M2007J17I");
    property_override("ro.product.marketname", "Mi 10i");
}
void load_miuicamera_properties() {
    property_override("vendor.camera.aux.packagelist", "com.android.camera,org.codeaurora.snapcam");
    property_override("persist.vendor.camera.privapp.list", "com.android.camera");
    property_override("ro.com.google.lens.oem_camera_package", "com.android.camera");
    property_override("ro.miui.notch", "1");
}

void vendor_load_properties() {
    std::string region = android::base::GetProperty("ro.boot.hwc", "");
    if (region.find("CN") != std::string::npos)
        load_gauguinpro();
    else if (region.find("INDIA") != std::string::npos)
        load_gauguininpro();
    else if (region.find("GLOBAL") != std::string::npos)
        load_gauguin();

/* Workaround CTS */
    workaround_cts_properties();
/* Spoof Build keys */
	  for (int i = 0; build_keys_props[i]; ++i) {
		  property_override(build_keys_props[i], "release-keys");
	  }
/* Miui Camera */
   load_miuicamera_properties();
}
