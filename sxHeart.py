__author__ = 'sxm'
import urllib2
import time
import json
import re
import hashlib
import socket
import commands
 
def get_ip():
    global URL
    try:
        res = urllib2.urlopen(URL + '/index.php/heart/GetIp', timeout=2000)
    except:
        return None
    if res.getcode() != 200:
        return None
    re = res.read().decode('gbk').encode('utf8')
    res.close()
    return json.loads(re)
 
 
 
def send_pack(data, ip, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print str(len(data)) + '(86+your ShanXun Acount)'
        sock.sendto(data, (ip, port))
    except Exception as e:
        log('ERROR: ' + time.asctime(time.localtime(time.time())) + ' \xe5\x8f\x91\xe9\x80\x81\xe6\x95\xb0\xe6\x8d\xae\xe5\xa4\xb1\xe8\xb4\xa5\r\n')
        exit()
    finally:
        sock.close()
 
 
 
def get_data(strdata):
    try:
        respone = urllib2.urlopen(URL + '/index.php/heart/getByRouter/?' + strdata)
    except:
        return None
    if respone.getcode() != 200:
        return None
    data = respone.read()
    respone.close()
    return data
 
 
 
def log(logStr):
    with open('/tmp/sxlog.txt', 'a') as f:
        f.write(logStr + '\r\n')
 
 
if __name__ == '__main__':
    URL = 'http://sx.mandroid.cn'
    user = commands.getoutput('uci get network.wan.username')
    if user == None:
        log('ERROR: ' + time.asctime(time.localtime(time.time())) + ' GET USER ERROR\r\n')
        exit()
    print user
    ip = get_ip()
    if ip == None:
        log('ERROR: ' + time.asctime(time.localtime(time.time())) + ' GET IP ERROR\r\n')
        exit()
    ip_info = ip['ip']
    print ip_info
    sendstr = 'user=' + user + '&ip=' + ip_info
    data = get_data(sendstr)
    data = json.loads(data)
    status = data['status']
    if status == 200:
        data = data['data']
        pack_data = data['packData']
        send_ip = data['sendIp']
        send_port = data['sendPort']
        import base64
        data = base64.b64decode(pack_data)
    else:
        log('ERROR: ' + time.asctime(time.localtime(time.time())) + 'GET DATA ERROR  code=' + data['message'] + '\r\n')
        exit()
    send_pack(data.strip(), send_ip, send_port)