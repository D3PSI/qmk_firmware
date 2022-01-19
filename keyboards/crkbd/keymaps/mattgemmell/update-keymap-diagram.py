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
diagram_inset = 0 # horizontal and vertical, around entire diagram
layer_spacing = 30 # vertical spacing between each layer
layout_keys_per_row = 12 # last row (only) can have fewer keys
layout_num_edge_keys_ignored = 1 # first and last x keys per row won't be displayed in diagram
# Note: layout_keys_per_row is the actual, real number of keys per row in the keymap structure. It includes ignored edge keys.
key_width = 65
key_height = 55
key_radius = 6 # corner radius
key_spacing = 4 # horizontal and vertical, both between keys and around entire layer
last_row_pad = 20 # additional vertical spacing (added to key_spacing) for final row

# Split layout
layout_split = True # expects an equal number of keys per half, and thus an even number of keys per row
split_spacing = 30 # horizontal spacing between halves of a split layout (used instead of horizontal key_spacing if layout_split is True)

# RGB LED colours
show_led_colours = True # if True, sets "rgb" CSS class on the root <svg> element
led_colours_opacity = 0.3 # 0.0 to 1.0

# Layers
show_layer_titles = False
layer_title_height = 20 # text box height; set font attributes in CSS below
layer_title_spacing = 10 # vertical spacing between layer title and its layer diagram
layer_held_keycodes = { # keycodes whose keys are implicitly held down on a given layer, gaining the held_css_class specified below
  "_NAV": ["NAV"],
  "_NUM": ["NUM"],
  "_ADJUST": ["NUM", "NAV"]
}
held_css_class = "held" # edit the actual CSS below
keycode_blank = "XXXXXXX"
blank_css_class = "blank" # as above, for keys with no function (i.e. keycode_blank above)
keycode_transparent = "_______"
transparent_css_class = "transparent" # as above, for transparent keys (falling through to base layer; i.e. keycode_transparent above)
# Note: Transparent keys (on non-base layers) will be labelled identically to the corresponding key on the base layer

# SVG template segments
svg_header = '''<svg width="${svg_width}" height="${svg_height}" viewBox="0 0 ${svg_width} ${svg_height}" xmlns="http://www.w3.org/2000/svg" class="${svg_classes}">
<style>
    svg {
        font-family: -apple-system, "Helvetica Neue", sans-serif;
        font-size: 14px;
        text-rendering: optimizeLegibility;
        fill: #333;
        background-color: white;
    }

    text {
    	text-anchor: middle;
    	dominant-baseline: middle;
    }

    .text-container {
        background-color: white;
        border-radius: ${key_radius}px;
    }

    .text-container > div:hover {
        font-size: 16px;
        font-weight: bold;
    }

    .text-container > div {
        cursor: default;
        padding: 1px 2px;
        box-sizing: border-box;
        background-color: #f0f0f0;
        text-align: center;
        width: ${key_width}px;
        height: ${key_height}px;
        display: flex;
        justify-content: center;
        align-items: center;
        hyphens: auto;
        -webkit-hyphens: auto;
        -moz-hyphens: auto;
        -ms-hyphens: auto;
        border-radius: ${key_radius}px;
    }

    .text-container > div.${held_css_class} {
        background-color: #ccf;
    }

    .rgb .text-container > div.${held_css_class} {
        border: 3px solid #666;
    }

    .text-container > div.${blank_css_class} {

    }

    .text-container > div.${transparent_css_class} {

    }

    .layer_title {
		font-size: 16px;
		font-weight: bold;
		fill: #777;
    }

    .layer_bg {
        fill: #ccc;
        width: ${layer_bg_width}px;
        height: ${layer_bg_height}px;
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

svg_layer_bg = '''
<rect rx="${key_radius}" x="${layer_bg_x}" y="${layer_bg_y}" class="layer_bg" />
'''

svg_key = '''
<foreignObject x="${key_x}" y="${key_y}" width="${key_width}" height="${key_height}" class="text-container">
	<div xmlns="http://www.w3.org/1999/xhtml" lang="en" class="${key_classes}">${key_label}</div>
</foreignObject>
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
    "KC_EN_DASH": "En Dash",
    "KC_EM_DASH": "Em Dash",
    "OS_SHFT": "Shift",
    "OS_CTRL": "Ctrl",
    "OS_ALT": "Option",
    "OS_CMD": "Cmd",
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
    "KC_BRIGHTNESS_UP": "Screen Bright Up",
    "KC_MEDIA_PREV_TRACK": "Prev Track",
    "KC_MEDIA_PLAY_PAUSE": "Play Pause",
    "KC_MEDIA_NEXT_TRACK": "Next Track",
    "KC_MS_ACCEL0": "Mouse Accel 0",
    "KC_BRIGHTNESS_DOWN": "Screen Bright Down",
    "KC_QUOT": "'",
    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SLSH": "/",
    "KC_SPC": "Space",
    "KC_ESC": "Esc",
    "KC_PGUP": "Page Up",
    "KC_UP": "Up",
    "KC_BSPC": "Bkspc",
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
    "KC_LBRACKET": "[",
    "KC_RBRACKET": "]",
    "KC_GRAVE": "`",
}

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

