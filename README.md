# OTP-stream-cipher

One of the most secure stream ciphers is the one-time-pad(OTP) stream
cipher, OTP uses a keystream that is truly random, long as the plain
text message and used only once.
OTP stream cipher provides unconditional security.
The encryption process involves XORing each bit of the plaintext
with the corresponding bit of the keystream:

Ci = Pi ⊕ Ki
Ci is the ciphertext bit, Pi is the plaintext bit, and Ki is the keystream
bit.
The decryption process is identical, as XORing the ciphertext with
the same keystream bit returns the original plaintext.

Pi = Ci ⊕ Ki

The security of the OTP relies on the randomness of the keystream and
the fact that it is used only once; if the same keystream is used, patterns
can emerge and the security of the cipher can be compromised.
This problem is known as the "two-time pad" problem, where an attacker
can exploit the reuse of the keystream to uncover information about the
plaintext. However, OTP has its practical limitations; generating
and distributing truly random keystreams long as the message is challenging.
For example, suppose we have a plaintext message "HELLO" and a PRNG
that produces the keystream "XMCKL". In this case, first, we convert
the keystream to binary form:
Plaintext: H (01001000), E (01000101), L (01001100), L (01001100), O (01001111)

Keystream: X (01011000), M (01001101), C (01000011), K (01001011), L (01001100)

Next, we XOR each bit of the plaintext with the corresponding bit of the keystream:

H (01001000) XOR X (01011000) = 00010000

E (01000101) XOR M (01001101) = 00001000

L (01001100) XOR C (01000011) = 00001111

L (01001100) XOR K (01001011) = 00000111

O (01001111) XOR L (01001100) = 00000011

The resulting ciphertext in binary form is: 00010000 00001000 00001111 00000111 00000011
To decrypt the ciphertext back into plaintext, the receiver must know
the keystream and apply the same XOR operation, which will give the
original message.
