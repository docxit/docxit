#!/bin/bash

# list all files recursively with their paths. * ? . .. is all supported

listDir(){
	if [[ -d $1 ]]
	then
		cd $1
		dirfiles=$(ls | sed "s:^:`pwd`/: ")
	else
		file=$(echo $1 | sed "s:^:`pwd`/: ")	# you can change 'echo' to 'ls' for error test
		# echo "$file"		# here
		[[ -f $file ]] && /usr/local/lib/docxit/addIndex $file || /usr/local/lib/docxit/removeIndex $file
		return
	fi

	for i in $dirfiles
	do
		if [ -d $i ]
		then
			listDir $i 
		else
			# echo "$i"		# here
			/usr/local/lib/docxit/addIndex $i
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
