#!/bin/bash

# Flash BR or NR using Simplicity Commander
# Usage: ./flash.sh br   or   ./flash.sh nr

TARGET=$1

if [ "$TARGET" == "br" ]; then
    HEXFILE="../build/br.hex"
else
    HEXFILE="../build/nr.hex"
fi

echo "Flashing $TARGET firmware..."
simplicity_commander flash --device EFR32FG25A121F1152IM56 --image $HEXFILE
echo "Done."
