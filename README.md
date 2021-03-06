# Decription
A simple tool to encrypt/decrypt a file by **keyword**,which can encrypt/decrypt          
all printable character in ASCII table.           
As for _**keyword**_,it can also access all printable character in ASCII table.          
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
```
$ ./vigenere_cipher text       
Enter the keyword: Lemon     
```     
then will create a new file named `text.cry` that contain the ciphertext.              
**Decrypt the file `text.cry`:**           
```     
$ ./vigenere -d text.cry      
Enter the keyword: Lemon
```        
then a new file named `text` will be created,and the original text will in it.             

# Try it on my website
You can try this tool on my website:             
**Encrypt:** [http://www.studyandshare.info/encrypt.html](http://www.studyandshare.info/encrypt.html)           
**Decrypt:** [http://www.studyandshare.info/decrypt.html](http://www.studyandshare.info/decrypt.html)        

# Reference
Reference [Wikipedia](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher).                   
In addition,I have enhanced the function of encrypy and decrypt,such as it can                  
encrypt/decrypt all printable character in ASCII table.       
