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
		[[ -f $file ]] && addfile=$addfile" $file" || removefile=$removefile" $file"
		return
	fi

	for i in $dirfiles
	do
		if [ -d $i ]
		then
			listDir $i 
		else
			# echo "$i"		# here
			addfile=$addfile" $i"
			
		fi
	done
}

if [[ -z $1 ]] 
then
	exit
fi

rootdir=$PWD
addfile=""
removefile=""

for j in "$@"
do
	cd $rootdir
	listDir $j
done

/usr/local/lib/docxit/addIndex $addfile
/usr/local/lib/docxit/removeIndex $removefile
