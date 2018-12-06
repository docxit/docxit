#!/bin/bash

# docxitPath, tagname
key=""
if [ -z $3 ]
then
	head=`cat $1".docxit/HEAD"`
	key=`cat $head`
else
	key=$3
fi

tfile=$1".docxit/refs/tags/"$2
if [ -f $tfile ]
then
	echo "error: tag '$2' exists"
else
	echo -n $key > $tfile
	echo "create tag '$2'"
fi
