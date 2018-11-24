use `./test_indexOp.sh` to test
use `./test_indexOp.sh clean` to clean
test files:
	test_indexOp.c indexOp.h indexOp.c

实现当前目录中的 addIndex.c 和 removeIndex.c
	其中 filename 变量已经存了需压添加 / 删除的文件的完整路径名（到 / 根目录的），每次执行只需要添加 / 删除一个文件
	index 文件的接口在 indexOp.h 中，使用方法可以参考 test_indexOp.c

退到 docxit/docxit 目录执行 ./reinstall.sh 可以测试代码，去一个地方 docxit init 建立仓库，之后使用 docxit add 进行测试

在 doc/ 目录下的 顶层设计.md 中有流程图参考，这个 addIndex.c 不是流程图中的 addIndex，需要从 “对文件调用 sha1 算法求出 key” 开始实现。removeIndex.c 就是流程图中的 removeIndex
