from socket import *
from time import ctime
import datetime

HOST = ''
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

tcpSerSock = socket(AF_INET, SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

while True:
    print('等待连接中')
    tcpCliSock, addr = tcpSerSock.accept()
    print('...connected from:', addr)

    while True:
        data = tcpCliSock.recv(BUFSIZ)
        #time_start = datetime.datetime.now().microsecond
        if not data:
            break

        #time_end = datetime.datetime.now().microsecond
        #print(time_end, time_start)
        #delay_time = time_end - time_start
        tcpCliSock.send(('[%s] 收到数据 %s' % (ctime(), data)).encode())

    tcpCliSock.close()
tcpSerSock.close()
