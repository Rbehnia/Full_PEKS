/*

 A portion of this code was prepared by Thomas Prest.

*/



#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/mat_ZZ.h>
#include <gmp.h>
#include <zmq.hpp>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <complex.h>
#include "params.h"
#include "io.h"
#include "FFT.h"
#include "Sampling.h"
#include "Random.h"
#include "Algebra.h"
#include "Scheme.h"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include "blake2.h"


using namespace std;
using namespace NTL;

//#include </boost/algorithm/string/classification.hpp>


using namespace std;
typedef std::set<string> TYPE_KEYWORD_DICTIONARY;
typedef unsigned long int TYPE_COUNTER;

const char* const delimiter = "`-=[]\\;\',./~!@#$%^&*()+{}|:\"<>? \n\t\v\b\r\f\a"; 


bool file_existence(const string path , const string file_name)
{
	
	string fname_with_path = "";

	fname_with_path.append(path);
	fname_with_path.append(file_name);
    ifstream infile(fname_with_path.c_str());
    return infile.good();
}


bool is_word(std::string& s){
	bool flagd =true, flagc = false;  int count = 0;
	std::string::iterator it = s.begin();
    for (it = s.begin();it != s.end(); ++it)  {
		count++;
		if (std::isalpha(*it)){}
		else{
			flagd = false; 	
			}
		if (count > 3)  flagc = true;
	}
	
	
    return (flagd && flagc);
}
int extractWords_using_find_first_of(TYPE_KEYWORD_DICTIONARY &rKeywordsDictionary,
		TYPE_COUNTER *pKeywordNum,
		ifstream &rFin){

	bool capture = false;
	string line, word;
	while(getline(rFin, line)) 
    {
		int counter = 0;
		size_t prev = 0, pos;
		boost::trim(line);
		while ((pos = line.find_first_of(delimiter, prev)) != std::string::npos)
		{
			if (pos > prev)
            {
				word = line.substr(prev, pos-prev);
				boost::trim(word);
                //convert the word to lower case
                std::transform(word.begin(),word.end(),word.begin(),::tolower);
				//if (word == "dfossum") 
				capture=true;
				if (is_word(word) && capture &&   rKeywordsDictionary.size()<numOfKeywords){
                rKeywordsDictionary.insert(word);
				*pKeywordNum = *pKeywordNum + 1;
				}
			}

			prev = pos+1;
		}
		if (prev < line.length()){
			word = line.substr(prev, std::string::npos);
			boost::trim(word);

            //convert the word to lower case
            std::transform(word.begin(),word.end(),word.begin(),::tolower);
			if (word == "dfossum") capture=true;
			if (is_word(word)&& capture && rKeywordsDictionary.size()<numOfKeywords){
				rKeywordsDictionary.insert(word);
				*pKeywordNum = *pKeywordNum + 1;
			}
		}

	}

	return 0;
}
int extractKeywords(TYPE_KEYWORD_DICTIONARY &rKeywordsDictionary,
		string file_name ,string path) 
{ 
	TYPE_COUNTER keyword_num = 0;
	string fname_with_path;

	// create a file-reading object
	ifstream fin;

	fname_with_path.append(path);
	fname_with_path.append(file_name);

	// open a file
	fin.open(fname_with_path.c_str(),std::fstream::in);
	if (!fin.good()){
		cout << "No such file exist"<<endl; // exit if file not found
	}
	// Extract keywords from a file
	extractWords_using_find_first_of(rKeywordsDictionary, &keyword_num, fin);

	fin.close();

	return 0;
}
// Function gets the file info and a set of keywords and writes them on the file for the future use. 
void writeKeywords(TYPE_KEYWORD_DICTIONARY keywordSet, string file_name, string path){
	
	string fname_with_path;
	std::set<string>::iterator it;

	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("kw");
	// Opening file to write the keywords on it. 
	ofstream myfile;
	myfile.open (fname_with_path.c_str(), ios::out | ios::binary); 
	for (it=keywordSet.begin(); it!=keywordSet.end(); ++it){
		myfile << ' ' << *it;
	}
	myfile.close();
	
	
}
// Function to read keywords from file
void extractKeywordFile(string *keywordExtracted,  string file_name, string path, int& counterKeys)
{
    ifstream ifile;
	string fname_with_path;
	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("kw");
	// Opening file to read the keywords from it. 
    ifile.open (fname_with_path);
    if (!ifile.is_open()) 
		{cout << "No such file exist"<<endl;}
	string word;
	counterKeys = 0; 
    while (ifile >> word)
    {
		keywordExtracted[counterKeys] = word;
		counterKeys++;
     }
	 int cc = 1;
	for (int key = 0;key<counterKeys;key++){
	cout << file_name<< " "<< cc << "   "<< keywordExtracted[key]<<endl; cc++;}
	ifile.close();
}

// Stores the PEKS obtained from the function below in the file. 

