# docxit 函数和协议设计

## 目录

[TOC]

## docxit add

### 主函数

```flow
st=>start: docxit add <filenames>
cond1=>condition: 对每个文件(忽略目录)
该文件是否存在
sub2=>subroutine: removeIndex (<filename>)
condret=>condition: 函数成功找到并
删除文件记录
fatal=>end: fatal error: 文件不存在
op1=>operation: 对文件调用 sha1 算法求出 key
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

### index 文件格式

（暂时先这样，以后可能考虑压缩存储空间。暂时不做重命名类型）

#### 记录格式

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

#### 文件格式

```
n 的字符串形式<LF>
n 个 DocxitRecord 的二进制存储
```

*注：可以考虑从固定字节处开始存放二进制的 DocxitRecord 以方便 fseek。可能需要考虑结构体对齐*



## docxit status

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



## git commit -m \<info\>

