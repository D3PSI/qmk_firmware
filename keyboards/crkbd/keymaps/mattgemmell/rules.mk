LTO_ENABLE = yes # link time optimisation
MOUSEKEY_ENABLE = yes
VIA_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUTO_SHIFT_ENABLE = yes
WEBUSB_ENABLE = no # might just be for Oryx
EXTRAKEY_ENABLE = yes # media/volume keys
SPACE_CADET_ENABLE = no # parentheses when tapping left/right mods
GRAVE_ESC_ENABLE = no # superimpose the grave (`) and Escape keys
MAGIC_ENABLE = no # NKRO toggling, mod swapping, etc
MUSIC_ENABLE = no
OLED_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no # yes for per-key/layer RGB
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes

SRC += oneshot.c
SRC += swapper.c
