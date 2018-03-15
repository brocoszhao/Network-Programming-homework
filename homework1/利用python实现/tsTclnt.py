from socket import *
import time

HOST = '127.0.0.1'
PORT = 21567
BUFSIZ = 1024
ADDR =(HOST, PORT)

tcpCliSock = socket(AF_INET, SOCK_STREAM)
tcpCliSock.connect(ADDR)

while True:
    data = input()
    if not data:
        break
    time_start = time.time()
    tcpCliSock.send(data.encode())
    data = tcpCliSock.recv(BUFSIZ).decode()
    time_end = time.time()
    delay_time = time_end - time_start
    if not data:
        break
    print('延迟时长为 %s' % delay_time)

tcpCliSock.close()