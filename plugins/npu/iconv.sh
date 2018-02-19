#!/bin/bash

find . -name '*.php' | while read line; do
	echo "Processing file '$line'"
	iconv -f ISO-8859-2 -t UTF-8 $line > $line.utf8
	mv $line.utf8 $line
done

find . -name '*.inc' | while read line; do
        echo "Processing file '$line'"
        iconv -f ISO-8859-2 -t UTF-8 $line > $line.utf8
        mv $line.utf8 $line
done
