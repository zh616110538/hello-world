# Makefile for lib/libcrypt.

CFLAGS	= -O -D_MINIX -D_POSIX_SOURCE -wo
CC1	= $(CC) $(CFLAGS) -c

LIBRARY	= ../libcrypt.a
all:	$(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(aes.o) \
	$(LIBRARY)(md5.o) \
	$(LIBRARY)(hmac_md5.o) \
	$(LIBRARY)(sha256.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(aes.o):	aes.c
	$(CC1) aes.c

$(LIBRARY)(md5.o):	md5.c
	$(CC1) md5.c

$(LIBRARY)(hmac_md5.o):	hmac_md5.c
	$(CC1) hmac_md5.c

$(LIBRARY)(sha256.o):	sha256.c
	$(CC1) sha256.c
