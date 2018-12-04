#!/bin/sh

ls -d -1 textures/* | grep -E ".*.(png|jpg|bmp)$" > textures/textures.conf
