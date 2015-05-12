#!/bin/bash

for f in *.so.3.0.0
do
	f=${f#'.so.3.0.0'}
	f=${f%'.so.3.0.0'}
	ln -s $f.so.3.0.0 $f.so.3.0
	ln -s $f.so.3.0 $f.so 
done
