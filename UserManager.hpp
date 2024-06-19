#include "User.hpp"

class UserManager
{
	private:
		std::map<std::string, int> socketMap;

	public:
		UserManager();
		UserManager(const UserManager& copy);
		UserManager& operator=(const UserManager& rhs);
		~UserManager();

		std::map<std::string, int>	getSocketMap() const;
		void sendToOne(User user, std::string message, struct pollfd *pfdsArr, int arrSize);

		void				addUser(User user, int socket);
		void				removeUser(User user);
};
