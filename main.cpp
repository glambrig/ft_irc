#include "User.hpp"

int main()
{
	User user;
	user.setUsername("FirstUser");
	std::cout << user.getUsername() << std::endl;

	user.setPassword("1234");
	user.setSocket(42);
	return (0);
}