void writePEKStoFile(string file_name, string path, long const Ciphertext[2][N0], long const Ciphertext2[N0]){
	
	string fname_with_path;
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("sc");

	ofstream ofile;
	// opening file for writing the ciphertext, each row of the array Ciphertext is separated with newline. 
	ofile.open (fname_with_path.c_str(), ios_base::app); 
	for (int i = 0;i < 2 ;i++){
		
		for (int j = 0;j < N0; j++){
			ofile << Ciphertext[i][j]<< " ";
				
		} ofile<<endl;

	}
	for (int j = 0;j < N0; j++){
		ofile << Ciphertext2[j]<< " ";
	} ofile<<endl;
	ofile.close();
}
	
//Function to encrypt keywords and store them in file using writePEKStoFile function

void KeywordstoPEKS(long  Ciphertext[2][N0], long Ciphertext2[N0],  string file_name, string path, string *keywordExtracted , int counterKeys, const MPK_Data * const MPKD)
	{
	long keywordConverted[N0];
	int sum = 0;
	string word; char ch;
	char keywordAux[N0] = {'0'};
	for(int i = 0; i<counterKeys;i++){
		word =keywordExtracted[i];
		for (int i =0; i<N0;i++)
			keywordAux[i] ='0';
			for  (int i=0; i < word.length();i++){
				keywordAux[i] = word[i];
				ch  = keywordAux[i];
				keywordConverted[i] = (ch);

			}
		for (int i =word.length(); i<N0;i++){
			keywordConverted[i] = 0;
		}
	
		for (int i =word.length(); i<N0;i++){
			keywordConverted[i] = 0;
		}
		sum = 0;
		for (int i =0; i<N0;i++){
			sum +=keywordConverted[i];
		}
		
		
		
		
		
		uint8_t hash[64];
		for (int i = 0; i<N0/16; i++){
			word.append(to_string(i).c_str());
			
			blake2b(hash, word.c_str(), NULL, 64, word.size(), 0);
			for (int j = 0; j<16; j++){
				keywordConverted[i*16+j] = (hash[4*j] + hash[4*j+1]*256 + hash[4*j+2]*256*256 + hash[4*j+3]*256*256*256)%q0;
			}
				
		}
		
		PEKS_Enc(Ciphertext, Ciphertext2, keywordConverted, MPKD);
		
		writePEKStoFile(file_name,path,Ciphertext, Ciphertext2);
	}
	


}


// Function to generate trapdoor on user input
void myTrapdoorGenerator( MSK_Data * MSKD,  ZZX  SK_td[2]){
	
	char keywordAux[N0] = {'0'};
	int sum = 0;
	long keywordConverted[N0];
	unsigned int testing = 0;
	auto start = time_now;
	auto end = time_now;
	vec_ZZ keyword_zz;
	string word; char ch;
	cout << endl<<"Please keyin the keyword you would like to be searched: ";
	cin >> word;
	
	
	start = time_now;
	for (int i =0; i<N0;i++)
		keywordAux[i] ='0';
		
		
	for  (int i=0; i < word.length();i++){
		keywordAux[i] = word[i];
		ch  = keywordAux[i];
		keywordConverted[i] = ch;

	} 
	for (int i =word.length(); i<N0;i++){
		keywordConverted[i] = 0;
	}
	

	cout << endl;
		sum = 0;
	for (int i =0; i<N0;i++){
		sum +=keywordConverted[i];
	}
			
		uint8_t hash[64];
		for (int i = 0; i<N0/16; i++){
			word.append(to_string(i).c_str());
			blake2b(hash, word.c_str(), NULL, 64, word.size(), 0);
			for (int j = 0; j<16; j++){
				keywordConverted[i*16+j] = (hash[4*j] + hash[4*j+1]*256 + hash[4*j+2]*256*256 + hash[4*j+3]*256*256*256)%q0;
			}
				
		}

	keyword_zz = keywordVector(keywordConverted);
	PEKS_Trapdoor(SK_td, keyword_zz, MSKD);
	testing = PEKS_Verify_Trapdoor(SK_td, keyword_zz, MSKD);
	end = time_now;
	cout<<"Trapdoor Generation took    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
}


void findFileByKeywords(TYPE_KEYWORD_DICTIONARY & listOfFiles, string path, const ZZX SK_td[2]){
	cout << "We are in Find FILE BY KEYWORD now: "<<endl<<endl;
	int rep;
	bool flagvalid = false; 
	CC_t SKtd_FFT[N0]; 
	long  Ciphertext_file[2][N0] = {0};
	long Ciphertext2_file[N0] = {0};
	int counter = 0;
	long message[N0];
	string auxstring[N0];
        string line1 = "";
    	string line2 = "";	
	string line3 = "";
    	ZZXToFFT(SKtd_FFT, SK_td[1]);
	string temp1,temp2="",fileNameforList="", fname_with_path;
	fstream ifile;
	
	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		string line1 = "";
		string line2 = "";	
		string line3 = "";
		fstream ifile;
		fname_with_path = "";
		ifile.close();
		fname_with_path.append(path);
		string file_name = "";
		file_name.append("/");
		temp1 = to_string(filecount);
		file_name.append(temp1);
		fileNameforList.append(file_name);
		//fileNameforList.append(".");
		file_name.append("sc");
		fname_with_path.append(file_name);
		cout << file_name << " being opend"<<endl;
		ifile.open(fname_with_path,ios::in);
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		string word ="";
		string target = "";
		while (getline(ifile,line1)){
	//======	
			
			getline(ifile,line2);
			getline(ifile,line3);
			istringstream ss;
			ss.str(line1);
			counter =0;
			while(ss >> word){
 
			Ciphertext_file[0][counter] = stol(word); counter++;}
			istringstream ss1;
			ss1.str(line2);
			counter =0;
			while(ss1 >> word)
			{
				Ciphertext_file[1][counter] = stol(word); counter++;
			}

			istringstream ss2;		
			ss2.str(line3);
			counter =0;
			while(ss2 >> word)
			{
				Ciphertext2_file[counter] = stol(word); counter++;
			}

			PEKS_Test(message, Ciphertext_file, SKtd_FFT);
			rep = 0;
			for(int j=0; j<N0; j++){
				
				if( Ciphertext2_file[j] == message[j])
				{
					rep +=1 ;
					
				}	
				if (rep == N0-1){
					flagvalid =true;
					target = file_name;
					cout << "it matched";
					listOfFiles.insert(target);
				}


			}	

				
		}

	}		

}


