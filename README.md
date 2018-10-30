# docxit

*A distributed version control tool for docx files.*

## Install

You should install `gcc` first.

If you want to manage versions for text files simultaneously, you should also install `git`.

Finally, do the following steps to install:

```shell
cd docxit
. install.sh
```

You can also build from source with:

```bash
cd docxit
make
sudo make install
source ~/.bashrc
```

You can reinstall with:

```shell
cd docxit
. reinstall.sh
```

## Uninstall

If you want to uninstall docxit but preserve your existing repositories (you can reinstall docxit whenever you like) , you should execute:

```bash
cd docxit
sudo make uninstall
```

If you want to uninstall docxit permanently, that is to say, you want to remove all the existing docxit repositories (.docxit directories but not workspaces, unable to recover) , you should execute:

```shell
cd docxit
./uninstall_permanently.sh
```

## Team Members

 - 赵建博 PB16001750
 - 伊昕宇 PB16001749
 - 班泰瑜 PB16001724

