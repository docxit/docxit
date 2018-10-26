# docxit 函数和协议设计

## 目录

[TOC]

## TODO

- [ ] 删除仓库的问题，每次更新 .docxitPath 删除不用的记录或通过命令
- [ ] 自内而外的嵌套初始化仓库问题
- [ ] 修改 `ifstream fh("/home/yxy/.docxitPath");` 为任何人都可用，且不存在文件时不应该报错
- [ ] 添加彻底卸载功能，遍历 `.docxitPath` 删除所有仓库版本文件并最后删除 `.docxitPath`。普通的卸载不会删除这些东西，下次安装可以恢复原来的仓库。



## .docxitPath 文件格式

该文件保存在 `/home/<username>/` 下，由 `docxit init` 创建，记录该用户所有 docxit 仓库的完整路径名，用于辨识当前位于哪个仓库中。

```
/path/to/your/docxit/repository1/
/path/to/your/docxit/repository2/
...
/path/to/your/docxit/repositoryn/
```



## index 文件格式

*暂时先这样，以后可能考虑压缩存储空间。暂时不做重命名类型。暂时不考虑文件权限问题。*

该文件保存了暂存区域整个目录树的信息，记录从项目初始化到目前为止，项目仓库中所有文件文件名、sha1值等

### 记录格式

```c
typedef enum{
    add, remove, changed, unchanged
}DocxitRecordKind;

typedef struct{
    DocxitRecordKind kind;
    char name[4096];		// 相对于 docxit 管理的根目录的路径名
    char key[40];			// 记录旧 key
    char newkey[40];		// 记录新 key，在 add、unchanged 或 remove 中没有意义
}DocxitRecord;
```

### 文件格式

```
n 的字符串形式<LF>
n 个 DocxitRecord 的二进制存储
```

*注：可以考虑从固定字节处开始存放二进制的 DocxitRecord 以方便 fseek。可能需要考虑结构体对齐*



## 对象格式

### BLOB 对象格式

直接存储二进制的 docx，暂时不压缩

### tree 对象格式

暂时定为

```
m n
<filename1> <key1>
<filename2> <key2>
...
<filenamem> <keym>
<dirname1> <key1>
<dirname2> <key2>
...
<dirnamen> <keyn>
```

### commit 对象格式

暂时定为

```
<tree_root_key>
<author_info>
<date>
<commit_message>
<parent_commit_object_key>
n
<child_commit_object_key1>
<child_commit_object_key2>
...
<child_commit_object_keyn>
```



## 底层函数

### valueSHA_1

- 参数是文件相对于版本根文件夹的相对路径名，不包括根文件夹名
- 返回的 string 给出该文件的 sha-1 值，40 个字符。

```flow
st=>start: valueSHA_1(string filename)
sub=>subroutine: 创建管道 pipe(pipefd[2])
sub2=>subroutine: 保存标准输出 fd = dup(STDOUT_FILENO)
sub3=>subroutine: 重定向输出到管道写端 dup2(pipefd[1]， STDOUT_FILENO)
sub4=>subroutine: 执行 sha1sum 系统命令获取 sha1 值
sub5=>subroutine: 关闭管道写端 close(pipefd[1])
sub6=>subroutine: 申请内存 buffer = malloc()
sub7=>subroutine: 用 read() 从管道读端读入 sha-1 值到内存 buffer
sub8=>subroutine: 关闭管道读端 close(pipefd[0])
sub9=>subroutine: 恢复标准输出 dup2(fd, STDOUT_FILENO)
sub10=>subroutine: 关闭临时句柄 close(fd)
sub11=>subroutine: 释放内存 free(buffer)
op=>operation: 调整内存中的字符串并生成 string 对象
op2=>end: 返回 string 对象

st->sub->sub2->sub3->sub4->sub5->sub6->sub7->sub8->sub9->sub10->sub11->op->op2
```



### docxitPath

*暂时不支持仓库嵌套*

- 访问 .docxitPath 文件，找到当前目录所在的仓库，将路径赋值给全局变量。
- 返回 1 表示成功，0 表示失败。

```flow
st=>start: docxitPath()
op1=>operation: 打开 .docxitPath 文件并读入 path 信息
cond=>condition: 当前目录包含
某个仓库的 path
op2=>operation: 将仓库路径保存在全局变量 DOCXIT_PATH 中
e=>end: return 1
f=>end: return 0
st->op1->cond(yes)->op2->e
cond(no)->f
```





## docxit add

*暂时不实现 rm，因为可以通过 add 达到同样的效果*

主要任务

- 获取文件 sha-1 值并将文件保存为 BLOB 对象
- 将文件信息记录到 index 文件

### 主函数

```flow
st=>start: docxit add <filenames>
cond1=>condition: 对每个文件(忽略目录)
该文件是否存在
sub2=>subroutine: removeIndex (<filename>)
condret=>condition: 函数成功找到并
删除文件记录
fatal=>end: fatal error: 文件不存在
op1=>subroutine: 对文件调用 sha1 算法求出 key
cond=>condition: 该 key 对象是否
已存在于 objects/
op2=>operation: 将文件保存于 objects/ 
下合适位置（不压缩）
sub1=>subroutine: addIndex (<filename>, <key>)
其中 <filename> 参数可包含路径名
e=>end: end

st->cond1(yes)->op1->cond
cond1(no)->sub2->condret(no, down)->fatal
condret(yes)->e
cond(yes)->sub1
cond(no, down)->op2->sub1->e
```

### addIndex

