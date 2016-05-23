#!/bin/ash
#!/bin/sh
date -k
usr=$(uci get network.wan.username)
#usr="15355498807@DZKD.XY"
body="http://sx.mandroid.cn/index.php/heart/getByShell?user=""$usr"
wget -O /tmp/heart.log $body
chmod 777 /tmp/heart.log
heart=$(cut -c 3- /tmp/heart.log)
usrlen=${#usr}
len=`expr $usrlen + 86`
/usr/sbin/heart "115.239.134.167" 8080 ${heart} ${len}
date >> /tmp/sxht.log
