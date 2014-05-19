// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "..\game_lib\net_msg.h"
#include <thread>
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::thread> threads;
	for(int i = 0; i < 1000; ++i)
	{
		threads.push_back(std::thread([=](){

			ClientSocket sock;
			sock.Init();
			if (sock.Create() == false)
			{
				cout<<"create sock fail"<<endl;
				return ;
			}
			if (sock.Connect("192.168.1.109", 11111)==false)
			{
				cout<<"connect sock fail"<<endl;
				return ;
			}

			while (true)
			{
				tagnc_playerAuthSession msg;
				msg.playerID = i;
				sock.Send((char*)&msg, msg.size);
				std::this_thread::sleep_for(chrono::milliseconds(50));
			}
			sock.Close();
			sock.Clean();

		}));

	}
	for(auto& thread : threads)
	{
		thread.join();
	}
	
	return 0;
}

