#include<iostream>
#include<cstdio>
#include<unistd.h>
#include<fstream>
#include<string>
#include<cstring>
#define MAX_KEYWORD_LEN 40
#define DEFAULT_FILENAME_LEN 40
using std::cout;
using std::endl;
using std::cerr;

const char upper_alphabet[] = {'A','B','C','D','E','F',
                  		 'G','H','I','J','K','L',
						 'M','N','O','P','Q','R',
						 'S','T','U','V','W','X',
						 'Y','Z'};

const char lower_alphabet[] = {'a','b','c','d','e','f',
                  		 'g','h','i','j','k','l',
						 'm','n','o','p','q','r',
						 's','t','u','v','w','x',
						 'y','z'};

const char digit[] = {'0','1','2','3','4',
					  '5','6','7','8','9'};

/*
 * Check whether the keyword is alphabet
 *
 */
bool isAlphabet(const char *keyword)
{
	// Corner case
	if(keyword == nullptr)
		return false;
	
	int len = strlen(keyword);
	for(int i = 0; i < len; ++i)
	{
		if(!isalpha(keyword[i]))
			return false;
	}

	return true;
}

/*
 * Convert the keyword to lowercase
 *
 */
void toLower(char *keyword)
{
	int len = strlen(keyword);

	for(int i = 0; i < len; ++i)
	{
		if(isupper(keyword[i]))
			keyword[i] = tolower(keyword[i]);
	}
}

/*
 * Encrypt the file
 *
 */
void encrypt(const char *input_file,const char *output_file,char *keyword)
{
	std::ifstream fin;
	fin.open(input_file);

	// Open successfully
	if(fin)
	{
		std::ofstream fout;
		fout.open(output_file);
		if(!fout)
		{
			cerr<<"output_file open error.\n";
			return;
		}

		std::string line;
		int msg_len;
		int key_len = strlen(keyword);

		// Convert keyword to lowercase
		toLower(keyword);

		// Encrypt the file 
		while(getline(fin,line))
		{
			msg_len = line.length();
			int key_idx = 0;
			int row_idx, col_idx;
			int result_idx;
			char msg_char, key_char;

			for(int i = 0; i < msg_len; ++i)
			{
				msg_char = line[i];
				key_char = keyword[key_idx];
				key_idx = (key_idx+1) % key_len;
				row_idx = key_char - 'a';

				// `msg_char` is not alpha and digit
				if(!isalpha(msg_char) && !isdigit(msg_char))
					continue;

				// `msg_char` is alphabet
				if(isalpha(msg_char))
				{
					// `msg_char` is lowercase
					if(islower(msg_char))
					{
						col_idx = msg_char - 'a';
						result_idx = (row_idx + col_idx) % 26;
						line[i] = lower_alphabet[result_idx]; 
					}
					// `msg_char` is uppercase
					else
					{
						col_idx = msg_char - 'A';
						result_idx = (row_idx + col_idx) % 26;
						line[i] = upper_alphabet[result_idx];
					}
				}

				// `msg_char` is digit
				if(isdigit(msg_char))
				{
					// Convert row_idx into range [0,9]
					row_idx %= 10;

					// Calculate column index
					col_idx = msg_char - '0';

					// Get the result index of `digit[]`
					result_idx = (row_idx + col_idx)%10;

					// Update line[] with cipher char
					line[i] = digit[result_idx];
				}
			}

			fout<<line<<"\n";
		}
		
		fin.close();
		fout.close();
	}
	else
	{
		cerr<<"Input_file open error.\n";
		return;
	}
}

/*
 * Decrypt the file
 *
 */
void decrypt(const char *input_file,const char *output_file,char *keyword)
{
	// Check whether the parameter is valid 
	if(input_file == nullptr || output_file == nullptr || keyword == nullptr)
	{
		cerr<<"Parameter error.\n";
		return;
	}

	// Open `input_file`
	std::ifstream fin;
	fin.open(input_file);

	// Open file successfully
	if(fin)
	{
		// Open `output_file`
		std::ofstream fout;
		fout.open(output_file);

		// Check whether open successfully
		if(!fout)
		{
			cerr<<"Open output_file error.\n";
			return;
		}

		// Convert keyword to lowercase
		toLower(keyword);

		std::string line;
		char cipher_char;
		int cipher_idx, key_idx, msg_idx;
		int cipher_len;
		int keyword_len = strlen(keyword);
		int j;

		while(getline(fin,line))
		{
			cipher_len = line.length();
			j = 0;

			for(int i = 0; i < cipher_len; ++i)
			{
				key_idx = keyword[j] - 'a';
				j = (j+1) % keyword_len;

				cipher_char = line[i];

				// Check whether the character is alphabet or digit
				if(!isalpha(cipher_char) && !isdigit(cipher_char))
					continue;

				// Deal with alphabet
				if(isalpha(cipher_char))
				{
					// Lowercase
					if(islower(cipher_char))
					{
						cipher_idx = cipher_char - 'a';
						msg_idx = cipher_idx - key_idx;

						if(msg_idx < 0)
							msg_idx += 26;

						line[i] = lower_alphabet[msg_idx];
					}
					// Uppercase
					else
					{
						cipher_idx = cipher_char - 'A';
						msg_idx = cipher_idx - key_idx;

						if(msg_idx < 0)
							msg_idx += 26;

						line[i] = upper_alphabet[msg_idx];
					}
				}

				// Deal with digit
				if(isdigit(cipher_char))
				{
					// Convert `key_idx` into range [0,9]
					key_idx %= 10;

					cipher_idx = cipher_char - '0';

					// Get index of digit[]
					msg_idx = cipher_idx - key_idx;
					if(msg_idx < 0)
						msg_idx += 10;

					// Update line[] with original mssage
					line[i] = digit[msg_idx];
				}
			}

			// Output to `output_file`
			fout<<line<<"\n";
		}

		// Close the file stream
		fin.close();
		fout.close();

	}
	else
	{
		cerr<<"Open input_file error.\n";
		return;
	}

}

