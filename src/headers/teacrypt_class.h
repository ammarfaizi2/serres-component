
#ifndef __TEACRYPT_CLASS_H
#define __TEACRYPT_CLASS_H 1

class Teacrypt {
	public:
		static std::string encrypt(std::string, std::string, bool);
		static std::string decrypt(std::string, std::string, bool);
};

#endif
