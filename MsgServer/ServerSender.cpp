#include"ServerSenderr.h"


HttpMessage ServerSender::makeMessage(size_t n, const std::string& body, const EndPoint& ep)
{
	HttpMessage msg;
	HttpMessage::Attribute attrib;
	EndPoint myEndPoint = "localhost:8080";  // ToDo: make this a member of the sender
											 // given to its constructor.
	msg.clear();
	switch (n)
	{
	case 1:
		msg.addAttribute(HttpMessage::attribute("GET", "Ack-Upload"));
		break;
	case 2:
		msg.addAttribute(HttpMessage::attribute("GET", "Ack-Download"));
		break;
	case 3:
		msg.addAttribute(HttpMessage::attribute("GET", "Ack-PUBLISH"));
		break;
	case 4:
		msg.addAttribute(HttpMessage::attribute("GET", "Ack-DOWNLOAD"));
		break;
	case 5:
		msg.addAttribute(HttpMessage::attribute("GET", "Exception"));
		break;
	default:
		msg.clear();
		msg.addAttribute(HttpMessage::attribute("Error", "unknown message type"));
	}
	msg.addAttribute(HttpMessage::Attribute("mode", "oneway"));
	msg.addAttribute(HttpMessage::parseAttribute("toAddr:" + ep));
	msg.addAttribute(HttpMessage::parseAttribute("fromAddr:" + myEndPoint));
	msg.addBody(body); // the above strings are passed byte by byte through http message
	if (body.size() > 0)
	{
		attrib = HttpMessage::attribute("content-length", Converter<size_t>::toString(body.size()));
		msg.addAttribute(attrib);
	}

	return msg;
}


bool ServerSender::sendFile(const std::string& filename, Socket& socket)
{
	// assumes that socket is connected

	std::string fqname = "../ServerRepository/" + filename;
	FileSystem::FileInfo fi(fqname);
	size_t fileSize = fi.size(); //Size
	std::string sizeString = Converter<size_t>::toString(fileSize); //convert size to string
	FileSystem::File file(fqname);
	file.open(FileSystem::File::in, FileSystem::File::binary);
	if (!file.isGood())
		return false;

	HttpMessage msg = makeMessage(1, "", "localhost::8081");
	msg.addAttribute(HttpMessage::Attribute("file", filename));
	msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
	sendMessage(msg, socket);
	const size_t BlockSize = 2048;
	Socket::byte buffer[BlockSize];
	while (true)
	{
		FileSystem::Block blk = file.getBlock(BlockSize);
		if (blk.size() == 0)
			break;
		for (size_t i = 0; i < blk.size(); ++i)
			buffer[i] = blk[i];
		socket.send(blk.size(), buffer);
		if (!file.isGood())
			break;
	}
	file.close();
	return true;
}

//----< send message using socket >----------------------------------

void ServerSender::sendMessage(HttpMessage& msg, Socket& socket)
{
	std::string msgString = msg.toString();
	socket.send(msgString.size(), (Socket::byte*)msgString.c_str());
}

//----< this defines the behavior of the client >--------------------

void ServerSender::execute(const size_t TimeBetweenMessages, const size_t NumMessages)
{
	// send NumMessages messages
	std::cout << "Sending message from " << std::endl;
	try
	{
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", 8080)) //if the server isn't connected to the client on that port then the client sleeps
		{
			Show::write("\n server waiting to connect");
			::Sleep(100);
		}

		// send a set of messages

		HttpMessage msg;
			std::string msgBody =
				"<msg>Message # Test message from Server from Server # </msg>"; //myCounterString 
			
			msg = makeMessage(1, msgBody, "localhost:8080");
			/*
			* Sender class will need to accept messages from an input queue
			* and examine the toAddr attribute to see if a new connection
			* is needed.  If so, it would either close the existing connection
			* or save it in a map[url] = socket, then open a new connection.
			*/
			sendMessage(msg, si);
			Show::write("\n\n  server sent\n" + msg.toIndentedString()); //enqueqe into the blocking queue //Client Client Number sent and the messgae sent
			::Sleep(TimeBetweenMessages);

		//  send all *.cpp files from TestFiles folder

		std::vector<std::string> files = FileSystem::Directory::getFiles("../ServerRepository", "*.htm");
		for (size_t i = 0; i < files.size(); ++i)
		{
			Show::write("\n\n  sending file " + files[i]); //to blocking queue
			sendFile(files[i], si);
		}

		// shut down server's client handler

		msg = makeMessage(5, "quit", "toAddr:localhost:8080");
		sendMessage(msg, si);
		Show::write("\n\n server  sent\n" + msg.toIndentedString());

		Show::write("\n");
		Show::write("\n  All done folks");
	}
	catch (std::exception& exc)
	{
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}

