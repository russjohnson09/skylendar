#!/bin/sh
for i in /usr /usr/local; do
		if [ -e $i/share/fonts/Type1/skylendar.pfb ]; then
				mkfontdir $i/share/fonts/Type1
				break
		fi
done
