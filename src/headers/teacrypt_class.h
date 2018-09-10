
#ifndef __TEACRYPT_CLASS_H
#define __TEACRYPT_CLASS_H 1

class Teacrypt {
	public:
		static std::string encrypt(std::string, std::string);
		static std::string decrypt(std::string, std::string);
	private:
		static std::string generateSalt(std::string::size_type);
};

#endif
