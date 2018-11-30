#!/bin/bash

sudo make uninstall

if [ -f ~/.docxitPath ]
then
	docxitrepo=$(cat ~/.docxitPath)
else
	exit 0
fi

for i in $docxitrepo
do
	rm -rf "$i"".docxit"
done

rm -rf ~/.docxitPath ~/.docxitconfig
