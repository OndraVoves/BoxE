#!/bin/sh
find ./ -name "*.orig" -print0 | xargs -0 rm

