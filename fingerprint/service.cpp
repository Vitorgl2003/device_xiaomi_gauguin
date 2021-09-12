/*
 * Copyright (C) 2017 The Android Open Source Project
 * Copyright (C) 2020 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.1-service.xiaomi_gauguin"

#include <android/log.h>
#include <hidl/HidlTransportSupport.h>

#include "BiometricsFingerprint.h"

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint;

using android::status_t;

status_t BiometricsFingerprint::registerAsSystemService() {
    status_t ret = 0;

    ret = IBiometricsFingerprint::registerAsService();
    if (ret != 0) {
        ALOGE("Failed to register IBiometricsFingerprint (%d)", ret);
        goto fail;
    } else {
        ALOGI("Successfully registered IBiometricsFingerprint");
    }

    ret = IXiaomiFingerprint::registerAsService();
    if (ret != 0) {
        ALOGE("Failed to register IXiaomiFingerprint (%d)", ret);
        goto fail;
    } else {
        ALOGI("Successfully registered IXiaomiFingerprint");
    }

fail:
    return ret;
}

int main() {
    android::sp<BiometricsFingerprint> service = nullptr;

    service = new BiometricsFingerprint();
    if (service == nullptr) {
        ALOGE("Instance of BiometricsFingerprint is null");
        return 1;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status_t status = service->registerAsSystemService();
    if (status != android::OK) {
        ALOGE("Cannot register service for Fingerprint HAL(%d).", status);
        return 1;
    }

    joinRpcThreadpool();

    return 0; // should never get here
}
