/*
Even though Boost.Asio is a library that can process any kind of data 
asynchronously, it is mainly being used for network programming. This is 
due to the fact that Boost.Asio supported network functions long before 
additional I/O objects were added over time. Network functions are a 
perfect example for asynchronous processing since the transmission of data 
within a network may take longer and thus acknowledges as well as error 
conditions are not directly available.

Boost.Asio provides many I/O objects to develop network applications. The 
following example uses the boost::asio::ip::tcp::socket class to establish 
a connection to a different PC and download the 'Highscore' homepage; just 
like a browser does when pointed to www.highscore.de.
*/

#include <boost/asio.hpp> 
#include <boost/array.hpp> 
#include <iostream> 
#include <string> 

boost::asio::io_service io_service; 
boost::asio::ip::tcp::resolver resolver(io_service); 
boost::asio::ip::tcp::socket sock(io_service); 
boost::array<char, 4096> buffer; 

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
  if (!ec) 
  { 
    std::cout << std::string(buffer.data(), bytes_transferred) << std::endl; 
    sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
  } 
} 

void connect_handler(const boost::system::error_code &ec) 
{ 
  if (!ec) 
  { 
    boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n")); 
    sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
  } 
} 

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) 
{ 
  if (!ec) 
  { 
    sock.async_connect(*it, connect_handler); 
  } 
} 

int main() 
{ 
  boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80"); 
  resolver.async_resolve(query, resolve_handler); 
  io_service.run(); 
} 

/*
The most obvious part of the application is the usage of three handlers: 
The connect_handler() and read_handler() functions are called once the 
connection has been established and while data are being received, 
respectively. Why is the resolve_handler() function required though?

The Internet uses so-called IP addresses to identify individual PCs. IP 
addresses are essentially just a lengthy number that is hard to remember. 
It is much easier to remember names such as www.highscore.de instead. In 
order to use such a name for the Internet, it needs to be translated into 
the corresponding IP address via a process called name resolution. The 
process is accomplished by a so-called name resolver which explains the 
name of the corresponding I/O object: boost::asio::ip::tcp::resolver.

Name resolution is a process that requires a connection to the Internet as 
well. Dedicated PCs, called DNS servers, act just like a phone book and 
know what IP address is assigned to an individual PC. Since the process 
itself is transparent, it is only important to understand the concept 
behind it and why the boost::asio::ip::tcp::resolver I/O object is 
therefore required. Since name resolution does not take place locally, it 
is also implemented as an asynchronous operation. The resolve_handler() 
function is called once the name resolution has either succeeded or 
terminated with an error.

Since receiving data presumes a successful connection which in turn presumes
a successful name resolution, different asynchronous operations are started 
within the individual handlers. resolve_handler() accesses the I/O object 
sock to create a connection using the resolved address provided by the 
iterator it. sock is also being accessed inside of connect_handler() to 
send the HTTP request and to initiate the data reception. Since all of 
these operations are asynchronous, the names of the individual handlers are 
being passed as arguments. Depending on the corresponding handler, 
additional arguments are required such as the iterator it pointing to the 
resolved address or the buffer buffer storing the received data.
*/

/*
Once executed, the application creates an object query of type 
boost::asio::ip::tcp::resolver::query that represents a query containing 
the name www.highscore.de and the, in the Internet commonly used, port 80. 
This query is passed to the async_resolve() method to resolve the name. 
Finally, main() simply calls the run() method of the I/O service to 
transfer control over the asynchronous operations to the operating system.

Once the name resolution process has finished, resolve_handler() is called 
which checks whether or not the name could be resolved. If successfully 
resolved, the object ec, containing the various error conditions, is set to 
0. Only in this case, the socket is accessed to create a connection 
accordingly. The server address is provided via the second argument of type 
boost::asio::ip::tcp::resolver::iterator.

After calling the async_connect() method, connect_handler() is called 
automatically. Inside the handler, the ec object is evaluated to check 
whether or not a connection has been established. In case a connection is 
available, the async_read_some() method is called for the corresponding 
socket which initiates the read operation. To store the received data, a 
buffer is provided as the first argument. In the given example, it is of 
type boost::array which is part of the Boost C++ Library Array and is 
defined in boost/array.hpp.

The read_handler() function is called every time one or more bytes have 
been received and stored within the buffer. The exact number of bytes 
received is given via the argument bytes_transferred which is of type 
std::size_t. As is the rule, the handler should first evaluate the argument 
ec to check for any reception error. If successfully received, the data is 
simply written to the standard output stream.
*/

/*
Please note that read_handler() calls the async_read_some() method again 
once the data has been written via std::cout. This is necessary since there 
is no guarantee that the whole homepage has been received with just one 
single asynchronous operation. The alternating calls of async_read_some() 
and read_handler() only stop if the connection has been disrupted, e.g. when
the web server has transmitted the complete homepage. In this case, an 
error is reported inside read_handler() which prevents further data output 
on the standard output stream as well as further invocations of the 
async_read() method for this particular socket. The example application 
will actually terminate since no further asynchronous operations are 
outstanding.
*/

/*
While the previous example was used to retrieve the homepage of 
www.highscore.de, the next example actually illustrates a simple web server.
The crucial difference is that the application does not connect to other 
PCs but rather waits for incoming connections.
*/

//#include <boost/asio.hpp> 
//#include <string> 
//
//boost::asio::io_service io_service; 
//boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80); 
//boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint); 
//boost::asio::ip::tcp::socket sock(io_service); 
//std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"; 
//
//void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
//{ 
//} 
//
//void accept_handler(const boost::system::error_code &ec) 
//{ 
//  if (!ec) 
//  { 
//    boost::asio::async_write(sock, boost::asio::buffer(data), write_handler); 
//  } 
//} 
//
//int main() 
//{ 
//  acceptor.listen(); 
//  acceptor.async_accept(sock, accept_handler); 
//  io_service.run(); 
//}

/*
The I/O object acceptor of type boost::asio::ip::tcp::acceptor - initialized
with the protocol and the port - is used to wait for incoming connections 
from other PCs. The initialization happens via the endpoint object which 
is of type boost::asio::ip::tcp::endpoint and configures the acceptor in 
the example to use port 80 to wait for incoming connections of version 4 
of the Internet protocol which is typically the port and protocol used for 
the WWW.

After initializing the acceptor, main() first calls the listen() method to 
put the acceptor into receive mode before it waits for the initial 
connection using the async_accept() method. The socket used to send and 
receive data is passed as the first argument.

Once a PC tries to establish a connection, accept_handler() is called 
automatically. If the connection request was successful, the free-standing 
boost::asio::async_write() function is invoked to send the information 
stored in data via the socket. boost::asio::ip::tcp::socket also provides 
a method named async_write_some() to send data; however, it will invoke the 
associated handler whenever at least one byte has been sent. The handler 
would need to calculate how many bytes are left to send and invoke 
async_write_some() repeatedly until all bytes have been sent. This can 
be avoided by using boost::asio::async_write() since this asynchronous 
operation only terminates after all bytes of the buffer have been sent.

Once all data has been sent, the empty function write_handler() is called 
in this example. Since all asynchronous operations have finished, the 
application is terminated. The connection to the other PC is closed accordingly.
*/