layer_width = (num_cols * key_width) + (num_cols * key_spacing)
if layout_split:
    layer_width += split_spacing
else:
    layer_width += key_spacing
svg_width = (2 * diagram_inset) + layer_width

num_layers = len(layer_order)
layer_height = (num_rows * key_height) + ((num_rows + 1) * key_spacing) + last_row_pad
svg_height = (2 * diagram_inset) + (num_layers * layer_height) + ((num_layers - 1) * layer_spacing)
if show_layer_titles:
    svg_height += num_layers * (layer_title_height + layer_title_spacing)

extra_css = ""
from string import Template

if show_led_colours:
    colour_css_template = Template('''
    .text-container > div.${colour_class} {
		background-color: rgba(${colour_rgb}, ${led_colours_opacity});
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

# Generate output
svg_raw = ""

# Header
svg_classes = []
if show_led_colours:
    svg_classes.append("rgb")
header_template = Template(svg_header)
svg_raw += header_template.substitute({'svg_width': svg_width,
                                       'svg_height': svg_height,
                                       'svg_classes': " ".join(svg_classes),
                                       'key_width': key_width,
                                       'key_height': key_height,
                                       'key_radius': key_radius,
                                       'held_css_class': held_css_class,
                                       'blank_css_class': blank_css_class,
                                       'transparent_css_class': transparent_css_class,
                                       'layer_bg_width': layer_width,
                                       'layer_bg_height': layer_height,
                                       'extra_css': extra_css})

if show_layer_titles:
    layer_title_template = Template(svg_layer_title)
    layer_title_x = float(svg_width) / 2.0; # SVG text boxes are positioned at their centre point

layer_bg_template = Template(svg_layer_bg)
key_template = Template(svg_key)

cur_x = diagram_inset
cur_y = diagram_inset

layer_num = 0
row_num = 0

for layer_id in layer_order:
    # Layer title
    if show_layer_titles:
        layer_title = layer_names[layer_id]
        layer_title_y = float(cur_y) + (float(layer_title_height) / 2.0)
        svg_raw += layer_title_template.substitute({'layer_title_x': layer_title_x,
                                                    'layer_title_y': layer_title_y,
                                                    'layer_title': layer_title})
        cur_x = diagram_inset
        cur_y += (layer_title_height + layer_title_spacing)

    # Layer background
    svg_raw += layer_bg_template.substitute({'key_radius': key_radius,
                                             'layer_bg_x': cur_x,
                                             'layer_bg_y': cur_y})

    cur_x += key_spacing
    cur_y += key_spacing

    # Keys
    key_index = 0 # Zero-based
    key_text_x = 0
    key_text_y = 0
    key_classes = []
    key_label = ""
    layer_keys = key_layers[layer_id]
    for key in layer_keys:
        key_label = key
        key_classes = []

        # Text box position (coords are the centre of the box)
        key_text_x = float(cur_x) + (float(key_width) / 2.0)
        key_text_y = float(cur_y) + (float(key_height) / 2.0)

        # Key's human-readable label
        if key == keycode_transparent:
            key_classes.append(transparent_css_class)
            if layer_id != layer_order[0]:
                key = key_layers[layer_order[0]][key_index]

        if key in key_names:
            key_label = key_names[key]
        elif key.startswith(keycode_prefix):
            key_label = key[len(keycode_prefix):]
        elif key == keycode_blank:
            key_classes.append(blank_css_class)
            key_label = ""

        # CSS classes to apply to the key rect shape
        if layer_id in layer_held_keycodes and key in layer_held_keycodes[layer_id]:
            key_classes.append(held_css_class)
        if show_led_colours and layer_id in led_layers:
            key_classes.append(led_layers[layer_id][key_index].lower())

        svg_raw += key_template.substitute({'key_radius': key_radius,
                                            'key_x': cur_x,
                                            'key_y': cur_y,
                                            'key_classes': " ".join(key_classes),
                                            'key_width': key_width,
                                            'key_height': key_height,
                                            'key_label': key_label})

        # Prep for next key
        key_index += 1
        if (key_index % num_real_cols == 0) or (key_index == num_keys):
            # Start of a new row
            cur_x = diagram_inset + key_spacing
            cur_y += (key_spacing + key_height)
            row_num += 1
            if row_num == num_rows - 1:
                cur_y += last_row_pad
        else:
            # Continue current row
            cur_x += (key_spacing + key_width)

    # Prep for next layer
    layer_num += 1
    row_num = 0
    cur_y += layer_spacing

# Footer
svg_raw += svg_footer # no vars in this, so it can be included literally

# Write out SVG file.
svg_file = open(svg_filename, "w")
svg_file.write(svg_raw)
svg_file.close()
