#!/bin/sh
# graphics.sh : generate svg and png versions of tree images
for i in *.dot
do
    dot -Tsvg $i > $i.svg
    dot -Tpng $i > $i.png
done
