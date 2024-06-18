#include "User.hpp"

class UserManager
{
	private:
		std::vector<User>	users;

	public:
		UserManager();
		UserManager(const UserManager& copy);
		UserManager& operator=(const UserManager& rhs);
		~UserManager();

		std::vector<User>	getUsers() const;

		void				addUser(User user);
		void				removeUser(User user);
};
