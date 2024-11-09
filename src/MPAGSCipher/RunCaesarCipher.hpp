#ifndef MPAGSCIPHER_RUNCAESARCIPHER_HPP
#define MPAGSCIPHER_RUNCAESARCIPHER_HPP

#include <string>

std::string runCaesarCipher(const std::string& inTxt, const size_t key, const bool mode);

#endif