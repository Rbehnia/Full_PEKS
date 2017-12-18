/*
   Boneh, Di Crescenzo, Ostrovsky & Persiano
   Public Key Encryption with keyword Search

   See http://eprint.iacr.org/2003/195.pdf
   Section 3.1

   (From reading the protocol to a working implementation - 10 minutes!)

   Compile with modules as specified below

   For MR_PAIRING_CP curve
   cl /O2 /GX peks.cpp cp_pair.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_MNT curve
   cl /O2 /GX peks.cpp mnt_pair.cpp zzn6a.cpp ecn3.cpp zzn3.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib
	
   For MR_PAIRING_BN curve
   cl /O2 /GX peks.cpp bn_pair.cpp zzn12a.cpp ecn2.cpp zzn4.cpp zzn2.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_KSS curve
   cl /O2 /GX peks.cpp kss_pair.cpp zzn18.cpp zzn6.cpp ecn3.cpp zzn3.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   For MR_PAIRING_BLS curve
   cl /O2 /GX peks.cpp bls_pair.cpp zzn24.cpp zzn8.cpp zzn4.cpp zzn2.cpp ecn4.cpp big.cpp zzn.cpp ecn.cpp miracl.lib

   Test program 
*/
#include <cstring>
#include "big.h"
#include <ctime>
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "zzn.h"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <sstream>
#include "params-peks.h"
#include <zmq.hpp>
 
using namespace std;

//********* choose just one of these pairs **********
//#define MR_PAIRING_CP      // AES-80 security   
//#define AES_SECURITY 80

//#define MR_PAIRING_MNT	// AES-80 security
//#define AES_SECURITY 80

//#define MR_PAIRING_BN    // AES-128 or AES-192 security
//#define AES_SECURITY 128
//#define AES_SECURITY 192

//#define MR_PAIRING_KSS    // AES-192 security
//#define AES_SECURITY 192

//#define MR_PAIRING_BLS    // AES-256 security
//#define AES_SECURITY 256
//*********************************************
#include "pairing_3.h"
#include "ecn.h"
#include "miracl.h"

PFC pfc(AES_SECURITY);  // initialise pairing-friendly curve


	
void keyGen(string path,G1	&g, Big &alpha, G1& h );
void boneh_Peks(G1 g,G1 h, G1 &PA, Big &PB,string keyword);
void boneh_Trapdoor(Big alpha,G2 &TW, string keyword);
bool boneh_Test(G2 TW, G1 PA, Big PB);
//==========================================================================================================
string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

