#!/bin/bash

# docxitPath, tagname, commitkey

tfile=$1".docxit/refs/tags/"$2
if [ -f $tfile ]
then
	echo "error: tag '$2' exists"
else
	echo -n $3 > $tfile
	echo "create tag '$2'"
fi
