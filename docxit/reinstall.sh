#!/bin/bash

# release
make rebuild && sudo make uninstall && sudo make install && source ~/.bashrc

# debug
# make rebuild mode=debug && sudo make uninstall mode=debug && sudo make install mode=debug && source ~/.bashrc
