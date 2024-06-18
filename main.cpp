#include "User.hpp"
#include "Channel.hpp"

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

#include "Server.hpp"

int	main(int ac, char **av)
{
	Server	server(ac, av);

	if (server.errToggle == true)
		return (1);
	try
	{
		server.run();
	}
	catch (const char *e)
	{
		// std::cout << e << std::endl;
		perror(e);
	}
	return (0);
}
