#!/usr/bin/python

# ============================================
#   Creates an SVG keymap diagram by parsing
#   my qmk keymap.c file, including RGB LED
#   colours.
#
#   This is COMPLETELY SPECIFIC to my map!
#
#   by Matt Gemmell
#   Web:        https://mattgemmell.com/
#   Twitter:    https://twitter.com/mattgemmell
#   GitHub:     https://github.com/mattgemmell
#
# ============================================


# ============================================
#   SETTINGS
# ============================================

# Files (in same dir as this script)
keymap_filename = "keymap.c"
svg_filename = "keymap_diagram.svg"

# SVG Geometry
diagram_inset = 30 # horizontal and vertical, around entire diagram
layer_spacing = 20 # vertical spacing between each layer
layout_keys_per_row = 12 # last row (only) can have fewer keys
layout_num_edge_keys_ignored = 1 # first and last x keys per row won't be displayed in diagram
# Note: layout_keys_per_row is the actual, real number of keys per row in the keymap structure. It includes ignored edge keys.
key_width = 55
key_height = 45
key_radius = 6 # corner radius (rx and ry in SVG; doesn't seem to be compatible with CSS as of Jan 2022)
key_spacing = 4 # horizontal and vertical, interior to layout only (not around outer edges; see diagram_inset instead)
last_row_pad = 10 # additional vertical spacing (added to key_spacing) for final row

# Split layout
layout_split = True # expects an equal number of keys per half, and thus an even number of keys per row
split_spacing = 20 # horizontal spacing between halves of a split layout (used instead of horizontal key_spacing if layout_split is True)

# RGB LED colours
show_led_colours = True
led_colours_opacity = 0.3 # 0.0 to 1.0

# Layers
show_layer_titles = True
layer_title_height = 20 # text box height; set font attributes in CSS below
layer_title_spacing = 10 # vertical spacing between layer title and its layer diagram
layer_held_keycodes = { # keycodes whose keys are implicitly held down on a given layer, gaining the CSS ".held" class
  "_NAV": ["NAV"],
  "_NUM": ["NUM"],
  "_ADJUST": ["NUM", "NAV"]
}

# SVG template segments
svg_header = '''<svg width="${svg_width}" height="${svg_height}" viewBox="0 0 ${svg_width} ${svg_height}" xmlns="http://www.w3.org/2000/svg">
<style>
    svg {
        font-family: SFMono-Regular,Consolas,Liberation Mono,Menlo,monospace;
        font-size: 14px;
        font-kerning: normal;
        text-rendering: optimizeLegibility;
        fill: #333;
        background-color: white;
    }

    rect {
        fill: #f0f0f0;
        width: ${key_width}px;
        height: ${key_height}px;
    }

    .held {
        fill: #ccf;
        stroke-width: 2px;
        stroke: #666;
    }

    text {
    	text-anchor: middle;
    	dominant-baseline: middle;
    }

    .layer_title {
		font-size: 16px;
		font-weight: bold;
		fill: #777;
    }
${extra_css}
</style>
'''

svg_footer = '''
</svg>
'''

svg_layer_title = '''
<text x="${layer_title_x}" y="${layer_title_y}" class="layer_title">${layer_title}</text>
'''

svg_key = '''
<rect rx="${key_radius}" x="${key_x}" y="${key_y}" class="${key_classes}" />
<text x="${key_text_x}" y="${key_text_y}">${key_label}</text>
'''

# ============================================
#   END OF SETTINGS
# ============================================

import re
import pprint

# Read keymap C file
keymap_file = open(keymap_filename, "r")
keymap_contents = keymap_file.read()
keymap_raw = ""
ledmap_raw = ""

# Extract raw C keymap and ledmap
keymap_regexp = re.compile(r"^[^]\r\n]+?keymaps\[\][^}]+?{$.*?};$", re.MULTILINE | re.DOTALL)
keymap_match = keymap_regexp.search(keymap_contents)
if keymap_match != None:
    keymap_raw = keymap_match.group()

ledmap_regexp = re.compile(r"^[^]\r\n]+?ledmap\[\][^}]+?{$.*?};$", re.MULTILINE | re.DOTALL)
ledmap_match = ledmap_regexp.search(keymap_contents)
if ledmap_match != None:
    ledmap_raw = ledmap_match.group()

# Parse keys and LED colours into usable data
key_layers = {}
led_layers = {}
layer_order = []
row_regexp = re.compile(r"^\s*\[([^\]]+)\][^({]+[({]$([^)}]+)[)}]", re.MULTILINE)
key_row_matches = row_regexp.finditer(keymap_raw)
led_row_matches = row_regexp.finditer(ledmap_raw)
for key_row_match in key_row_matches:
    key_layers.update({key_row_match.group(1): [x.strip() for x in key_row_match.group(2).split(",")]});
    layer_order.append(key_row_match.group(1))
for led_row_match in led_row_matches:
    led_layers.update({led_row_match.group(1): [x.strip() for x in led_row_match.group(2).split(",")]});

# Create substitution mappings
layer_names = {
  "_BASE": "Base",
  "_NAV": "Navigation",
  "_NUM": "Numpad",
  "_ADJUST": "Adjust"
}