```flow
st=>start: addindex (<filename>,<key>)
cond1=>condition: 该文件名是否
已经存在
cond2=>condition: 该 key 值是否
发生了变化
cond3=>condition: 是否为 remove 
类型的记录
cond4=>condition: 是否为 remove 或 
unchanged 类型
opru=>operation: 修改为 changed
并添加 newkey
cond5=>condition: 是否为 add 类型
opa=>operation: 更新
key
cond6=>condition: 新 key 是否和记录
中的原 key 相等
opc=>operation: 更新
newkey
op1=>operation: 修改为 unchanged 类型
op3=>operation: 将记录的类型修改
为 unchanged
e=>end: end
op2=>operation: 添加一条 add
类型的纪录
st->cond1
cond1(yes)->cond2
cond2(yes)->cond4
cond4(yes, right)->opru(right)->e
cond4(no)->cond5
cond5(yes, right)->opa(right)->e
cond5(no)->cond6
cond6(yes)->op1->e
cond6(no)->opc(right)->e
cond2(no)->cond3(no)->e
cond3(yes)->op3->e
cond1(no)->op2(right)->e
```

### removeIndex

```flow
st=>start: removeIndex (<filename>)
cond1=>condition: 该文件名是否
已经存在
fatal=>end: 返回失败值
cond3=>condition: 是否为 remove 
类型的记录
cond4=>condition: 是否为 unchanged 
或 changed 类型
op1=>operation: 修改为 remove 类型
op2=>operation: (是 add 类型)
删除这条记录
e=>end: 正常退出函数

st->cond1
cond1(yes)->cond3
cond1(no)->fatal
cond3(yes,right)->fatal
cond3(no)->cond4
cond4(yes, right)->op1->e
cond4(no)->op2->e
```



## docxit status

主要任务：

- 根据 index 文件确定是否有要提交的文件并输出相应信息
- 根据工作区情况确定是否有未跟踪的文件并输出相应信息

### 主函数

```flow
st=>start: docxit status
op1=>operation: 从 index 文件读入 DocxitRecord 数组
op2=>operation: 查看 HEAD 文件确定并打印当前分支
cond=>condition: 有非 unchanged 记录
op3=>operation: 遍历 DocxitRecord 数组
op4=>operation: 递归遍历项目文件夹，通过文件相对路径名
找到所有未在 index 中记录的文件
cond2=>condition: 有未跟踪的文件
op7=>operation: 未跟踪文件:
docxit add <文件> 以包含要提交的内容
打印所有未跟踪文件
op5=>operation: 无文件要提交
干净的工作区
op6=>operation: 要提交的变更:
使用 docxit reset HEAD <file> 以取消暂存
打印所有非 unchanged 记录
op8=>operation: clean = true
op9=>operation: clean = false
condc=>condition: clean == true ?
opc=>operation: 提交为空，但是存在
尚未跟踪的文件
e=>end: 退出函数
conda=>condition: clean == true ?
opo=>operation: 有要提交的变更，使用
docxit commit -m <info> 提交
st->op1->op2->op3->cond
cond(yes)->op6->op9->op4->cond2
cond2(yes)->op7->conda
conda(no)->opo->e
cond(no)->op8(right)->op4
cond2(no)->condc(yes)->op5(right)->e
condc(no, down)->opo->e
conda(yes)->opc->e
```

*注：整个文件夹未记录时，可将整个文件夹作为未跟踪的文件*

直接存储这个 index 文件作为一个版本太浪费空间，比如你的项目有一个 a 文件夹，里面有 100 个文件，如果有 10 个版本，每个版本都需要记录这 100 个文件，这需要 1000 条记录；而如果把这个文件夹抽象成 tree 对象（其中存有 100 条记录），在 10 个根 tree 对象每个只需要存储 1 个这个 tree 对象（即记录了这 100 个文件），只需要 100 + 10 = 110 条记录，节省了接近 90% 的空间占用。



## docxit commit

主要任务：

- 由 index 文件生成一个根 tree 对象以及其他所有需要的 tree 对象
- 生成 commit 对象并记录根 tree对象指针和提交信息

### 主函数

```flow
st=>start: docxit commit -m <info>
op1=>operation: 访问 HEAD 文件打印分支信息
gentree=>subroutine: root = generateTreeObject ()
gencomm=>subroutine: generateCommitObject (root, info)
cond=>condition: root != NULL ?
e=>end: 结束
op2=>operation: 无文件要提交，干净的工作区

st->op1->gentree->cond
cond(yes)->gencomm->e
cond(no)->op2->e

```

### generateTreeObject

```flow
st=>start: generateTreeObject ()
op1=>operation: 访问 index 文件读出 DocxitRecord 数组
op2=>end: 返回根 tree 对象
op3=>operation: 遍历 DocxitRecord 数组
op4=>operation: 生成需要的 tree 对象
sub=>subroutine: 调用 sha1 算法求出 key
sub2=>subroutine: 调用函数利用 key 储存该对象
op5=>operation: 转化所有非 unchanged 为 unchanged 对象
cond=>condition: 有非 unchanged 记录
fe=>end: return NULL

st->op1->op3->cond(yes)->op4->sub->sub2->op5->op2
cond(no)->fe

```

### generateCommitObject

*暂定提交树用双向链表（树）表示，即树的双亲孩子表示法*

```flow
st=>start: generateCommitObject (root, info) 
op1=>operation: 将 root 和 info 以及 date、author 等信息写入临时文件
op2=>operation: 通过 HEAD 文件获得当前分支
op3=>operation: 从 refs/heads/<分支名> 文件获得上一次的 commit 对象文件
sub=>subroutine: 调用 sha1 算法求出 key
sub2=>subroutine: 调用函数利用 key 储存该文件为 commit 对象
op5=>operation: 修改两个 commit 对象文件的指针域实现双向链表插入
op6=>operation: 修改 refs/heads/<分支名> 文件为新的 commit 对象的 key
e=>end: 退出

st->op1->sub->sub2->op2->op3->op5->e
```

