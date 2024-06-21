#include "User.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include <iostream>

// ------------------------ basic tests -----------------------------//
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
// 	channel1.setTopicOn("This channel talks about the weather");
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

// int main()
// {
// 	UserManager userManager;

// 	struct pollfd pfdsArr[10];
// 	int arrSize = 10;

// 	// initialisation of pfdsArr
// 	for (int i = 0; i < arrSize; i++)
// 	{
// 		pfdsArr[i].fd = i;
// 	}

// 	User user1("User1");
// 	User user2("User2");
// 	User user3("User3");

// 	std::string message = "Hello User1";

// 	std::cout << "Preparation envoi message from" << user3.getNickname() << std::endl;

// 	userManager.sendToOne(user3, message, pfdsArr, arrSize);
// 	std::cout << "Message envoye" << std::endl;

// 	// userManager.addUser(user1, 2);
// 	// userManager.addUser(user2, 3);

// 	// std::map<std::string, int> socketMap = userManager.getSocketMap();

// 	return 0;
// }

// ------------------------ test channels -----------------------------//


int main()
{
	// Création d'un Channel
	std::string channelName("TechTalk");
	Channel techTalkChannel(channelName);

	// Création du ChannelManager
	ChannelManager channelManager;

	// Création d'utilisateurs
	User alice("Alice");
	User bob("Bob");

	// Ajout d'utilisateurs au Channel via ChannelManager
	techTalkChannel.addUser(alice.getNickname());
	techTalkChannel.addUser(bob.getNickname());

	// Affichage des utilisateurs du Channel
	std::cout << "Utilisateurs dans le channel " << techTalkChannel.getName() << ": ";
	std::vector<std::string> users = techTalkChannel.getUsers();
	for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Ajout d'opérateurs et d'invitations
	channelManager.addOperator(channelName, alice);
	channelManager.inviteUser(channelName, bob);

	// Vérification des rôles et des invitations
	if (channelManager.isUserOperator(channelName, alice))
	{
		std::cout << alice.getNickname() << " est un opérateur du channel " << channelName << std::endl;
	}

	if (channelManager.isUserInvited(channelName, bob))
	{
		std::cout << bob.getNickname() << " est invité au channel " << channelName << std::endl;
	}

	// Gestion des sujets
	std::string topic("Nouvelles Technologies");
	channelManager.setTopicOn(channelName, topic);
	std::cout << "Le sujet du channel " << channelName << " est : " << channelManager.getTopic(channelName) << std::endl;

	// Gestion des limites d'utilisateurs
	int limit = 5;
	channelManager.setLimit(channelName, limit);
	if (!channelManager.isLimitReached(channelName))
	{
		std::cout << "La limite d'utilisateurs pour le channel " << channelName << " n'est pas atteinte." << std::endl;
	}

	return 0;
}
