#include <iostream>
#include "TestExecutive.h"

/*int main(int argc, char * argv[])
{
	argc = 5;
	argv[0] = "Upload";
	argv[1] = "Category3";
	argv[2] = "..\\files\\";
	argv[3] = "*.h";
	argv[4] = "*.cpp";
	std::cout << "Upload function" << std::endl;
	MsgClient c1;
	//c1.cparguments(argc, argv);
	std::thread t1(
		[&]() { c1.execute(100, 1); }
	);
	t1.join();
	BlockingQueue<HttpMessage> clientReceiverQ_;
	try
	{
		SocketListener sl(8081, Socket::IP6);      //client listens to the server
		ClientReceiver receiver(clientReceiverQ_);
		sl.start(receiver);
		while (true)
		{
			HttpMessage msg = clientReceiverQ_.deQ();    //BlockingQueue.h
			Show::write("\n\n  Client received message with body contents:\n" + msg.bodyString());
		}
	}
	catch (std::exception& exc)
	{
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}*/