void storeSKDatatoFile(ZZX MSK[4], MSK_Data * MSKD, string path){
	
	
	
	string fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSK");
	cout << fname_with_path<<endl;
	ofstream ofileMSK;
	ofileMSK.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i<4;i++)
		ofileMSK << MSK[i] <<endl ;
		
		
		
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDPrk");
	ofstream ofileMSKDPrk;
	ofileMSKDPrk.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i<4;i++)
		
		ofileMSKDPrk << MSKD->PrK[i] <<endl ;

	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDPrkfft");
	ofstream ofileMSKDPrkfft;
	ofileMSKDPrkfft.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i<4;i++){
		for (int j = 0; j<N0;j++){
			ofileMSKDPrkfft << MSKD->PrK_fft[i][j]<<endl;
		}
	}
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDGSNorms");
	ofstream ofileMSKDGSNorms;
	ofileMSKDGSNorms.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i < (2*N0); i++){
		
		ofileMSKDGSNorms<< MSKD->GS_Norms[i]<<endl; 
	}
	//ofile<< endl;
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDsigma");
	ofstream ofileMSKDsigma;
	ofileMSKDsigma.open (fname_with_path.c_str(),  ios::binary); 
	ofileMSKDsigma <<MSKD->sigma; 
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDB");
	ofstream ofileMSKDB;
	ofileMSKDB.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i < (2*N0); i++){
		for (int j = 0; j < (2*N0); j++){
			ofileMSKDB<< MSKD->B[i][j]<<endl;

		}
		//ofile<< endl;
	}
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDBfft");
	ofstream ofileMSKDBfft;
	ofileMSKDBfft.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i < (2*N0); i++){
		for (int j = 0; j < (2*N0); j++){
			ofileMSKDBfft<< MSKD->Bstar[i][j]<<endl;

		}
		//ofile<< endl;
	}
	ofileMSKDBfft.close();
	ofileMSKDB.close();
	ofileMSKDsigma.close();
	ofileMSKDGSNorms.close();
	ofileMSKDPrkfft.close();
	ofileMSKDPrk.close();
	ofileMSK.close();
	

	
}
	

void readSKdataFromFile (ZZX MSK[4] ,  MSK_Data * MSKD, string path){

	
	RR_t B1[2*N0][2*N0];
	
	
	
	
	string fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSK");
	cout << fname_with_path<<endl;
	ifstream ifileMSK;
	ifileMSK.open (fname_with_path.c_str()); 
	for (int i = 0; i<4;i++)
		ifileMSK >> MSK[i] ;
		
		
		
	string fname_with_path1 = "";
	//recreate the file name
	fname_with_path1.append(path);
	fname_with_path1.append("MSKDPrk");
	ifstream ifileMSKDPrk;
	ifileMSKDPrk.open (fname_with_path1.c_str()); 
	for (int i = 0; i<4;i++)
		
		ifileMSKDPrk >> MSKD->PrK[i] ;
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDPrkfft");
	ifstream ifileMSKDPrkfft;
	ifileMSKDPrkfft.open (fname_with_path.c_str()); 
	for (int i = 0; i<4;i++){
		for (int j = 0; j<N0;j++){
			ifileMSKDPrkfft >> MSKD->PrK_fft[i][j];
		}
	}
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDGSNorms");

	ifstream ifileMSKDGSNorms;
	ifileMSKDGSNorms.open (fname_with_path.c_str()); 
	for (int i = 0; i < (2*N0); i++){
		
		ifileMSKDGSNorms >> MSKD->GS_Norms[i]; 
	}
	//ofile<< endl;
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDsigma");

	ifstream ifileMSKDsigma;
	ifileMSKDsigma.open (fname_with_path.c_str()); 
	ifileMSKDsigma >> MSKD->sigma;
	
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDB");
	ifstream ifileMSKDB;
	ifileMSKDB.open (fname_with_path.c_str()); 
	for (int i = 0; i < (2*N0); i++){
		for (int j = 0; j < (2*N0); j++){
			ifileMSKDB >> MSKD->B[i][j];

		}
		//ofile<< endl;
	}
	
	
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MSKDBfft");
	ifstream ifileMSKDBfft;
	ifileMSKDBfft.open (fname_with_path.c_str()); 
	for (int i = 0; i < (2*N0); i++){
		for (int j = 0; j < (2*N0); j++){
			ifileMSKDBfft>> MSKD->Bstar[i][j];

		}
		//ofile<< endl;
	}
	ifileMSKDBfft.close();
	ifileMSKDB.close();
	ifileMSKDsigma.close();
	ifileMSKDGSNorms.close();
	ifileMSKDPrkfft.close();
	ifileMSKDPrk.close();
	ifileMSK.close();
	

		
	
	
	}
	
	


