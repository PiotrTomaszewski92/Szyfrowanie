#ifndef RSA_CLASS
#define RSA_CLASS
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
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
			string block; //block of 10-letter text
			vector<long> numblock; //translated block of text to ASCII
			vector<long> encrypted; //the same block, but encrypted
			//string encryptedblock; //encrypted text
		}value;
		listEL *next;
		listEL();
	};
	listEL *head;
public:
	rsa();
	void parseFile(string&);
	void createList();
	~rsa();
	void encrypt();
};

void rsa::parseFile(string &directory){
	string oneline;
	fstream textfile;
	textfile.open(directory, ios::in);
	if(textfile.is_open()){
		while(!textfile.eof()){
			getline(textfile, oneline);
			text.append(oneline);
		}
	}
	else cout << "Cannot open file!\n";
	textfile.close();
}

rsa::rsa(){
	head = new listEL;
	string directory;
	cout << "Please input the directory of your file to encrypt: ";
	cin >> directory;
	parseFile(directory);
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
		cout << "Please input q (p and q must be coprime!): ";
		cin >> q;
		if(q<=0 || p%q==0 || q%p==0){
			cout << "q must be positive and prime with p!\n";
			check = true;
		}
	}while(check);

	n = p*q; //calculating n and m
	m = (p-1)*(q-1);
	cout << "n = " << n << "\nm = " << m << endl;

	do{  // in this part, we want user to input a and b
		check = false;
		cout << "Please input a:\n1<a<m and gcd(a,m)=1: ";
		cin >> a;
		if(a<=1 || a>=m || GCD(a,m)!=1){
			cout << "You have given the wrong number!\n";
			check = true;
		}
	}while(check);
	b = mod_inv(a, m); //modular inversion (a^(-1)mod m)
	cout << "b = " << b << " (a^(-1) mod m)\n";
}

rsa::listEL::listEL(){
	next = NULL;
}

void rsa::createList(){
	long i = 0;
	listEL *newel;
	do{
		newel = new listEL;
		newel->value.block = text.substr(i, 10); // dividing the given text into 10-letter blocks
		for(int j = 0; j < newel->value.block.size(); ++j) newel->value.numblock.push_back((long)newel->value.block[j]); //translating into ASCII
		newel->next = head->next; //adding the element to our list
		head->next = newel;
		i+=10;
	}while(head->next->value.block.size()==10);
}

void rsa::encrypt(){
	listEL *pointhelp = head->next;
	long power;
	while(pointhelp){
		for(int j=0; j<10; ++j){
			power = pow(pointhelp->value.numblock[j],a);
			pointhelp->value.encrypted.push_back(power%m);
			//pointhelp->value.encryptedblock.push_back(static_cast<char>(pointhelp->value.encrypted[j]));
			cout << pointhelp->value.encrypted[j] << ',';
		}
		pointhelp = pointhelp->next;
	}
	delete pointhelp;
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