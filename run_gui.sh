#!/bin/bash

LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

cd bin/Release
./sttyciar_gui
