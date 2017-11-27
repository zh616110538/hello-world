
/* This program demonstrates how to use hmac_md5() to
 *   generate a HMAC-MD5 digest
 */ 

void hmac_md5(unsigned char*  text, int text_len, unsigned char*  key,
	      int key_len, unsigned char* digest);  


/* 128-bit key used to generate HMAC */
static unsigned char key[16] = {
   0x4E, 0x46, 0xF8, 0xC5, 0x09, 0x2B, 0x29, 0xE2,
   0x9A, 0x97, 0x1A, 0x0C, 0xD1, 0xF6, 0x10, 0xFB
};

static char *data = "We want to generate hmac for this message.";

int main(int argc, char* argv[])
{
   int data_length;
   int i;
   unsigned char digest[16];

   data_length = strlen(data);
   hmac_md5(data, data_length, key, 16, digest);

   printf("HMAC: ");
   for (i=0; i<16; i++){
       printf("%02x ", digest[i]); 
   }
   printf("\n");

   return 0;
}
