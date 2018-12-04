#!/bin/bash

# docxitPath, tagname

tfile=$1".docxit/refs/tags/"$2
if [ ! -f $tfile ]
then
	echo "error: tag '$2' not found"
else
	rm -f $tfile
	echo "delete tag '$2'"
fi
