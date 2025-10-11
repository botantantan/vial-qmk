# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

LTO_ENABLE = yes

# feature
QMK_SETTINGS = no # cuma ngefek di vial
TAP_DANCE_ENABLE = yes # 1744
COMBO_ENABLE = no # 2200
KEY_OVERRIDE_ENABLE = no

# memory saving
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# gak guna
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no