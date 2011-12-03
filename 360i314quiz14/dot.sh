#!/bin/sh

for i in *.dot
do
dot -Tpng $i > $i.png
dot -Tsvg $i > $i.svg
mv *.svg svg
mv *.png png
done
