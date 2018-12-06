#!/bin/bash

# docxitPath

tfiles=`ls $1".docxit/refs/tags/"`
for tfile in $tfiles
do
	echo -e "$tfile: \t`cat $1".docxit/refs/tags/"$tfile`"
done
