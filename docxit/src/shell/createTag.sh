#!/bin/bash

# docxitPath, tagname

head=`cat $1".docxit/HEAD"`
commitkey=`cat $head`
tfile=$1".docxit/refs/tags/"$2
if [ -f $tfile ]
then
	echo "error: tag '$2' exists"
else
	echo -n $commitkey > $tfile
	echo "create tag '$2'"
fi
