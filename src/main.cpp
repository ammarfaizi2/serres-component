
#include <phpcpp.h>
#include <iostream>
#include "headers/teacrypt_php_function.h"

extern "C" {
	PHPCPP_EXPORT void *get_module() {
		static Php::Extension extension("teacrypt", "1.0");
		extension.add<teaEncrypt>("teaEncrypt", {
			Php::ByVal("data", Php::Type::String),
			Php::ByVal("key", Php::Type::String),
			Php::ByVal("isBinarySafe", Php::Type::Bool, false)
		});
		return extension;
	}
}
