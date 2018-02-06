#!/bin/bash

BINDIR="../bin"
SRCDIR="../src"

cd $SRCDIR && 
make -f makefile &&
mv ./*.o $BINDIR &&
mv ./kayehttp $BINDIR 
