#!/bin/bash

pushd abstractionlayer
qmake-qt4
make release
popd

pushd networklogiclayer
qmake-qt4
make release
popd

pushd nll_hub
qmake-qt4
make release
popd

pushd nll_switch
qmake-qt4
make release
popd

pushd statisticslayer
qmake-qt4
make release
popd

pushd sttyciarui_gui
qmake-qt4
make release
popd

pushd sttyciarrunner
qmake-qt4
make release
popd

pushd sttyciar
qmake-qt4
make release
popd


