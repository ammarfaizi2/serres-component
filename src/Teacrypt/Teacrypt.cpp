
#include <phpcpp.h>
#include <random>
#include <string>
#include <iostream>
#include "../headers/teacrypt_class.h"

#define SALT_LENGTH 3

std::string Teacrypt::encrypt(std::string data, std::string key) {
	
	std::string 
		salt = generateSalt(SALT_LENGTH),
		newKey = "",
		result = "";


	int 
		segmentKey = 1,
		segmentKey2 = 1,
		saltLength = SALT_LENGTH,
		dataLength = data.length(),
		keyLength  = key.length(),
		i = 0, j, cost_i = 0, 
		cost_j = 0, cost_k = 0,
		sumakey = 0, sumasalt = 0;

	for (; i < saltLength; ++i)
	{
		sumasalt += (int)salt[i];
		for (j = 0; j < keyLength; ++j)
		{
			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ i ^ j
			))[j+i+0];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ i ^ j
			))[j+i+1];

			sumakey += (int)(newKey += (char)(
				(int)key[j] ^ i ^ j
			))[j+i+2];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ i
			))[j+i+3];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ j
			))[j+i+4];
		}
	}

	keyLength = newKey.length();
	
	for (i = 0; i < dataLength; ++i)
	{
		cost_i += i;
		for (j = 0; j < keyLength; ++j)
		{
			cost_j += j;
			segmentKey = (
				(sumakey % (j+1)) ^ (sumakey % (i+1)) ^ (int)data[i] ^ 
				(int)newKey[j] ^ i ^ j ^ (dataLength % (j+1)) ^ (keyLength % (i+1) ^ 
				((sumakey << sumakey << i) % 0xff)) ^ ((sumakey << sumakey << j) % 0xff) ^
				((sumasalt << sumasalt << i) % 0xff) ^ ((sumasalt << sumasalt << j) % 0xff)
			);
			segmentKey2 = ((segmentKey2 << segmentKey) % (j+1));
		}
		cost_k += cost_i + cost_j + 1;
		result += segmentKey ^ segmentKey2 ^ ((cost_i << cost_j) % (i+1)) ^ ((cost_k >> cost_i << cost_j) % (i+2));
	}

	return result + salt;
}

std::string Teacrypt::decrypt(std::string data, std::string key) {

	int dataLength = data.length();

	std::string 
		salt = data.substr(dataLength - SALT_LENGTH, SALT_LENGTH),
		newKey = "",
		result = "";

	data = data.substr(0, dataLength - SALT_LENGTH);

	int 
		segmentKey = 1,
		segmentKey2 = 1,
		saltLength = SALT_LENGTH,
		keyLength  = key.length(),
		i = 0, j, cost_i = 0, 
		cost_j = 0, cost_k = 0,
		sumakey = 0, sumasalt = 0;
	
	dataLength = data.length();

	for (; i < saltLength; ++i)
	{
		sumasalt += (int)salt[i];
		for (j = 0; j < keyLength; ++j)
		{
			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ i ^ j
			))[j+i+0];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ i ^ j
			))[j+i+1];

			sumakey += (int)(newKey += (char)(
				(int)key[j] ^ i ^ j
			))[j+i+2];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ i
			))[j+i+3];

			sumakey += (int)(newKey += (char)(
				(int)salt[i] ^ (int)key[j] ^ j
			))[j+i+4];
		}
	}

	keyLength = newKey.length();
	
	for (i = 0; i < dataLength; ++i)
	{
		cost_i += i;
		for (j = 0; j < keyLength; ++j)
		{
			cost_j += j;
			segmentKey = (
				(sumakey % (j+1)) ^ (sumakey % (i+1)) ^ (int)data[i] ^ 
				(int)newKey[j] ^ i ^ j ^ (dataLength % (j+1)) ^ (keyLength % (i+1) ^ 
				((sumakey << sumakey << i) % 0xff)) ^ ((sumakey << sumakey << j) % 0xff) ^
				((sumasalt << sumasalt << i) % 0xff) ^ ((sumasalt << sumasalt << j) % 0xff)
			);
			segmentKey2 = ((segmentKey2 << segmentKey) % (j+1));
		}
		cost_k += cost_i + cost_j + 1;
		result += segmentKey ^ segmentKey2 ^ ((cost_i << cost_j) % (i+1)) ^ ((cost_k >> cost_i << cost_j) % (i+2));
	}

	return result;
}

std::string Teacrypt::generateSalt(std::string::size_type length)
{
    static int chrs[] = {
    	0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa
    };

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while(length--) {
        s += chrs[pick(rg)];
    }

    return s;
}
