#!/bin/bash

# Other options for generating the 1 gig file:
#dd if=/dev/urandom of=demo1G.bin bs=1G count=1 iflag=fullblock
#head -c 1G /dev/urandom > demo1G.bin

# Generate a random 1 gigabyte file
openssl rand -out demo1G.bin -base64 $(( 2**30 * 3/4 ))

#############
#### DES ####
#############

# Record the time that it takes to encrypt a 1 gig file with DES
time openssl enc -des-cbc -iv 90cb27445f4ef5cb -K e54320e26a3424db -provider legacy -provider default -in demo1G.bin -out demo1G.bin.des

# ...and to decrypt it
time openssl enc -d -des-cbc -iv 90cb27445f4ef5cb -K e54320e26a3424db -provider legacy -provider default -in demo1G.bin.des -out demo1G.bin.decryptdes

# Check for differences--there shouldn't be any, so diff returns nothing
diff demo1G.bin demo1G.bin.decryptdes

# Now let's try decrypting with the wrong key
time openssl enc -d -des-cbc -iv 90cb27445f4ef5cb -K e54320e26a3424dc -provider legacy -provider default -in demo1G.bin.des -out demo1G.bin.decryptbad

# Check for differences--diff should return that the files are different
diff demo1G.bin demo1G.bin.decryptbad


#############
#### AES ####
#############


# Record the time that it takes to encrypt a 1 gig file with 128-bit AES
time openssl enc -aes-128-cbc -iv 90cb27445f4ef5cb90cb27445f4ef5cb -K 4320e26a3424dba74320e26a3424dba7 -in demo1G.bin -out demo1G.bin.aes

# ...and to decrypt it
time openssl enc -d -aes-128-cbc -iv 90cb27445f4ef5cb90cb27445f4ef5cb -K 4320e26a3424dba74320e26a3424dba7 -in demo1G.bin.aes -out demo1G.bin.decryptaes

# Check for differences--there shouldn't be any, so diff returns nothing
diff demo1G.bin demo1G.bin.decryptaes

# Now let's try decrypting with the wrong key
time openssl enc -d -aes-128-cbc -iv 90cb27445f4ef5cb90cb27445f4ef5cb -K 4320e26a3424dba74320e26a3424dba8 -in demo1G.bin.aes -out demo1G.bin.decryptbad

# Check for differences--diff should return that the files are different
diff demo1G.bin demo1G.bin.decryptbad


############################
#### OpenSSL speed test ####
############################

openssl speed -provider legacy -provider default -elapsed des-cbc des-ede3 aes-128-cbc aes-256-cbc 



