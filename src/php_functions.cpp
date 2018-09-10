
#include <iostream>
#include <phpcpp.h>
#include "headers/teacrypt_class.h"

Php::Value teaEncrypt(Php::Parameters &params) {
	return Teacrypt::encrypt(params[0], params[1], params[3]);
}
