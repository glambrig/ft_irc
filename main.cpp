#include "User.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include <iostream>

// int main()
// {
// 	User user1, user2, user3, user4, user5, user6, user7;
// 	user1.setUsername("FirstUser");
// 	user2.setUsername("SecondUser");
// 	user3.setUsername("ThirdUser");
// 	user4.setUsername("FourthUser");
// 	user5.setUsername("FifthUser");
// 	user6.setUsername("SixthUser");
// 	user7.setUsername("SeventhUser");

// 	Channel channel1, channel2, channel3;
// 	channel1.setName("FirstChannel");
// 	channel2.setName("SecondChannel");
// 	channel3.setName("ThirdChannel");

// 	channel1.setKey("2345");
// 	channel1.setTopic("This channel talks about the weather");
// 	channel1.addUser("SecondUser");
// 	channel1.addUser("ThirdUser");

// 	//display channel1 information
// 	std::cout << "Channel name: " << channel1.getName() << std::endl;
// 	std::cout << "Channel topic: " << channel1.getTopic() << std::endl;
// 	std::cout << "Channel users: " << channel1.getUsers() << std::endl;
// 	std::cout << "User added:" << channel1.addUser("FifthUser") << std::endl;
// 	std::cout << "Channel users: " << channel1.getUsers() << std::endl;
// 	std::cout << "User removed:" << channel1.removeUser("SecondUser") << std::endl;
// 	std::cout << "Channel users: " << channel1.getUsers() << std::endl;
// 	std::cout << "Check User connection: " << channel1.isUserInChannel("ThirdUser") << std::endl;
// 	std::cout << "Check User connection: " << channel1.isUserInChannel("SecondUser") << std::endl;
// 	return (0);
// }

// -------------------------------------------------------------------//

// int	main(int ac, char **av)
// {
// 	Server	server(ac, av);

// 	if (server.errToggle == true)
// 		return (1);
// 	server.run();
// 	return (0);
// }

// -------------------------------------------------------------------//

int main()
{
	UserManager userManager;

	struct pollfd pfdsArr[10];
	int arrSize = 10;

	// initialisation of pfdsArr
	for (int i = 0; i < arrSize; i++)
	{
		pfdsArr[i].fd = i;
	}

	User user1("User1");
	std::string message = "Hello User1";

	std::cout << "Preparation envoi message " << user1.getNickname() << std::endl;
	userManager.sendToOne(user1, message, pfdsArr, arrSize);
	std::cout << "Message envoye" << std::endl;

	// userManager.addUser(user1, 2);
	// userManager.addUser(user2, 3);

	// std::map<std::string, int> socketMap = userManager.getSocketMap();

	return 0;
}