void storePKDatatoFile(ZZ_pX MPK, MPK_Data * MPKD, string path){
	
	string fname_with_path;
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MPK");
	//cout << fname_with_path<<endl;
	ofstream ofileMPK;
	ofileMPK.open (fname_with_path.c_str(),  ios::binary); 

	ofileMPK<<MPK;
	
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MPKDh");
	ofstream ofileMPKDh;
	ofileMPKDh.open (fname_with_path.c_str(),  ios::binary); 
	ofileMPKDh << MPKD->h<<endl;
	
		
	fname_with_path = "";
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("MPKDhfft");
	//cout << fname_with_path<<endl;
	ofstream ofileMPKDhfft;
	ofileMPKDhfft.open (fname_with_path.c_str(),  ios::binary); 
	for (int i = 0; i<N0;i++)
		ofileMPKDhfft << MPKD->h_FFT[i] ;

	ofileMPK.close();
	ofileMPKDhfft.close();
	ofileMPKDh.close();
}




void readPKDatafromFile(ZZ_pX &MPK, MPK_Data * MPKD, string path){
	//CC_t h_FFT[N0];
	string fname_with_path = "";
	fname_with_path.append(path);
	fname_with_path.append("MPK");
	//cout << "This is the main"<<fname_with_path<<endl;
	ifstream ifileMPK;
	string line;
	ifileMPK.open (fname_with_path.c_str()); 
	ifileMPK>>MPK;
/*	for (int i = 0;i<N0;i++){
	
	getline(ifileMPK,line);
	}*/
	fname_with_path = "";
	fname_with_path.append(path);
	fname_with_path.append("MPKDh");
	ifstream ifileMPKDh;
	ifileMPKDh.open (fname_with_path.c_str()); 
	ifileMPKDh >> MPKD->h;
	
	fname_with_path = "";
	fname_with_path.append(path);
	fname_with_path.append("MPKDhfft");
	//cout << fname_with_path<<endl;
	ifstream ifileMPKDhfft;
	ifileMPKDhfft.open (fname_with_path.c_str()); 
	for (int i = 0; i<N0;i++)
		ifileMPKDhfft >> MPKD->h_FFT[i];

 
	ifileMPK.close();
	ifileMPKDhfft.close();
	ifileMPKDh.close();

}



// ============================Sending Files to Server 



void sendPeksToServer(string path){
    zmq::context_t context(1);
	zmq::socket_t socket(context,ZMQ_REQ);
	printf("   Connecting to server...");
	socket.connect ("tcp://localhost:5560");
	//socket.connect ("tcp://128.193.38.12:5560");
	//socket.connect ("tcp://34.216.2.150:5560");
	printf("OK!\n");
	string line1 = "";
    string line2 = ""; string line3 = "";		
	string fname_with_path;
	fstream ifile;
	size_t sizeLine1 = 0;
	size_t sizeLine2 = 0;
	size_t sizeLine3 = 0;
	auto start = time_now;
    auto end = time_now;
	float sum = 0.0;
	string line22 = "Hello there how are you0";
	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		
		string temp1 = "";
		fstream ifile;
		fname_with_path = "";
		fname_with_path.append(path);
		string file_name = "";
		file_name.append("/");
		temp1 = to_string(filecount);
		file_name.append(temp1);
		file_name.append("sc");
		fname_with_path.append(file_name);
		size_t size1, size2,size3;
		ifile.open(fname_with_path.c_str());
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		int i = 0;
		while (i < numOfKeywords){
			
			line1 = "";line2 = "";line3 = "";
			getline(ifile,line1);
			getline(ifile,line2);
			getline(ifile,line3);
			sizeLine1 = (size_t)line1.length();
			zmq::message_t request_line1(sizeLine1);
			memcpy (request_line1.data (), line1.c_str(), sizeLine1);
			
			sizeLine2 = (size_t)line2.length();
			zmq::message_t request_line2(sizeLine2);
			memcpy (request_line2.data (), line2.c_str(), sizeLine2);
			
			sizeLine3 = (size_t)line3.length();
			zmq::message_t request_line3(sizeLine3);
			memcpy (request_line3.data (), line3.c_str(), sizeLine3);
			
			
			
			start = time_now;
			socket.send (request_line1);
			zmq::message_t reply;
			socket.recv (&reply);
	     	socket.send (request_line2);
			socket.recv (&reply);
			socket.send (request_line3);
			socket.recv (&reply);
			end = time_now;
			sum += (float)(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count());
			
			i++;
			}

		}
		
		cout<<	"Sending PEKS, each file takes   "<<sum/(numOfFiles*numOfKeywords)<<" microseconds on average"<<endl;
		
		cout << "All files have been received and stored in "<< path << "  folder "<< endl;
		ifile.close();
		socket.close();


		
	}



