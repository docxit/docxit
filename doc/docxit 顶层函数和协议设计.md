# docxit 函数和协议设计

## add

```flow
st=>start: docxit add <filenames>
op1=>operation: 为每个文件调用 sha1 算法求出 key
op2=>operation: 用每个文件的 key 将文件保存于 objects/ 下合适位置（暂不压缩）
sub1=>subroutine: updateIndex (<filename>,<key>)
e=>end: end

st->op1->op2->sub1->e
```

## updateIndex

```flow
st=>start: updateindex (<filename>,<key>)
cond1=>condition: 该文件名是否已经存在
cond2=>condition: 该 key 值是否发生了变化
op1=>operation: 更新 key 值
op2=>operation: 添加该文件的 (<filename>,<key>) 新纪录
e=>end: end

st->cond1
cond1(yes)->cond2
cond2(yes)->op1
cond2(no)->e
cond1(no)->op2->e
```

## index 文件格式

```
总记录数 n
<filename1>\t<key1>
<filename2>\t<key2>
...
<filenamen>\t<keyn>
```

