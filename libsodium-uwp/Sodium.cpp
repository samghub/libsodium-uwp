#include "pch.h"
#include "Sodium.h"

using namespace Sodium;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::Security::Cryptography;
using namespace Windows::Security::Cryptography::Core;
using namespace Windows::Storage::Streams;

// Returns the libsodium version string
String^ Sodium::Core::SodiumVersionString()
{
	return SODIUM_VERSION_STRING;
}

// Returns count number of random bytes
Array<unsigned char>^ Sodium::Core::GetRandomBytes(int count)
{
	Array<unsigned char>^ nonce = ref new Array<unsigned char>(count);
	randombytes_buf(nonce->Data, nonce->Length);
	return nonce;
}

// Returns a random number with an upper bound of upper_count
int Sodium::Core::GetRandomNumber(int upper_count)
{
	return randombytes_uniform(upper_count);
}

// Generates a SecretBox Nonce
Array<unsigned char>^ Sodium::SecretBox::GenerateNonce()
{
	return Sodium::Core::GetRandomBytes(crypto_secretbox_NONCEBYTES);
}

// Returns a SecretBox key
Array<unsigned char>^ Sodium::SecretBox::GenerateKey()
{
	return Sodium::Core::GetRandomBytes(crypto_secretbox_KEYBYTES);
}

Array<unsigned char>^ Sodium::SecretBox::Create(const Array<unsigned char>^ message, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key)
{
	if (key->Length != crypto_secretbox_KEYBYTES) {
		throw ref new Platform::Exception(1, "Key must be {0} bytes in length");
	}

	if (nonce->Length != crypto_secretbox_NONCEBYTES) {
		throw ref new Platform::Exception(1, "Nonce must be {0} bytes in length");
	}

	int cipherLength = crypto_secretbox_MACBYTES + message->Length;
	Array<unsigned char>^ cipherText = ref new Array<unsigned char>(cipherLength);
	int result = crypto_secretbox_easy(
		cipherText->Data,
		message->Data,
		message->Length,
		nonce->Data,
		key->Data
	);

	if (result == 0) {
		return cipherText;
	}

	throw ref new Platform::Exception(result, "Unable to create SecretBox.");
}

Array<unsigned char>^ Sodium::SecretBox::Open(const Array<unsigned char>^ ciphertext, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key)
{
	if (key->Length != crypto_secretbox_KEYBYTES) {
		throw ref new Platform::Exception(1, "Key must be {0} bytes in length");
	}

	if (nonce->Length != crypto_secretbox_NONCEBYTES) {
		throw ref new Platform::Exception(1, "Nonce must be {0} bytes in length");
	}

	int cipherLength = ciphertext->Length - crypto_secretbox_MACBYTES;
	Array<unsigned char>^ message = ref new Array<unsigned char>(cipherLength);
	int result = crypto_secretbox_open_easy(
		message->Data,
		ciphertext->Data,
		ciphertext->Length,
		nonce->Data,
		key->Data
	);

	if (result == 0) {
		return message;
	}

	throw ref new Platform::Exception(result, "Unable to open SecretBox.");
}

Array<unsigned char>^ Sodium::SecretKeyAuth::GenerateKey()
{
	return Sodium::Core::GetRandomBytes(crypto_secretbox_KEYBYTES);
}

Array<unsigned char>^ Sodium::SecretKeyAuth::Sign(const Array<unsigned char>^ message, const Array<unsigned char>^ key)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SecretKeyAuth::Verify(const Array<unsigned char>^ message, const Array<unsigned char>^ signature, const Array<unsigned char>^ key)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

// Generates a SecretAEAD Nonce
Array<unsigned char>^ Sodium::SecretAead::GenerateNonce()
{
	return Sodium::Core::GetRandomBytes(8);
}

Array<unsigned char>^ Sodium::SecretAead::Encrypt(const Array<unsigned char>^ message, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SecretAead::Encrypt(const Array<unsigned char>^ message, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key, const Array<unsigned char>^ additionaData)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SecretAead::Decrypt(const Array<unsigned char>^ encrypted, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SecretAead::Decrypt(const Array<unsigned char>^ encrypted, const Array<unsigned char>^ nonce, const Array<unsigned char>^ key, const Array<unsigned char>^ additionaData)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SealedPublicKeyBox::Create(const Array<unsigned char>^ message, const Array<unsigned char>^ recipientPublicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SealedPublicKeyBox::Create(const Array<unsigned char>^ message, KeyPair ^ recipientPublicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SealedPublicKeyBox::Open(const Array<unsigned char>^ cipherText, const Array<unsigned char>^ recipientSecretKey, const Array<unsigned char>^ recipientPublicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::SealedPublicKeyBox::Open(const Array<unsigned char>^ cipherText, KeyPair ^ recipientPublicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

// Generates a Crypto Box Nonce
Array<unsigned char>^ Sodium::PublicKeyBox::GenerateNonce()
{
	return Sodium::Core::GetRandomBytes(crypto_box_NONCEBYTES);
}

KeyPair^ Sodium::PublicKeyBox::GenerateKeyPair()
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

KeyPair^ Sodium::PublicKeyBox::GenerateKeyPair(const Array<unsigned char>^ privateKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyBox::Create(const Array<unsigned char>^ message, const Array<unsigned char>^ nonce, const Array<unsigned char>^ secretKey, const Array<unsigned char>^ publicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyBox::Open(const Array<unsigned char>^ cipherText, const Array<unsigned char>^ nonce, const Array<unsigned char>^ secretKey, const Array<unsigned char>^ publicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

KeyPair ^ Sodium::PublicKeyAuth::GenerateKeyPair()
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

KeyPair ^ Sodium::PublicKeyAuth::GenerateKeyPair(const Array<unsigned char>^ privateKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyAuth::Sign(const Array<unsigned char>^ message, const Array<unsigned char>^ privateKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyAuth::Verify(const Array<unsigned char>^ signedMessage, const Array<unsigned char>^ publicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyAuth::ConvertEd25519PublicKeyToCurve25519PublicKey(const Array<unsigned char>^ publicKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

Array<unsigned char>^ Sodium::PublicKeyAuth::ConvertEd25519SecretKeyToCurve25519SecretKey(const Array<unsigned char>^ privateKey)
{
	throw ref new Platform::NotImplementedException();
	// TODO: insert return statement here
}

// Creates a Sha256 hash
Array<unsigned char>^ Sodium::CryptoHash::Sha256(const Array<unsigned char>^ message)
{
	Array<unsigned char>^ buffer = ref new Array<unsigned char>(crypto_hash_sha256_BYTES);
	int result = crypto_hash_sha256(buffer->Data, message->Data, message->Length);

	if (result == 0) {
		return buffer;
	}

	throw ref new Platform::Exception(result, "Unable to generate Sha256 hash");
}

// Creates a Sha512 hash
Array<unsigned char>^ Sodium::CryptoHash::Sha512(const Array<unsigned char>^ message)
{
	Array<unsigned char>^ buffer = ref new Array<unsigned char>(crypto_hash_sha512_BYTES);
	int result = crypto_hash_sha512(buffer->Data, message->Data, message->Length);

	if (result == 0) {
		return buffer;
	}

	throw ref new Platform::Exception(result, "Unable to generate Sha512 hash");
}