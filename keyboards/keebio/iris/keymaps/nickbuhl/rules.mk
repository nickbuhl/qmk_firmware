# Build Options
#   change yes to no to disable
#
# AUTO_SHIFT_ENABLE = yes
SWAP_HANDS_ENABLE = yes
# KEY_OVERRIDE_ENABLE = yes

# Space Optimizations
LTO_ENABLE = yes
TCONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
#MAGIC_ENABLE = no

# Custom Shift Codes
SRC += features/custom_shift_keys.c
