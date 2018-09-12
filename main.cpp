#include <iostream>
#include <sys/time.h>
#include "src/headers/teacrypt_class.h"
#include "src/Teacrypt/Teacrypt.cpp"

int	main(int argc, char const *argv[])
{
	struct timeval  tv1, tv2;
	
	gettimeofday(&tv1, NULL);

	std::string str = "qwertyuiopasdfghjklzzxcvbnmQWERTYUIOPSDFGHJKLZXCVBNM";
	std::string key = "ini kunci";
	for (int i = 0; i < 5000; ++i)
	{
		std::string a = Teacrypt::encrypt(str, key);
		std::string b = Teacrypt::decrypt(a, key);

		std::cout << i << std::endl;
		if (b != str)
		{
			std::cerr << "Error!" << std::endl;
			return 1;
		}
	}

	gettimeofday(&tv2, NULL);

	std::cout << "Success!" << std::endl << "C++ test" << std::endl << ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec)) << " seconds" << std::endl;

	return 0;
}
