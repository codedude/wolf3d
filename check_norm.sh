#!/bin/bash

norminette includes/*.h | grep -E "(Warning|Error)" -B1
norminette srcs/**/*.c | grep "Error" -B1
