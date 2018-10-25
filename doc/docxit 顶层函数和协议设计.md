# docxit 函数和协议设计

## add

```flow
st=>start: docxit add <filenames>
cond1=>condition: 对每个文件：
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
cond1(no)->sub2->condret(no)->fatal
condret(yes)->e
cond(yes)->sub1
cond(no)->op2->sub1->e
```

## addIndex

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
op2=>operation: 添加一条
add 型纪录
op3=>operation: 将记录的类型修改
为 unchanged
e=>end: end

st->cond1
cond1(yes)->cond2
cond2(yes)->cond4
cond4(yes, right)->opru->e
cond4(no)->cond5
cond5(yes, right)->opa->e
cond5(no)->cond6
cond6(yes)->op1->e
cond6(no)->opc->e
cond2(no)->cond3(no)->e
cond3(yes)->op3->e
cond1(no)->op2->e
```

## removeIndex

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
cond3(yes,right)->fatal
cond3(no)->cond4
cond4(yes, right)->op1->e
cond4(no)->op2->e
```



## index 文件格式

（暂时先这样，以后可能考虑压缩存储空间。暂时不做重命名类型）

### 记录格式

```c
typedef enum{
    add, remove, changed, unchanged
}DocxitRecType;

typedef struct{
    RecType type;
    char name[4096];		// 相对于 docxit 管理的根目录的路径名
    char key[40];			// 记录旧 key
    char newkey[40];		// 记录新 key，在 unchanged 或 remove 中为空
    }
}DocxitRecord;	// 可能需要考虑结构体对齐问题
```

### 文件格式

```
n 的字符串形式<LF>
n 个 DocxitRecord 的二进制存储
```

**这样非常不方便单独修改某一条记录，还需要改**