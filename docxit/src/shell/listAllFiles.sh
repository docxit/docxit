#!/bin/bash

# list all files recursively with their paths. * ? . .. is all supported

listDir(){
	if [[ -d $1 ]]
	then
		cd $1
		dirfiles=$(ls | sed "s:^:`pwd`/: ")
	else
		file=$(ls $1 | sed "s:^:`pwd`/: ")
		echo "$file"		# here
		return
	fi

	for i in $dirfiles
	do
		if [ -d $i ]
		then
			listDir $i 
		else
			echo "$i"		# here
		fi
	done
}

if [[ -z $1 ]] 
then
	exit
fi

rootdir=$PWD

for j in "$@"
do
	cd $rootdir
	listDir $j
done