void writePEKStoFileServer(string fname_with_path, string fname,  string x, string y, string pb){
	
	 
	

	//string fname_with_path;
	//recreate the file name

	fname_with_path.append(fname);
	
	ofstream ofile;
	ofile.open (fname_with_path.c_str(), ios_base::app | ios::binary); 
	ofile << x ;

	ofile<<endl;
	ofile << y << endl;
	
	ofile << pb;
	ofile<<endl;
	ofile.close();
}





void receivingPeksServer(string serverPath){
	
	
	zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5560");
	int counterKeywords; 

	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		
		string temp1 = "";
		ofstream ofile;
		string fname_with_path1 = "";
		fname_with_path1.append(serverPath);
		string file_name = "";
		file_name.append("/");
		temp1 = to_string(filecount);
		file_name.append(temp1);
		file_name.append("sc");
		fname_with_path1.append(file_name);
		size_t size1, size2,size3;
		ofile.open (fname_with_path1.c_str(),  ios::binary); 


	counterKeywords = 0;
    while (counterKeywords < numOfKeywords) {
		
        zmq::message_t request1;
        socket.recv (&request1);
        string rpl1 = string(static_cast<char*>(request1.data()), request1.size());
        cout <<  rpl1<< endl;
		
		zmq::message_t reply1 (8);
        memcpy (reply1.data (), "World", 8);
        socket.send (reply1);
		
	//sleep(1);
		zmq::message_t request2;
		socket.recv (&request2);
        string rpl2 = string(static_cast<char*>(request2.data()), request2.size());
        cout <<  rpl2<< endl;	

        zmq::message_t reply2 (8);
        memcpy (reply2.data (), "World", 8);
        socket.send (reply2);	
		
		
	//sleep(1);	
	//sleep(1);	
		zmq::message_t request3;
		socket.recv (&request3);
        string rpl3 = string(static_cast<char*>(request3.data()), request3.size());
        cout <<  rpl3<< endl;
		
		zmq::message_t reply3 (8);
        memcpy (reply3.data (), "World", 8);
        socket.send (reply3);
		writePEKStoFileServer(serverPath ,file_name, rpl1, rpl2,rpl3);

		counterKeywords++; 

        //  Do some 'work'

        //  Send reply back to client

    }
}

	
	cout << "All files have been received and stored in "<< serverPath << "folder "<< endl;
	socket.close();
	
}







void writeTrapdoorFile(string fname_with_path, ZZX SK_td[2]){
	
	

	fname_with_path.append("trapdoor");
	
	ofstream ofile;
	ofile.open (fname_with_path.c_str(),  ios::binary);
	ofile << SK_td[0]<<endl;
	ofile<< SK_td[1];


	ofile.close();
}


void sendTrapdoorToServer(string path){
    zmq::context_t context(1);
	zmq::socket_t socket(context,ZMQ_REQ);
	printf("   Connecting to server...");
	socket.connect ("tcp://localhost:5559");
	//socket.connect ("tcp://34.216.2.150:5559");
	//socket.connect ("tcp://128.193.38.12:5559");
	printf("OK!\n");
	string line1 = "";
	string fname_with_path;
	size_t sizeLine1 = 0;
	ZZX td; 
	auto start = time_now;
    auto end = time_now;
	float sum = 0.0;
	
	fstream ifile;
	fname_with_path = "";
	fname_with_path.append(path);
	//file_name = "";
	//file_name.append("/");
	fname_with_path.append("trapdoor");
	size_t size1;
	ifile.open(fname_with_path.c_str());
	if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		while(getline(ifile, line1)){
			cout << "The lines in sendTrapdoor "<<line1<<endl;
			sizeLine1 = (size_t)line1.length();
			zmq::message_t request_line1(sizeLine1);
			memcpy (request_line1.data (), line1.c_str(), sizeLine1);
			
			start = time_now;
			socket.send (request_line1);
			zmq::message_t reply;
			socket.recv (&reply);
			end = time_now;
			sum += (float)(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count());
		}

	cout<<	"Sending Trapdoor takes   "<<sum<<" microsecond"<<endl;
		
			
	ifile.close();
	socket.close();


		
	}


void writeTrapdoortoFileServer(string fname_with_path,  string x){
	
	 
	

	//string fname_with_path;
	//recreate the file name

	fname_with_path.append("trapdoor");
	
	ofstream ofile;
	ofile.open (fname_with_path.c_str(), ios_base::app | ios::binary); 
	ofile << x ;
	ofile<<endl;

	ofile.close();
}


void receivingTrapdoorServer(string serverPath){
	
	
	zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5559");

		ofstream ofile;
		string fname_with_path1 = "";
		fname_with_path1.append(serverPath);
		string file_name = "trapdoor";
		fname_with_path1.append(file_name);
		size_t size1;
		ofile.open (fname_with_path1.c_str(),  ios::binary); 


	int numOfLinesTrapdoor = 0;
    while (numOfLinesTrapdoor < 2) {
		
        zmq::message_t request1;
        socket.recv (&request1);
        string rpl1 = string(static_cast<char*>(request1.data()), request1.size());
        cout <<  rpl1<< endl;
		
		zmq::message_t reply1 (8);
        memcpy (reply1.data (), "World", 8);
        socket.send (reply1);
		
		writeTrapdoortoFileServer(serverPath, rpl1);

		numOfLinesTrapdoor++; 

        //  Do some 'work'

        //  Send reply back to client

    }


	
	cout << "All files have been received and stored in "<< serverPath << "folder "<< endl;
	socket.close();
	
}


