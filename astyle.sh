#!/bin/sh
find ./ -name "*.cpp" -print0 | xargs -0 astyle --options=astylerc
find ./ -name "*.h" -print0 | xargs -0 astyle --options=astylerc