# We'll just strip the keycode_prefix if a keycode isn't found in key_names.
keycode_prefix = "KC_"
key_names = {
    "KC_MAC_UNDO": "Undo",
    "KC_MAC_REDO": "Redo",
    "KC_MAC_CUT": "Cut",
    "KC_MAC_COPY": "Copy",
    "KC_MAC_PASTE": "Paste",
    "KC_MAC_LOCK_SCRN": "Lock Screen",
    "KC_MAC_SCRN_SHOT": "Screen Shot",
    "KC_MAC_SCRN_MRKP": "Markup Screen",
    "KC_MAC_HOME": "Home",
    "KC_MAC_END": "End",
    "KC_MAC_PREV_TAB": "Prev Tab",
    "KC_MAC_NEXT_TAB": "Next Tab",
    "KC_MAC_SPOTLIGHT": "Spotlight",
    "KC_EN_DASH": "En-Dash",
    "KC_EM_DASH": "Em-Dash",
    "OS_SHFT": "Shift",
    "OS_CTRL": "Control",
    "OS_ALT": "Option",
    "OS_CMD": "Command",
    "OS_CAPS": "Globe",
    "APP_SWITCH_FRWD": "Switch App",
    "NAV": "Nav",
    "NUM": "Num",
    "KC_AUDIO_VOL_DOWN": "Vol Down",
    "KC_AUDIO_MUTE": "Mute",
    "KC_AUDIO_VOL_UP": "Vol Up",
    "KC_MS_ACCEL2": "Mouse Accel 2",
    "KC_MS_WH_DOWN": "Mouse Wheel Down",
    "KC_MS_BTN1": "Left Click",
    "KC_MS_UP": "Mouse Up",
    "KC_MS_BTN2": "Right Click",
    "KC_MS_ACCEL1": "Mouse Accel 1",
    "KC_MS_WH_UP": "Mouse Wheel Up",
    "KC_MS_LEFT": "Mouse Left",
    "KC_MS_DOWN": "Mouse Down",
    "KC_MS_RIGHT": "Mouse Right",
    "KC_BRIGHTNESS_UP": "Brightness Up",
    "KC_MEDIA_PREV_TRACK": "Prev Track",
    "KC_MEDIA_PLAY_PAUSE": "Play Pause",
    "KC_MEDIA_NEXT_TRACK": "Next Track",
    "KC_MS_ACCEL0": "Mouse Accel 0",
    "KC_BRIGHTNESS_DOWN": "Brightness Down",
    "KC_QUOT": "'",
    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SLSH": "/",
    "KC_SPC": "Space",
    "KC_ESC": "Esc",
    "KC_PGUP": "Page Up",
    "KC_UP": "Up",
    "KC_BSPC": "Backspace",
    "KC_TAB": "Tab",
    "KC_PGDOWN": "Page Down",
    "KC_LEFT": "Left",
    "KC_DOWN": "Down",
    "KC_RIGHT": "Right",
    "KC_ENT": "Enter",
    "KC_SCLN": ";",
    "KC_LPRN": "(",
    "KC_RPRN": ")",
    "KC_BSLASH": "\\",
    "KC_MINUS": "-",
    "KC_ASTR": "*",
    "KC_EQUAL": "=",
    "KC_EN_DASH": "En Dash",
    "KC_EM_DASH": "Em Dash",
    "KC_LBRACKET": "[",
    "KC_RBRACKET": "]",
    "KC_GRAVE": "`",
}

keycode_blank = "XXXXXXX"
keycode_transparent = "_______"

# Parse colour values and create mapping
led_colours = {}
colours_regexp = re.compile(r"#define\s+(\S+)\s+\{([^\}]+)\}", re.MULTILINE)
colours_matches = colours_regexp.finditer(keymap_contents)
for colour_match in colours_matches:
    led_colours.update({colour_match.group(1): [x.strip() for x in colour_match.group(2).split(",")]});

# Ensure we have at least layout_keys_per_row keys on our base layer.
num_keys = len(key_layers[layer_order[0]])
if num_keys < layout_keys_per_row:
    layout_keys_per_row = num_keys

# Calculate overall viewbox dimensions, paying attention to layout_num_edge_keys_ignored.
import math
num_rows = int(math.ceil(float(num_keys) / float(layout_keys_per_row)))
num_real_cols = layout_keys_per_row
num_cols = num_real_cols
if layout_num_edge_keys_ignored > 0:
    num_cols -= (2 * layout_num_edge_keys_ignored)

svg_width = (2 * diagram_inset) + (num_cols * key_width) + ((num_cols - 2) * key_spacing)
if layout_split:
    svg_width += split_spacing
else:
    svg_width += key_spacing

num_layers = len(layer_order)
layer_height = (num_rows * key_height) + ((num_rows - 1) * key_spacing) + last_row_pad
if show_layer_titles:
    layer_height += (layer_title_height + layer_title_spacing)
svg_height = (2 * diagram_inset) + (num_layers * layer_height) + ((num_layers - 1) * layer_spacing)

extra_css = ""
from string import Template

if show_led_colours:
    colour_css_template = Template('''
    .${colour_class} {
		fill: rgba(${colour_rgb}, ${led_colours_opacity});
    }
''')
    for colour in led_colours:
        colour_class = colour.lower()
        colour_rgb_vals = led_colours[colour]
        if not (colour_rgb_vals[0] == "0" and colour_rgb_vals[1] == "0" and colour_rgb_vals[2] == "0"):
            colour_rgb = ", ".join(colour_rgb_vals)
            extra_css += colour_css_template.substitute({'colour_class': colour_class,
                                                         'colour_rgb': colour_rgb,
                                                         'led_colours_opacity': led_colours_opacity})

layer_title_x = float(svg_width) / 2.0; # SVG text boxes are positioned at their centre point

# Generate output
svg_raw = ""

# Header
header_template = Template(svg_header)
svg_raw += header_template.substitute({'svg_width': svg_width,
                                       'svg_height': svg_height,
                                       'key_width': key_width,
                                       'key_height': key_height,
                                       'extra_css': extra_css})

# TODO: Finish!


# Footer
svg_raw += svg_footer

# Write out SVG file.
svg_file = open(svg_filename, "w")
svg_file.write(svg_raw)
svg_file.close()
