#
# Copyright (C) 2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from gauguin device
$(call inherit-product, device/xiaomi/gauguin/device.mk)

# Inherit some common SparkOS stuff.
$(call inherit-product, vendor/spark/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := spark_gauguin
PRODUCT_DEVICE := gauguin
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := M2007J17G
PRODUCT_MANUFACTURER := Xiaomi

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
