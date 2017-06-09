#!/boot/bin/sh

ready
cd /tmp/fatfs
time /system/bin/iozone -a -g 32768
ps