/*
 * Show usage
 *
 */
void showUsage(char *excutable_file)
{
	cout<<"\n";
	cout<<"******************************* MANUAL *******************************\n";
	cout<<"Description:\n";
	cout<<"A utility tool to encrypt/decrypt a file.(can only encrypt/\n";
	cout<<"decrypt alphabet and digit.\n\n";
	cout<<"Usage:\n";
	cout<<excutable_file<<" [-o output_file] [-e] [-d] [-h] input_file\n\n";
	cout<<"Parameter:\n";
	cout<<"-e: Encrypt the file.[Default]\n";
	cout<<"-d: Decrypt the file.\n";
	cout<<"-o: Specify the output_filt.\n";
	cout<<"-h: Show help.\n\n";
	cout<<"Note:\n";
	cout<<"If you not use the `-o` parameter to specify a output file,\n";
	cout<<"then the cipertext will be output to a default file,and when\n";
	cout<<"after encrypt/decrypt the file,the original file(i.e `input_\n";
	cout<<"file`)will be deleted.So if you want to reserve the the orig- \n";
	cout<<"inal file,please use the `-o` parameter to specify a output \n";
	cout<<"file.\n";
	cout<<"**********************************************************************\n";
}

int main(int argc,char **argv)
{
	extern int optind;
	extern char *optarg;

	int oflag = 0, dflag = 0, hflag = 0, eflag = 0;
	char *input_file;
	char *output_file;
	char keyword[MAX_KEYWORD_LEN] = {0,};
	char encrypt_default_output_file[DEFAULT_FILENAME_LEN] = {0,};
	char decrypt_default_output_file[DEFAULT_FILENAME_LEN] = {0,};
	int c; 

	// Parse the parameter
	while((c = getopt(argc,argv,"o:deh")) != -1)
	{
		switch(c)
		{
			case 'e':
				eflag = 1;
				break;
			case 'o':
				oflag = 1;
				output_file = optarg;
				break;
			case 'd':
				dflag = 1;
				break;
			case 'h':
				hflag = 1;
				break;
			case '?':
				cerr<<"Unrecognized parameter.\n";
				showUsage(argv[0]);
				return 0;
		}
	}

	input_file = argv[optind];

	// Check whether the help flag is set
	if(hflag)
	{
		showUsage(argv[0]);
		return 0;
	}

	// No input_file
	if(optind == argc)
	{
		cerr<<"Syntax error: No input file.\n";
		showUsage(argv[0]);
		return 1;
	}

	// Check whether the encrypt flag and decrypt flag set simultaneously
	if(eflag && dflag)
	{
		cerr<<"Syntax error: ";
		cerr<<"Parameter `-d` and `-e` can't appear simultaneously.\n";
		return 1;
	}

	//cout<<"Input_file:"<<input_file<<endl;
	
	// Enter the keyword
	while(1)
	{
		cout<<"Enter the keyword: ";
		fgets(keyword,MAX_KEYWORD_LEN-1,stdin);

		// Strip the character of '\n'
		int k_len = strlen(keyword);
		keyword[k_len-1] = 0;


		// Check whether the keyword is valid
		if(isAlphabet(keyword))
			break;
		else
		{
			cerr<<"The keyword is invalid.\n";
			cerr<<"Note: only the alphabet is acceptable.\n";
		}
	}

	// oflag and dflag is not set,then use the default encrypt output file
	if(!oflag && !dflag)
	{
		strcpy(encrypt_default_output_file,input_file);
		strcat(encrypt_default_output_file,".cry");
	}
	// oflag is not set but the dflag is set,then use the default decrypt output file
	else if(!oflag && dflag)
	{
		int len = strlen(input_file);

		// Check whether the `input_file` have extension of '.cry'
		if(!strcmp(input_file+len-4,".cry"))
		{
			strncpy(decrypt_default_output_file,input_file,len-4);

		}
		// `input_file` don't have extension of '.cry',then add the
		// extension of '.de' to the end of `input_file`
		else
		{
			strcpy(decrypt_default_output_file,input_file);
			strcat(decrypt_default_output_file,".de");
		}
	}


	// Encrypt the file
	if(!dflag)
	{
		// oflag is set
		if(oflag)
			encrypt(input_file,output_file,keyword);
		else
		{
			encrypt(input_file,encrypt_default_output_file,keyword);

			// If `oflag` is not set,then remove the input_file
			remove(input_file);
		}
	}
	// Decrypt the file
	else
	{
		// `oflag` is set
		if(oflag)
			decrypt(input_file,output_file,keyword);
		else
		{
			decrypt(input_file,decrypt_default_output_file,keyword);

			// If `oflag` is not set,then remove the input_file
			remove(input_file);
		}
	}


	return 0;
}
