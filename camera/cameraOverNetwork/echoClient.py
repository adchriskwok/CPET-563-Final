import socket 

host = '192.168.0.31' 
port = 65432 
size = 1024 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((host,port)) 
s.send('Hello, world') 
data = s.recv(size) 
s.close() 
print 'Received:', data