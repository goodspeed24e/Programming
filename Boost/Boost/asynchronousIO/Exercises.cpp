
1. Modify the server from Section 7.4, “Network Programming” to prevent it 
from terminating after a single request but rather processes an 
arbitrary number.

2. Extend the client from Section 7.4, “Network Programming” to immediately 
parse the received HTML code for a URL. If found, the corresponding resource
should be downloaded as well. For this exercise, the first URL found should 
be utilized. Ideally, the website as well as the resource should be saved 
in two files rather than writing both to the standard output stream.

3. Create a client/server application to transmit a file between two PCs. 
Once the server is started, it should display the IP addresses of all 
local interfaces and wait for client connections. One of the available 
server IP addresses as well as the name of a local file should be passed to 
the client as command-line arguments. The client should transmit the file 
to the server which in turn saves it accordingly. While transmitting, the 
client should provide some visual indication of the progress to the user.
