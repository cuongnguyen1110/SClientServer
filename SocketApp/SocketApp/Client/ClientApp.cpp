// SocketApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Client.h"
int main()
{
    std::cout << "Welcome to 5s Client\n";
	
    Client* mClient = new Client();
	bool connected = mClient->ConnectToServer();
	if (!connected)
	{
		printf("ERROR: Fail to connect server. EXIT! \n");
		exit(-1);
	}
	else
	{
		printf("Connect server successfull \n");
	}

	std::cout << "Enter 'quit' to quit application \n";

    bool run = true;
    while(run)
    {
        std::string input;
        std::cout<<"Command:";
        std::cin>>input;
        if(input == std::string("quit") )
        {
            run = false;
        }
		else
		{
			std::cout << "Sending message to Server: " << input << "\n";
			int size = input.size();
			mClient->SendToServer((char*)input.data(), size);
		}
        
    }
    
    delete mClient;

    std::cout<<"Server shut down \n";
    
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
