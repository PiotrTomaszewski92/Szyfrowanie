#ifndef RSA_CLASS
#define RSA_CLASS
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "side_functions.h"
using namespace std;
class rsa{
	long p,q;
	long n,m;
	long a,b;
	string text;
	class listEL{
	public:
		class oneBlock{
		public:
			string block;
			vector<int> numblock;
		}value;
		listEL *next;
		listEL();
	};
	listEL *head;
public:
	rsa();
	string& parseFile(string&);
	void createList();
	~rsa();
};

string& rsa::parseFile(string &directory){
	string wholetext = "", oneline;
	fstream textfile;
	textfile.open(directory, ios::out);
	if(textfile.is_open()){
		while(textfile.eof()){
			getline(textfile, oneline);
			wholetext += oneline;
		}
	}
	else cout << "Cannot open file!\n";
	textfile.close();
	return wholetext;
}

rsa::rsa(){
	head = new listEL;
	string directory;
	cout << "Please input the directory of your file to encrypt: ";
	cin >> directory;
	text = parseFile(directory);
	bool check; //in this part, we want user to input p and q
	do{
		check = false;
		cout << "Please input p: ";
		cin >> p;
		if(p<=0){
			cout << "p must be positive!\n";
			check = true;
		}
	}while(check);
	do{
		check = false;
		cout << "Please input q (it must be prime with p): ";
		cin >> q;
		if(q<=0 || p%q || q%p){
			cout << "q must be positive and prime with p!\n";
			check = true;
		}
	}while(check);

	n = p*q; //calculating n and m
	m = (p-1)*(q-1);

	do{  // in this part, we want user to input a and b
		check = false;
		cout << "Please input a and b:\n1<a<m and gcd(a,m)=1: ";
		cin >> a;
		if(a<=1 || a>=m || GCD(a,m)!=1){
			cout << "You have given the wrong number!\n";
			check = true;
		}
	}while(check);
	do{
		check = false;
		cout << "(a*b)mod m = 1: ";
		cin >> b;
		if((a*b)%m!=1){
			cout << "You have given the wrong number!\n";
			check = true;
		}
	}while(check);
}

rsa::listEL::listEL(){
	next = NULL;
}

void rsa::createList(){
	long i = 0;
	do{
		listEL *newel = new listEL;
		newel->value.block = text.substr(i, 10); // dividing the given text into 10-letter blocks
		for(int j = 0; j < 10; ++j) newel->value.numblock.push_back((int)newel->value.block[j]); //translating into ASCII
		newel->next = head->next; //adding the element to our list
		head->next = newel;
		delete newel;
		i+=10;
	}while(head->next->value.block.size()==10);
}

//------------------------DESTRUCTORS------------------------
rsa::~rsa(){
	listEL *help;
	if(head->next){
		while(head->next->next){
			help = head->next->next;
			delete head->next;
			head->next = help;
		}
		delete head->next;
	}
	delete head;
}

#endif