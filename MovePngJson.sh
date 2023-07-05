#!/bin/bash

# Change to the Downloads directory
cd ~/Downloads

mv -f *.json ../Projects/cordetfw/doc/json/
mv -f *.png ../Projects/cordetfw/doc/images/

cd ../Projects/cordetfw

rm -f doc/json/*\(*\).json
rm -f doc/images/*\(*\).png

