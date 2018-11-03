#!/bin/bash

allrepo=$(cat ~/.docxitPath)

for i in $allrepo
do
	[ -d $i'.docxit' ] && echo $i >> ~/.tempfile
done

rm -f ~/.docxitPath
mv ~/.tempfile ~/.docxitPath
