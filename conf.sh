#!/bin/sh

ls -1 data/sprite | grep ".*\.png" > data/sprite/sprites.conf
ls -1 data/texture | grep ".*\.png" > data/texture/textures.conf