#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

// Function declarations
void AddRoundKey(unsigned char *state, unsigned char *roundKey);
void SubBytes(unsigned char *state);
void ShiftRows(unsigned char *state);
void MixColumns(unsigned char *state);
void Round(unsigned char *state, unsigned char *key);
void FinalRound(unsigned char *state, unsigned char *key);
void AESEncrypt(unsigned char *message, unsigned char *expandedKey, unsigned char *encryptedMessage);
void KeyExpansion(unsigned char inputKey[16], unsigned char expandedKeys[176]);
void KeyExpansionCore(unsigned char * in, unsigned char i);
#endif // ENCRYPT_H

