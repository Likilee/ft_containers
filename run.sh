#!/bin/bash

echo "My-tester Start"
if [ -z $1 ]; then
	make my CONT=vector
else
	make my CONT=$1
fi


echo "MLI-tester Start"
make mli
