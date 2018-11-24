#!/bin/bash

if [ -f ~/.docxitPath ]
then
	allrepo=$(cat ~/.docxitPath)

	touch ~/.tempfile
	for i in $allrepo
	do
		[ -d $i'.docxit' ] && echo $i >> ~/.tempfile
	done

	mv ~/.tempfile ~/.docxitPath
fi
