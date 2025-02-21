# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

LTO_ENABLE = yes

# feature needed
TAP_DANCE_ENABLE = yes # 1744
COMBO_ENABLE = yes # 2200

# memory saving
QMK_SETTINGS = no
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_OVERRIDE_ENABLE = no