# Decription
A utility tool to encrypt/decrypt a file.         
# Usage
**./vigenere\_cipher \[-o output\_file\] \[-e\] \[-d\] \[-h\] input\_file**           
<br />
**Parameter:**        
**-e:** Encrypt the file.[Default]      
**-d:** Decrypt the file.        
**-o:** Specify the output\_filt.     
**-h:** Show help.       
<br />
**Note:**          
If you not use the `-o` parameter to specify a output file,      
then the cipertext will be output to a default file,and when     
after encrypt/decrypt the file,the original file(i.e `input_     
file`)will be deleted.So if you want to reserve the the orig-      
inal file,please use the `-o` parameter to specify a output      
file.
# How to run the program?
You can run the program as          
```
$ make        
$ ./vigenere_cipher -h
```
# Example
**Encrypt the file `text`:**          
`$ ./vigenere_cipher text`     
then will create a new file named `text.cry` that contain the ciphertext.              
**Decrypt the file `text.cry`:**           
`$ ./vigenere -d text.cry`        