const char* const delimiter = "`-=[]\\;\',./~!@#$%^&*()+{}|:\"<>? \n\t\v\b\r\f\a"; 
bool is_word(std::string& s){
	bool flagd =true, flagc = false;  int count = 0;
	std::string::iterator it = s.begin();
    for (it = s.begin();it != s.end(); ++it)  {
		count++;
		if (std::isalpha(*it)){}
		else{
			flagd = false; 	
			}
		if (count > 2)  flagc = true;
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
	//fname_with_path.append(".txt");

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
	set<string>::iterator it;

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
void extractKeywordFile(string *keywordExtracted, int &keywordCounter, string file_name, string path)
{
    ifstream ifile;
	string fname_with_path;
	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("kw");
	// Opening file to read the keywords from it. 
    ifile.open(fname_with_path.c_str());
    if (!ifile.is_open()) 
		{cout << "No such file exist"<<endl;}
	string word;
	keywordCounter = 0; 
    while (ifile >> word)
    {
		keywordExtracted[keywordCounter] = word;
		keywordCounter++;
     }
	for (int key = 0;key<numOfKeywords;key++)
		cout << file_name << "   "<< keywordExtracted[key]<<endl;
	ifile.close();
}

// Stores the PEKS obtained from the function below in the file. 

void writePEKStoFile(string file_name, string path, G1  PA, Big PB){
	
	char testing[200]; 
	cout << "PA = " << PA.g << endl;

	Big x = 1;
	Big y = 1;
	PA.g.getxy(x,y);


	string fname_with_path;
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("sc");
	
	ofstream ofile;
	ofile.open (fname_with_path.c_str(), ios_base::app | ios::binary); 
	ofile<<x ;
	testing << x;
	ofile<<endl;
	ofile << y << endl;
	
	ofile << PB;
	ofile<<endl;
	ofile.close();
}
	
//Function to encrypt keywords and store them in file using writePEKStoFile function

void KeywordstoPEKS(G1  PA, Big PB,string file_name, string path, G1 g, G1 h, string keywordExtracted[numOfKeywords], int  keywordCounter)
	{
	string keyword;
	for (int i = 0; i < numOfKeywords; i++){
			keyword = keywordExtracted[i];
			boneh_Peks(g, h, PA, PB, keyword);
		//	Finished Boneh Peks, writing PEKS to file";
			writePEKStoFile(file_name,path,PA, PB);
		
	}


}

//void boneh_Trapdoor(Big alpha,G2 &TW, string keyword)
void myTrapdoorGenerator(Big alpha,G2 &TW, string& keyword){
	
	string word;
	cout << endl<<"Please keyin the keyword you would like to be searched: ";
	cin >> keyword;
	boneh_Trapdoor(alpha, TW, keyword);


}

void findFileByKeywords(TYPE_KEYWORD_DICTIONARY & listOfFiles, string file_name, string path, G2 TW){
	cout << "We are in Find FILE BY KEYWORD now: "<<endl<<endl;
	int rep;
	bool flagvalid = false; 

	int counter = 0;

    string line1 = "";
    string line2 = "";	
	string temp1,temp2="",fileNameforList="", fname_with_path;
	fstream ifile;

	
	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		string line1 = "";string line0 = "";
		string line2 = "";	
		string line3 = "";
		 
		
		fstream ifile;
		fname_with_path = "";
		fname_with_path.append(path);
		file_name = "";
		file_name.append("/");
		temp1 = std::to_string(filecount);

		file_name.append(temp1);
		fileNameforList.append(file_name);
		//fileNameforList.append(".");
		file_name.append("sc");
		fname_with_path.append(file_name);

		ifile.open(fname_with_path.c_str());
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		string word ="";
		string target = "";
		int i = 0;
		
		while (i < numOfKeywords){

			epoint *temp;

			Big x = 1;
			Big y = 1;
			
			
			
		
			Big  PB =1; G1 PA;

			ifile>>x;
			ifile>>y;
			
			ifile>>PB;
			
			ECn point;
			bool flag = point.set(x,y);
			if(flag == true)
			{
				cout<<"Good!"<<endl;
			}
			
			PA.g = point;


			i++;

			if (boneh_Test( TW, PA, PB)){
				listOfFiles.insert(file_name);
			}

		}
			


		
	}
	ifile.close();

}



void writekeystoFile( string path,const G1 g, const Big alpha, const G1 h){
	
	cout << "g = " << g.g << endl;
	cout << "h = " << h.g << endl;
	Big x = 1;
	Big y = 1;
	Big xx =1;
	Big yy =1;
	g.g.getxy(x,y);
	h.g.getxy(xx,yy);

	string fname_with_path;
	//recreate the file name
	fname_with_path.append(path);
	fname_with_path.append("/keyfile");
	cout << fname_with_path<<endl;
	ofstream ofile;
	ofile.open (fname_with_path.c_str(),  ios::binary); 
	ofile << x ;
	

	//cout << "/n/n/n/"<< "Hi This is x -----> "<< testing<<endl;
	ofile<<endl;
	ofile << y << endl;
	ofile<< alpha<<endl;
	ofile << xx<<endl;
	ofile << yy<<endl;
	ofile.close();
}
void readKeyFromFile ( string path, G1& g, Big& alpha, G1& h){
	
		string fname_with_path_key;
		fstream ifile;
		fname_with_path_key = "";
		fname_with_path_key.append(path);

		fname_with_path_key.append("/keyfile");
		ifile.open(fname_with_path_key.c_str());
		
	epoint *temp;

	Big x = 1;
	Big y = 1;
	Big xx = 1;
	Big yy = 1;

	ifile>>x;
	ifile>>y;
	
	ifile>>alpha;
	ifile >> xx;
	ifile>>yy;
	ECn point1;
	bool flag = point1.set(x,y);
	if(flag == false)
	{
		cout<<"Error in loading keys!"<<endl;
	}
	
	g.g = point1;
	
	ECn point2;
	bool flag1 = point2.set(xx,yy);
	if(flag1 == false)
	{
		cout<<"Error in loading keys1!"<<endl;
	}
	h.g = point2;
	
	
	
	}
//= ===== write trapdoor to file 


void writeTrapdoorFile(string fname_with_path,  G2 TW){
	
	ZZn3 x;
char a[2] = {'0','1'};
ZZn mya(a);
	ZZn3 y;
	ZZn atx;
	ZZn btx;
	ZZn ctx;
	ZZn aty;
	ZZn bty;
	ZZn cty;
	ECn3 mypoint; 
	mypoint = TW.g;
	cout << "The value of mypoint is : "<<mypoint<<endl;
	cout << "The value of Trapdoor is : "<<TW.g<<endl;
	mypoint.get(x,y);
	cout << "The value of x is : "<<x<<endl;
	cout << "The value of y is : "<<y<<endl;
	x.get(atx,btx,ctx);
	cout << "The value of a is : "<<atx<<endl;
	cout << "The value of b is : "<<btx<<endl;
	cout << "The value of c is : "<<ctx	<<endl;
	x.get(atx,btx,ctx);
	cout << "The value of aaaa is : "<<a	<<endl;
	y.get(aty,bty,cty);

	//string fname_with_path;
	//recreate the file name

	fname_with_path.append("trapdoor");
	
	ofstream ofile;
	ofile.open (fname_with_path.c_str(),  ios::binary); 
	ofile << atx <<endl<<btx <<endl<<ctx<<endl <<aty<<endl<<bty<<endl<<cty<<endl ;


	ofile.close();
}


void sendTrapdoorToServer(string file_name, string path){
    zmq::context_t context(1);
	zmq::socket_t socket(context,ZMQ_REQ);
	printf("   Connecting to server...");
	//socket.connect ("tcp://localhost:5559");
	socket.connect ("tcp://52.26.80.225:5559");
	printf("OK!\n");
	string line1 = "";
	string fname_with_path;
	size_t sizeLine1 = 0;
	auto start = time_now;
    auto end = time_now;
	float sum = 0.0;
	
	fstream ifile;
	fname_with_path = "";
	fname_with_path.append(path);
	//file_name = "";
	//file_name.append("/");
	fname_with_path.append(file_name);
	size_t size1;
	ifile.open(fname_with_path.c_str());
	if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		while(ifile >> line1){
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

	cout<<	"Sending Trapdoor takes   "<<sum<<" microseconds"<<endl;
		
			
	ifile.close();
	socket.close();


		
	}












//=== Send data to server


void sendPeksToServer(string file_name, string serverPath){
    zmq::context_t context(1);
	zmq::socket_t socket(context,ZMQ_REQ);
	printf("   Connecting to server...");
	//socket.connect ("tcp://localhost:5560");
	socket.connect ("tcp://52.26.80.225:5560");
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
		fname_with_path.append(serverPath);
		file_name = "";
		file_name.append("/");
		temp1 = std::to_string(filecount);
		file_name.append(temp1);
		file_name.append("sc");
		fname_with_path.append(file_name);
		size_t size1, size2,size3;
		ifile.open(fname_with_path.c_str());
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		int i = 0;
		while (i < numOfKeywords){
			
			line1 = "";line2 = "";line3 = "";
			ifile>>line1;
			ifile>>line2;
			ifile>>line3;
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
	
	cout << "All files have been received and stored in "<< serverPath << "folder "<< endl;
	ifile.close();
	socket.close();


		
	}
	
	
	
// ================== SERVER SIDE
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
		temp1 = std::to_string(filecount);
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
    while (numOfLinesTrapdoor < 6) {
		
        zmq::message_t request1;
        socket.recv (&request1);
        string rpl1 = string(static_cast<char*>(request1.data()), request1.size());
        cout <<  rpl1<< endl;
		
		zmq::message_t reply1 (8);
        memcpy (reply1.data (), "World", 8);
        socket.send (reply1);
		
		writeTrapdoortoFileServer(serverPath, rpl1);

		numOfLinesTrapdoor++; 



    }


	
	cout << "All files have been received and stored in "<< serverPath << "folder "<< endl;
	socket.close();
	
}




void findFileByKeywordsServer(TYPE_KEYWORD_DICTIONARY & listOfFiles, string file_name, string path, string serverPath){
	
	
	G2 TW;
	string tdfname = "";
	tdfname.append(serverPath);
	tdfname.append("trapdoor");
	ZZn3 x; ZZn3 y;
	ECn3 point;
	Big aux1 = 1;	Big aux2 = 1;
	Big aux3 = 1;	Big aux4 = 1;
	Big aux5 = 1;	Big aux6 = 1;
	ifstream fileTrapdoor;
	fileTrapdoor.open(tdfname.c_str());
	fileTrapdoor >> aux1;fileTrapdoor >> aux2;
	fileTrapdoor >> aux3;fileTrapdoor >> aux4;
	fileTrapdoor >> aux5;fileTrapdoor >> aux6;
	ZZn atx(aux1);
	ZZn btx(aux2);
	ZZn ctx(aux3);
	ZZn aty(aux4);
	ZZn bty(aux5);
	ZZn cty(aux6);
	x.set(atx,btx,ctx);
	y.set(aty,bty,cty);
	point.set(x,y);
	TW.g = point;
	cout << "We are in THE TESTING FUNC and the value is "<<TW.g<<endl;
	sleep(3);
	fileTrapdoor.close();
	
	
	int rep;
	bool flagvalid = false; 

	int counter = 0;

    string line1 = "";
    string line2 = "";	
	string temp1,temp2="",fileNameforList="", fname_with_path;
	fstream ifile;
		
	
	for (int filecount = 1; filecount < numOfFiles; filecount++)
	{	    
		string line1 = "";string line0 = "";
		string line2 = "";	
		string line3 = "";
		 
		
		fstream ifile;
		fname_with_path = "";
		fname_with_path.append(path);
		file_name = "";
		file_name.append("/");
		temp1 = std::to_string(filecount);

		file_name.append(temp1);
		fileNameforList.append(file_name);
		//fileNameforList.append(".");
		file_name.append("sc");
		fname_with_path.append(file_name);

		ifile.open(fname_with_path.c_str());
		if (!ifile.is_open()){cout << "The file "<<fname_with_path<< "is NOT fine \n"<<endl;}
		string word ="";
		string target = "";
		int i = 0;
		
		while (i < numOfKeywords){

			epoint *temp;

			Big x = 1;
			Big y = 1;
			
			
			
		
			Big  PB =1; G1 PA;

			ifile>>x;
			ifile>>y;
			
			ifile>>PB;
			
			ECn point;
			bool flag = point.set(x,y);
			if(flag == true)
			{
				cout<<"Good!"<<endl;
			}
			
			PA.g = point;


			i++;

			if (boneh_Test(TW, PA, PB)){
				listOfFiles.insert(file_name);
			}

		}
			


		
	}
	ifile.close();

}


//=========================================================================================================

void mainMenu(){
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "Select one of the following: \n";
	cout << "(1) Sender\n";
	cout << "(2) Receiver\n";
	cout << "(3) Server\n";
	cout << "(4) Exit\n";

	cout << "Choice: ";

}
void senderMenu(string path, const bool flagEnc, int numOfFiles){
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
	string filename = "/keyfile";
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
	



int main()
{   
	
	bool flagEnc = false; bool flagTrapdoor = false;
	time_t seed;
	time(&seed);
    irand((long)seed);
    clock_t t1, t2;  
	float diff;
	G1 g,h,PA,PA1;
	Big alpha,r,PB;
	GT t;
	G2 HW,TW;
	TYPE_KEYWORD_DICTIONARY listOfFiles;
	string keyword;
	const unsigned int nb_trdb = 100;
    const unsigned int nb_crypb = 100;
	unsigned int i;
	string path = "/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles";
	string file_name; 
	int keywordCounter;
	int choiceMain, choiceSender,choiceReceiver,serverChoice;
	auto start = time_now;
    auto end = time_now;
	float sum = 0.0;
// This function is run by Alice, the reciever,  to generate pk and sk. 

	labelMain: mainMenu( );
	string fname_with_path_key;
	fstream ifiles;
	fname_with_path_key = "";
	fname_with_path_key.append(path);

	fname_with_path_key.append("/keyfile");
	ifiles.open(fname_with_path_key.c_str());
	if (ifiles.is_open()){ 
	readKeyFromFile (path,g,alpha,h);
	}

	cin >> choiceMain;
	cout << "\n\n\n\n\n\n\n\n\n\n";

if (choiceMain == 1){
	labelSenderMenu:
	senderMenu( path,   flagEnc, numOfFiles);
	cin >> choiceSender;
	if (choiceSender == 1){
		cout << "Please keyin the new path: ";
		cin >> path;
		goto labelSenderMenu;
	}
	else if (choiceSender == 2){
		cout << "Please keyin the number of files: ";
		cin >> numOfFiles;
		goto labelSenderMenu;
	}
	else if (choiceSender == 3){
		
		
		for (int j = 1; j < numOfFiles; j++){
	
			string keywordExtracted[25];
			string temp;
			int rep[numOfKeywords] = {0};
			TYPE_KEYWORD_DICTIONARY myset;
			file_name = "/";
			temp = std::to_string(j);
			file_name.append(temp);
		//	file_name.append(".");
			extractKeywords(myset, file_name, path);
			writeKeywords(myset, file_name, path);
			extractKeywordFile(keywordExtracted, keywordCounter, file_name,path);
			start = time_now;
			KeywordstoPEKS(PA, PB,file_name, path,g,h, keywordExtracted, keywordCounter);
			end = time_now;
			sum += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
			cout << "Keywords have been successfully extracted and stored in .kw files. \n";
			cout << "Keywords have been encrypted for each file and stored in .sc files. \n";	cout << "\n\n\n\n\n\n\n\n\n\n";
		
		}
		cout<<"Generate PEKS, each file takes   "<<sum/numOfFiles<<" ms on average"<<endl;
		flagEnc = true;

	}
	else if (choiceSender == 4){
		sendPeksToServer(file_name,path);
		goto labelSenderMenu;
	}
		
	
	else if (choiceSender == 5){ goto labelMain;}
	sleep(1);
	goto labelSenderMenu;
	
	
	
	
	
	
}
	
if (choiceMain == 2){
	labelReceiverMenu: 
	receiverMenu(flagTrapdoor,path);
	cin >> choiceReceiver;
	if (choiceReceiver == 1 ){
		keyGen(path, g, alpha,h);
		cout << "Keys have been succefully generated. \n";	cout << "\n\n\n\n\n\n\n\n\n\n";
		sleep (1);
		goto labelReceiverMenu;
	}
	
	if (choiceReceiver == 2 ){
		flagTrapdoor = true;
		myTrapdoorGenerator( alpha,TW, keyword);
		cout << "Trapdoor has been succefully generated. \n";	cout << "\n\n\n\n\n\n\n\n\n\n";
		sleep (1);
		goto labelReceiverMenu;
	}

	else if (choiceReceiver == 3){ sendTrapdoorToServer("trapdoor", "/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server/");  goto labelReceiverMenu;}
	
	
		else if (choiceReceiver == 4 ){
		//findFileByKeywords(listOfFiles,  file_name,  path,  TW);
		start = time_now;
		findFileByKeywordsServer( listOfFiles,  file_name,  "/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server", "/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server2/");
		end = time_now;
	
		cout<<"Search time    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()/numOfFiles<<" ms"<<endl;
		for (set<string>::iterator it = listOfFiles.begin(); it != listOfFiles.end(); ++it) {
			cout <<"The file name is" << *it <<endl<<endl;
		}
		if (listOfFiles.size() == 0) cout << "No email was found for the keyword: "<< keyword << "\n";
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
		receivingTrapdoorServer("/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server2/"); goto labelServerMenu;
	}
	else if (serverChoice == 2 ){
	receivingPeksServer("/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server"); goto labelServerMenu;
	}
	else if (serverChoice == 3) {goto labelMain;}
}

if (choiceMain == 4){exit(1);}

				
	

    return 0;
}

void keyGen(string path,G1& g, Big& alpha, G1& h) {
	auto start = time_now;
    auto end = time_now;
	start = time_now;
	pfc.random(g);	
	pfc.precomp_for_mult(g);  // precompute on fixed g
	pfc.random(alpha);		  // private key
	h=pfc.mult(g,alpha);      // public key
	pfc.precomp_for_mult(h);
	end = time_now;
	
	cout<<"Key Generation took    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
	writekeystoFile(path,g,alpha,h);
}

void boneh_Peks(G1 g,G1 h, G1 &PA,Big &PB, string keyword)
{
	Big r;
	GT t;
	G2 HW;
	pfc.random(r);
	pfc.hash_and_map(HW,(char *)keyword.c_str());
	t=pfc.pairing(HW,pfc.mult(h,r));
	PA=pfc.mult(g,r);
	PB=pfc.hash_to_aes_key(t);    // [PA,PB] added to ciphertext
}

void boneh_Trapdoor(Big alpha,G2 &TW, string keyword)
{	
	auto start = time_now;
    auto end = time_now;
	start = time_now;
	G2 HW;
	pfc.hash_and_map(HW,(char *)keyword.c_str()); // key word we are looking for
	TW=pfc.mult(HW,alpha);
	pfc.precomp_for_pairing(TW);
	
	end = time_now;
	
	cout<<"Trapdoor Generation took    "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" ms"<<endl;
	
	cout << "This is what you want in file  "<< TW.g<<endl;
	writeTrapdoorFile("/home/bob/Desktop/80BonehPeks/80BonehPeks/textfiles/server/",TW);
}
bool boneh_Test(G2 TW, G1 PA, Big PB)
{
	if (pfc.hash_to_aes_key(pfc.pairing(TW,PA))==PB){
		cout << "yes it does work" << endl;
		return true;
	}
	
	else{
		cout << "It did not work"<<endl;
		return false;
	}
	
}
