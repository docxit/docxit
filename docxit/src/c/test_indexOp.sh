#########################################################################
# File Name: test.sh
# Author: yxy
# mail: 
# Created Time: 2018年11月08日 星期四 22时36分37秒
#########################################################################
#!/bin/bash

if [[ $1 == "clean" ]]
then
	rm _test_indexOp index
else
	gcc -g -o _test_indexOp test_indexOp.c indexOp.c
	./_test_indexOp
fi
