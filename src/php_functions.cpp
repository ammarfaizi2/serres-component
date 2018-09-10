
#include <iostream>
#include <phpcpp.h>

Php::Value teaEncrypt(Php::Parameters &params) {
	std::string data = params[0];
	std::string key  = params[1];
	return data + key;
}
