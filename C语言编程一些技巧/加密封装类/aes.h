#ifndef _AES_H
#define _AES_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

namespace aes {
	typedef struct aes_context
	{
		uint32 erk[64];     /* encryption round keys */
		uint32 drk[64];     /* decryption round keys */
		int nr;             /* number of rounds */
	}
	aes_context;

	int  aes_set_key(aes_context *ctx, uint8 *key, int nbits);
	void aes_encrypt(aes_context *ctx, uint8 input[16], uint8 output[16]);
	void aes_decrypt(aes_context *ctx, uint8 input[16], uint8 output[16]);
	
	class Encrypt {
	public:
		Encrypt();
		~Encrypt();
		void encrypt(std::vector<unsigned char>&, std::vector<unsigned char>&);
		void decrypt(std::vector<unsigned char>&, std::vector<unsigned char>&);
		void encrypt_file(std::string&, std::string&);
		void decrypt_file(std::string&, std::string&);
	private:
		aes_context *ctx;
		static unsigned char secret_key[32];
		const int textsize = 16;
		void readfile(std::string filename, std::vector<unsigned char>&);
		void writefile(std::string filename, std::vector<unsigned char>&);
	};

}
#endif /* aes.h */
