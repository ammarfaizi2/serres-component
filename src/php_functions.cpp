
#include <iostream>
#include <phpcpp.h>
#include "headers/teacrypt_class.h"

Php::Value teaEncrypt(Php::Parameters &params) {
	
	std::string encryptedData = Teacrypt::encrypt(params[0], params[1]);


	Php::out << "output: ";
	Php::out << (int)params[3];

	if (params[3])
	{
		return Php::call("base64_encode", encryptedData);
	}
	return params[3];
}

Php::Value teaDecrypt(Php::Parameters &params) {
	return Teacrypt::encrypt(params[0], params[1]);
}
