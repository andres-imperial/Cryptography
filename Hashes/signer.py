import os, random, struct
import sys
from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_v1_5
from Crypto.Hash import SHA512
from base64 import b64encode, b64decode

##################################################
# Loads the RSA key object from the location
# @param keyPath - the path of the key
# @return - the RSA key object with the loaded key
##################################################
def loadKey(keyPath):

	# The RSA key
	key = None

	# Open the key file
	with open(keyPath, 'r') as keyFile:

		# Read the key file
		keyFileContent = keyFile.read()

		# Decode the key
		decodedKey = b64decode(keyFileContent)

		# Load the key
		key = RSA.importKey(decodedKey)

	# Return the key
	return key


##################################################
# Signs the string using an RSA private key
# @param sigKey - the signature key
# @param string - the string
##################################################
def digSig(sigKey, string):

	# return the signature of the file
	return sigKey.sign(string, '');
	pass

##########################################################
# Returns the file signature
# @param fileName - the name of the file
# @param privKey - the private key to sign the file with
# @return fileSig - the file signature
##########################################################
def getFileSig(fileName, privKey):

	# 1. Open the file
	with open(fileName, 'r') as sigFile:
		# 2. Read the contents
		sigFileContent = sigFile.read()
		# 3. Compute the SHA-512 hash of the contents
		sigHash = SHA512.new(sigFileContent).hexdigest()
		# 4. Sign the hash computed in 4. using the digSig() function
		# you implemented.
		# 5. Return the signed hash; this is your digital signature
		return digSig(privKey, sigHash)

	pass

###########################################################
# Verifies the signature of the file
# @param fileName - the name of the file
# @param pubKey - the public key to use for verification
# @param signature - the signature of the file to verify
##########################################################
def verifyFileSig(fileName, pubKey, signature):

	# 1. Read the contents of the input file (fileName)
	with open(fileName, 'r') as inputFile:
		inputFileContents = inputFile.read()
		# 2. Compute the SHA-512 hash of the contents
		dataHash = SHA512.new(inputFileContents).hexdigest()
		# 3. Use the verifySig function you implemented in
		# order to verify the file signature
		# 4. Return the result of the verification i.e.,
		# True if matches and False if it does not match
		return verifySig(dataHash, signature, pubKey)

	pass

############################################
# Saves the digital signature to a file
# @param fileName - the name of the file
# @param signature - the signature to save
############################################
def saveSig(fileName, signature):

	# Signature is a tuple with a single value.
	# Get the first value of the tuple, convert it
	# to a string, and save it to the file (i.e., indicated
	# by fileName)
	with open(fileName, 'w') as sigFile:
		sigFile.write(str(signature[0]))

	pass

###########################################
# Loads the signature and converts it into
# a tuple
# @param fileName - the file containing the
# signature
# @return - the signature
###########################################
def loadSig(fileName):

	# Open the file, read the signature string, convert it
	# into an integer, and then put the integer into a single
	# element tuple
	with open(fileName, 'r') as sigFile:
		return (int(sigFile.read()),)

	pass

#################################################
# Verifies the signature
# @param theHash - the hash
# @param sig - the signature to check against
# @param veriKey - the verification key
# @return - True if the signature matched and
# false otherwise
#################################################
def verifySig(theHash, sig, veriKey):

	# signature using the verify() function of the
	# key and return the result
	return veriKey.verify(theHash, sig)

	pass

#################################################
# Encrypts the signature with the file
# @param fileName - fileName to append signature
# to and encrypt
# @param sig - the signature to append
# @param key - the AES key
#################################################
def encryptFile(fileName, sig, key):
	ciphertext = None

	with open(fileName, 'a') as outFile:
		outFile.write("\nSignature starts:\n" + str(sig[0]))

	with open(fileName, 'r') as inFile:
		aesObj = AES.new(key, AES.MODE_CFB, 'cpsc 452 rules!!')
		ciphertext = aesObj.encrypt(inFile.read())

	with open(fileName, 'w') as outFile:
		outFile.write(ciphertext)

#################################################
# Encrypts the signature with the file
# @param fileName - fileName to append signature
# to and encrypt
# @param key - the AES key
# @return - the decrypted signature
#################################################
def decryptFile(fileName, key):
	plaintext = None
	sig = None

	with open(fileName, 'r') as inFile:
		aesObj = AES.new(key, AES.MODE_CFB, 'cpsc 452 rules!!')
		plaintext = aesObj.decrypt(inFile.read())

	sig = plaintext[plaintext.find("Signature starts:") + len("Signature starts:"):]
	plaintext = plaintext[:plaintext.find("Signature starts:") - 1]

	with open(fileName, 'w') as outFile:
		outFile.write(plaintext)

	return (int(sig),)

#################################################
# The main function
#################################################
def main():

	# Make sure that all the arguments have been provided
	if len(sys.argv) < 5:
		print "USAGE: " + sys.argv[0] + " <KEY FILE NAME> <SIGNATURE FILE NAME> <INPUT FILE NAME> <sign/verify> <AES KEY (optional)>"
		exit(-1)

	# The key file
	keyFileName = sys.argv[1]

	# Signature file name
	sigFileName = sys.argv[2]

	# The input file name
	inputFileName = sys.argv[3]

	# The mode i.e., sign or verify
	mode = sys.argv[4]

	# Save RSA key
	if len(sys.argv) == 6:
		aesKey = sys.argv[5]
	else:
		aesKey = None

	key = loadKey(keyFileName)

	# We are signing
	if mode == "sign":

		# 1. Get the file signature
		fileSig = getFileSig(inputFileName, key)
		#       2. Save the signature to the file
		saveSig(sigFileName, fileSig)
		#		3. If RSA key provided encrypt file with sig
		if len(sys.argv) == 6:
			if len(aesKey) == 16:
				encryptFile(inputFileName, fileSig, aesKey)
			else:
				print "Key size is incorrect, please use 16 byte key."

		print "Saved the signature of ", inputFileName, " to ", sigFileName

	# We are verifying the signature
	elif mode == "verify":

		# Use the verifyFileSig() function to check if the
	# Load the key using the loadKey() function provided.
		# signature signature in the signature file matches the
		# signature of the input file
		#3. If AES key provided encrypt file with sig
		if len(sys.argv) == 6:
			if len(aesKey) == 16:
				sig = decryptFile(inputFileName, aesKey)
				if verifyFileSig(inputFileName, key, sig) == True:
					print "Signatures match!"
				else:
					print "Signatures don't match!!!"
			else:
				print "Key size is incorrect, please use 16 byte key."

		elif verifyFileSig(inputFileName, key, loadSig(sigFileName)) == True:
			print "They match!"
		else:
			print "They dont match!!!"
		pass
	else:
		print "Invalid mode ", mode

### Call the main function ####
if __name__ == "__main__":
	main()
