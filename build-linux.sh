#!/bin/bash

pushd abstractionlayer
make clean
qmake-qt4
make release
popd

pushd networklogiclayer
make clean
qmake-qt4
make release
popd

pushd nll_hub
make clean
qmake-qt4
make release
popd

pushd nll_switch
make clean
qmake-qt4
make release
popd

pushd statisticslayer
make clean
qmake-qt4
make release
popd

pushd sttyciarui_gui
make clean
qmake-qt4
make release
popd

pushd sttyciarrunner
make clean
qmake-qt4
make release
popd

pushd sttyciar
make clean
qmake-qt4
make release
popd

