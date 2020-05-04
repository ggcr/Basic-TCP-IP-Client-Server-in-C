## TCP Server-Client in C

#### Usage
Compile the whole project with the Makefile:
```
$  make
```
The client will send a custom-size BUFFER from text.txt with stdin:

Client:
```
$  ./client-c [127.0.0.1] [port number] < [txt file with the input]
```

Server:
```
$  ./server-c [port number]
```

This assignment was part of COS-461, Spring 2020: Computer Networks by the Princeton University.
