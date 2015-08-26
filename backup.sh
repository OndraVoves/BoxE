#!/bin/sh
./astyle.sh
./astyle-remove-backup.sh
./remove-tilda-backup.sh
tar -zcvf ../Backup/BoxE/BoxE\(`date +%d%m%y`\).tar.gz ../BoxE
