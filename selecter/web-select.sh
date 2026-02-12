#!/bin/sh

# Start dwm
dwm &
sleep 1

# Show application menu using dmenu
choice=$(printf "firefox\nchromium-browser\nbrave-browser" | dmenu -p "Launch:")

# Exit if no choice made
[ -z "$choice" ] && exit 0

# Launch the selected program
"$choice" &   