void findFileByKeywordsServer(TYPE_KEYWORD_DICTIONARY & listOfFiles, string path, string serverPath){
	
	
	ZZX SK_td[2];
	string tdfname = "";
	tdfname.append(serverPath);
	tdfname.append("trapdoor");
	ifstream fileTrapdoor;
	fileTrapdoor.open(tdfname.c_str());
	fileTrapdoor >> SK_td[0];
	fileTrapdoor >> SK_td[1];

	fileTrapdoor.close();
cout << "We are in Find FILE BY KEYWORD now: "<<endl<<endl;
	int rep;
	bool flagvalid = false; 
	CC_t SKtd_FFT[N0]; 
	long  Ciphertext_file[2][N0] = {0};
	long Ciphertext2_file[N0] = {0};
	int counter = 0;
	long message[N0];
	string auxstring[N0];
    string line1 = "";
    string line2 = "";	
	string line3 = "";
    ZZXToFFT(SKtd_FFT, SK_td[1]);
	string temp1,temp2="",fileNameforList="", fname_with_path;
	fstream ifile;
	
	
	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		string line1 = "";
		string line2 = "";	
		string line3 = "";
		fstream ifile;
		fname_with_path = "";
		ifile.close();
		fname_with_path.append(path);
		string file_name = "";
	//	file_name.append("/");
		temp1 = to_string(filecount);
		file_name.append(temp1);
		fileNameforList.append(file_name);
		//fileNameforList.append(".");
		file_name.append("sc");
		fname_with_path.append(file_name);
		cout << file_name << " being opend"<<endl;
		ifile.open(fname_with_path,ios::in);
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		string word ="";
		string target = "";
		while (getline(ifile,line1)){
	//======	
			
			getline(ifile,line2);
			getline(ifile,line3);
			istringstream ss;
			ss.str(line1);
			counter =0;
			while(ss >> word){
 
			Ciphertext_file[0][counter] = stol(word); counter++;}
			istringstream ss1;
			ss1.str(line2);
			counter =0;
			while(ss1 >> word)
			{
				Ciphertext_file[1][counter] = stol(word); counter++;
			}

			istringstream ss2;		
			ss2.str(line3);
			counter =0;
			while(ss2 >> word)
			{
				Ciphertext2_file[counter] = stol(word); counter++;
			}

			PEKS_Test(message, Ciphertext_file, SKtd_FFT);
			rep = 0;
			for(int j=0; j<N0; j++){
				
				if( Ciphertext2_file[j] == message[j])
				{
					rep +=1 ;
					
				}	
				if (rep == N0-1){
					flagvalid =true;
					target = file_name;
					cout << "it matched";
					listOfFiles.insert(target);
				}


			}	

				
		}

	}
	ifile.close();		
}



//============================== MENU ===========================================

void mainMenu(){
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "Select one of the following: \n";
	cout << "(1) Sender\n";
	cout << "(2) Receiver\n";
	cout << "(3) Server\n";
	cout << "(4) Exit\n";

	cout << "Choice: ";

}
void senderMenu(string path, const bool flagEnc){
	//int choiceSender = 0;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "The default path for the email files is: \n";
	cout << path<<endl;
	cout << "The  number of email files is: ";
	cout << numOfFiles <<endl;
	cout << "Select one of the following: \n";
	cout << "(1) Change the default path\n";
	cout << "(2) Change the default number of files\n";
	cout << "(3) Extract and encrypt keywords for each file "; if (flagEnc){ cout << "(Done)\n"; } else cout << "\n"; 
	cout << "(4) Send encrypted files to the server\n";
	cout << "(5) Return to the main menu\n";
	cout << "Choice: ";
}

void receiverMenu(const bool flagTrapdoor, string path){
	string filename = "MPK";
	string filename_with_path = "";
	filename_with_path.append(path);
	filename_with_path.append(filename);
	cout << filename_with_path<<endl;
	ifstream keyfile (filename_with_path.c_str()); 
	
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "Select one of the following: \n"; 
	cout << "(1) Generate keys ";  if (keyfile) { cout<< "(Done!) \n";} else cout <<"\n";
	cout << "(2) Generate trapdoor "; if (flagTrapdoor){ cout << "(Done!)\n"; } else cout << "\n"; 
	cout << "(3) Send Trapdoor to server (trapdoor should have been genrated first.)\n";
	cout << "(4) Find files by keyword (trapdoor should have been genrated first.)\n";
	cout << "(5) Return to the main menu\n";
	cout << "Choice: ";
}


	
void serverMenu(){
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "Select one of the following: \n";
	cout << "(1) Receive Trapdoor\n";
	cout << "(2) Receive PEKS\n";
	cout << "(3) Return to the main menu\n";

	cout << "Choice: ";

}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//==============================================================================
//==============================================================================
//                                  MAIN
//==============================================================================
//==============================================================================


int main()
{
	int choiceMain, choiceSender,choiceReceiver,serverChoice;
    

	bool flagKeyGen = false; 
	bool flagTrapdoor = false;
	bool flagEnc = false;
	
	// Added for ENRON Extension 
    long int keyword[N0], Ciphertext[2][N0], Ciphertext2[N0];
	string skPath = "/NTRU_PEKS/keys/sk/";
	string pkPath = "/NTRU_PEKS/keys/pk/";
	string path = "/NTRU_PEKS/textfiles";
	string serverPath = "/NTRU_PEKS/server/";
	TYPE_KEYWORD_DICTIONARY listOfFiles;
	ZZX SK_td[2];
	std::set<string>::iterator it;
	string keyword_str;
	
	ZZX MSK[4];
	ZZ_pX phiq, MPK;
    unsigned int i;
    float diff;
    MSK_Data * MSKD = new MSK_Data();
    MPK_Data * MPKD = new MPK_Data();
    clock_t t1, t2;
    const ZZX phi = Cyclo();
	auto start = time_now;
    auto end = time_now;
	float sum = 0.0;
	
    cout << "\n=======================================================================\n";
    cout << "This program is a proof-of concept for efficient PEKS over lattices.\n";
    cout << "It generates a NTRU lattice of dimension 2N and associated modulus q,\n";
    cout << "and perform benches and tests, for user PEKS and Trapdoor  and Test.";
    cout << "\n=======================================================================\n\n";

	
   // The code above this was added for ENRON extension of this code. 
	
	

    srand(rdtsc()); // initialisation of rand
    cout << "N = " << N0 << endl;
    cout << "q = " << q0 << endl;

    ZZ_p::init(q1);
    zz_p::init(q0);

    phiq = conv<ZZ_pX>(phi);
    ZZ_pXModulus PHI(phiq);
	

//=============cherck this





	if (file_existence(skPath,"MSK") && file_existence(skPath,"MSKDsigma") && file_existence(skPath,"MSKDBfft") && file_existence(pkPath,"MPKDhfft") && file_existence(pkPath,"MPKDh")){
		
		
		readSKdataFromFile (MSK, MSKD,skPath);
		readPKDatafromFile(MPK,  MPKD,  pkPath);
		CompleteMSK(MSKD, MSK);
  		CompleteMPK(MPKD, MPK);
		flagKeyGen = true;
	
	}
	else {

		t1 = clock();
		start = time_now;
		for(i=0; i<1; i++)
		{
        Keygen(MPK, MSK);
		
		}

	
	
		CompleteMSK(MSKD, MSK);
		CompleteMPK(MPKD, MPK);
		end = time_now;
		cout<<"Key Generation took    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
		storeSKDatatoFile( MSK,  MSKD, skPath);
		storePKDatatoFile(MPK, MPKD, pkPath );
	}



// ========================================== MENU STUFF 
labelMain: mainMenu( );
	cin >> choiceMain;
	cout << "\n\n\n\n\n\n\n\n\n\n";

if (choiceMain == 1){
	labelSenderMenu:
	senderMenu( path, flagEnc);
	cin >> choiceSender;
	if (choiceSender == 1){
		cout << "Please keyin the new path: ";
		cin >> path;
		goto labelSenderMenu;
	}
	else if (choiceSender == 2){
		cout << "Please keyin the number of files: ";
	//	cin >> numOfFiles;
		goto labelSenderMenu;
	}
	else if (choiceSender == 3){
		
		
		string file_name;
		int counterKeys;
		for (int j = 1; j < numOfFiles; j++){
			string keywordExtracted[25];
			string temp;
			vec_ZZ keyword_zz;
			int rep[numOfKeywords] = {0};
			TYPE_KEYWORD_DICTIONARY myset;
			file_name = "/";
			temp = to_string(j);
			file_name.append(temp);
			//file_name.append(".");
			extractKeywords(myset, file_name, path);
			writeKeywords(myset, file_name, path);
			extractKeywordFile(keywordExtracted,  file_name,path, counterKeys);
			start = time_now;
			KeywordstoPEKS(Ciphertext, Ciphertext2,file_name, path, keywordExtracted,counterKeys,MPKD);
			end = time_now;
			sum += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
			//cout<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
				
		}
		cout<<"Generate PEKS, each file takes   "<<sum/numOfFiles<<" ms on average"<<endl;
		flagEnc = true;

	}
	else if (choiceSender == 4){
		sendPeksToServer(path);
		goto labelSenderMenu;
	}
		
	
	else if (choiceSender == 5){ goto labelMain;}
	sleep(1);
	
	
	goto labelSenderMenu;
	
	
	
	
	
	
}
	
if (choiceMain == 2){
	labelReceiverMenu: 
	receiverMenu(flagTrapdoor,pkPath);
	cin >> choiceReceiver;
	if (choiceReceiver == 1 ){
		start = time_now;
		for(i=0; i<1; i++)
		{
			Keygen(MPK, MSK);
		}
		CompleteMSK(MSKD, MSK);
		CompleteMPK(MPKD, MPK);
		end = time_now;
		cout<<"Key Generation took    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
		cout << "Keys have been succefully generated. \n";	cout << "\n\n\n\n\n\n\n\n\n\n";
		sleep (1);
		goto labelReceiverMenu;
	}
	
	if (choiceReceiver == 2 ){
		flagTrapdoor = true;
		
		myTrapdoorGenerator(MSKD,SK_td);
		
	
		
		
		writeTrapdoorFile(skPath, SK_td);
		cout << "Trapdoor has been succefully generated. \n";	cout << "\n\n\n\n\n\n\n\n\n\n";
		
		
		sleep (1);
		goto labelReceiverMenu;
	}

	else if (choiceReceiver == 3){ sendTrapdoorToServer(skPath);
		goto labelReceiverMenu;}
	
	
	else if (choiceReceiver == 4 ){
		start = time_now;
		findFileByKeywordsServer(listOfFiles,  serverPath, serverPath);
		
		end = time_now;
	
		cout<<"Search time    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()/numOfFiles<<" ms"<<endl;
		
		
	
		for (std::set<string>::iterator it = listOfFiles.begin(); it != listOfFiles.end(); ++it) {
			cout << endl<<"The file name is" << *it <<endl<<endl;
		}
		if (listOfFiles.size() == 0) cout << "No email was found for the keyword: "<< keyword_str << "\n";
		cout << "\n\n\n\n\n\n\n\n\n\n";
		sleep(1);
		goto labelMain;
	}

	
	
	
	else if (choiceReceiver == 5){ goto labelMain;}
	
}

	if (choiceMain == 3){ 
	labelServerMenu:
		serverMenu();
		

		cin >> serverChoice;
		if (serverChoice == 1){
			receivingTrapdoorServer(serverPath); 
			goto labelServerMenu;
		}
			
	
		
		else if (serverChoice == 2){
			receivingPeksServer(serverPath); goto labelServerMenu;
		}
		else if (serverChoice == 3){ goto labelMain;}
	}






	if (choiceMain == 4){exit(1);}


//=========================================== MENU STUFF
















/*

    t2 = clock();
    diff = ((float)t2 - (float)t1)/1000000.0F;
    cout << "It took " << diff << " seconds to generate user keys" << endl;



    //==============================================================================
    //Key extraction bench and encryption/decryption bench
    //==============================================================================
    const unsigned int nb_trdb = 1000;
    const unsigned int nb_crypb = 1000;
    //const unsigned int nb_decrypb = 1000;


    cout << "\n===================================================================\n RUNNING PEKS BENCH FOR ";
    cout << nb_crypb << " DIFFERENT KEYWORDS\n===================================================================\n";
  // Encrypt_Bench(nb_crypb, MPKD, MSKD);


    cout << "\n===================================================================\n RUNNING TRAPDOOR BENCH FOR ";
    cout << nb_trdb << " DIFFERENT KEYWORDS\n===================================================================\n";
 //  Trapdoor_Bench(nb_trdb, MSKD);

    ///==============================================================================
    //Key extraction test and encryption/decryption test
    //==============================================================================
    const unsigned int nb_trdt = 100;
  const unsigned int nb_crypt = 100;


    cout << "\n===================================================================\n CHECKING PEKS VALIDITY FOR ";
    cout << nb_crypt << " DIFFERENT KEYWORDS\n===================================================================\n";
 //  Encrypt_Test(nb_crypt, MPKD, MSKD);

    cout << "\n===================================================================\n CHECKING TRAPDOOR VALIDITY FOR ";
    cout << nb_trdt << " DIFFERENT KEYWORDS\n===================================================================\n";*/
//Trapdoor_Test(nb_trdt, MSKD);

/*for (int i = 1; i < 2; i++){
	for (int j = 1; j < 5; j++){

		cout << SK_tr[i][j]<<endl;
		}}*/

	
//==============================================================================
//==============================================================================
//                               
//                      EXTRACTING AND ENCRYPTING KEYWORDS
//==============================================================================
//==============================================================================
	
/*	path = "/home/bob/Documents/MyCode/NTRU-PEKS/textfiles";
	string file_name;
	int counterKeys;
	for (int j = 1; j < numOfFiles; j++){
			string keywordExtracted[25];

	string temp;
	vec_ZZ keyword_zz;
	int rep[numOfKeywords] = {0};
		TYPE_KEYWORD_DICTIONARY myset;
		file_name = "/";
		temp = to_string(j);
		file_name.append(temp);
		file_name.append(".");
		//cout << file_name;
	extractKeywords(myset, file_name, path);
	writeKeywords(myset, file_name, path);
	extractKeywordFile(keywordExtracted,  file_name,path, counterKeys);
	KeywordstoPEKS(Ciphertext, Ciphertext2,file_name, path, keywordExtracted,counterKeys,MPKD);
		
	}*/
//==============================================================================
//==============================================================================
//                               
//                      COMPUTING TRAPDOOR
//==============================================================================
//==============================================================================


	//myTrapdoorGenerator(MSKD,SK_td);
//
//==============================================================================
//==============================================================================
//                               
//                      SEARCHING IN FILES
//==============================================================================

	

	free(MSKD);
	free(MPKD);	

    return 0;

}
