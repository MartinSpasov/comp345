/*
 * indexer.h
 *
 *  overridding operato >> with templates doesnt work when implemented in indexer.cpp
 *  I searched the net and found that it has to be implemented in the .h file
 *
 *
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include "document.h"
#include "stopwords.h"
#include "tokenizer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
using namespace std;

template<int size>
class indexer{

private:
	int N; // number of documnents
	bool normalized; // keep tracking of normalized status
	stopwords stpw; // stopword list
	vector<document> documents;
	map<string,int> dft; // number of documents a token appears in
	map<string,vector<int> > tftd1; // total tokens or words
	map<string,vector<int> > tftd2; // tokens with removed stopwords
	map<string,vector<double> > wtd; // weight of token in each document
	vector<int>total1;
	vector<int>total2;
public:
	indexer<size>()
	:N(0),normalized(false),stpw(stopwords("stopwords.txt"))
	{

	}
	int indexersize(){
		return size;
	}
	bool isNormalize(){
		return normalized;
	}
	stopwords getstpw(){
		return stpw;
	}
	vector<document> getdocuments(){
		return documents;
	}
	map<string,vector<int> > getTFtd2(){
		return tftd2;
	}
	map<string,vector<double> > getWtd(){
		return wtd;
	}
	void normalize(){
	normalized = true;
		// looping on the filtered tokens and calculating the document frequency for each token
		for(map<string, vector<int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
			string t = it->first;
			int df = 0;
			for(int j=0;j<tftd2[t].size();j++){
				if(tftd2[t][j] > 0)
					df++;
			}
			dft[t] = df;
		}

		// looping on the filtered tokens and calculating the document weight wt,d for each token
		for(map<string, vector<int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
			string t = it->first;
			for(int j=0;j<tftd2[t].size();j++){
				// formula from assignment
				double s = indexersize();
				double d = dft[t];
				double tf = tftd2[t][j];
				double temp1 = 1+((double)log(tf)/(double)log(10));
				double temp2 = (double)log(s/d)/(double)log(10);
				double Wtd = temp1*temp2;
				if(Wtd == -INFINITY || Wtd == INFINITY || isnan(Wtd))
				wtd[t].push_back(0);
				else
				wtd[t].push_back(Wtd);
			}
		}
	}
	const document & operator [](int n){
		return documents[n];
	}
	friend const document & operator >>(document & d,indexer<size> & idx){
			idx.normalized = false; // reading new document so indexer not normalized
			idx.documents.push_back(d); // pushing document to documnet vector
			string cont = d.content(); // string content of document
			int total_1 = 0;
			int total_2 = 0;
			tokenizer t;
			vector<string> tokens = t.tokenize(cont); // changing the content of document into tokens

			// same as assignment 1 pushing zeros then incrementing the token
			for(int i=0;i<tokens.size();i++){
				string s = tokens[i];
				if(idx.stpw(s)){
				if(idx.tftd1[s].size() == 0){
				for(int i=0;i<size;i++){
						idx.tftd1[s].push_back(0);
					}
				}
				idx.tftd1[s][idx.N]++;
				total_1++;
				}
				else{
					if(idx.tftd1[s].size() == 0){
					for(int i=0;i<size;i++){
							idx.tftd1[s].push_back(0);
						}
					}
					idx.tftd1[s][idx.N]++;

					if(idx.tftd2[s].size() == 0){
					for(int i=0;i<size;i++){
							idx.tftd2[s].push_back(0);
						}
					}
					idx.tftd2[s][idx.N]++;
					total_1++;
					total_2++;
				}
			}
			idx.total1.push_back(total_1);
			idx.total2.push_back(total_2);
			idx.normalize();
			idx.N++; // counter for index of which document is read
			return d;
	}
	friend ostream & operator <<(ostream & os,indexer<size> & idx){
		os << endl << "******* Full Document Matrix version *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<idx.documents.size();++i){
				os << right << setw(20) << idx.documents[i].name();
			}
			os << endl;
			for(map<string,vector<int> >::iterator it = idx.tftd1.begin();it != idx.tftd1.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}
			os << left << setw(20) << "Total";
			for(int i=0;i<idx.total1.size();i++){
				os << right << setw(20) << idx.total1[i];
			}
			os << endl;
			os << endl << "******* Filtered Document Matrix version *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<idx.documents.size();++i){
				os << right << setw(20) << idx.documents[i].name();
			}
			os << endl;
			for(map<string,vector<int> >::iterator it = idx.tftd2.begin();it != idx.tftd2.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}
			os << left << setw(20) << "Total";
			for(int i=0;i<idx.total2.size();i++){
				os << right << setw(20) << idx.total2[i];
			}
			os << endl;
			os << endl << "******* Document Frequency *********" <<endl;
			os << left << setw(20) << "Dictionary" <<  right << setw(20) << "Document Frequency" << endl;
			for(map<string,int >::iterator it = idx.dft.begin();it != idx.dft.end();++it)
			os << left << setw(20) << it->first << right << setw(20) << it->second << endl;

			os << endl << "******* Tf-idf weight *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<idx.documents.size();++i){
				os << right << setw(20) << idx.documents[i].name();
			}
			os << endl;
			for(map<string,vector<double> >::iterator it = idx.wtd.begin();it != idx.wtd.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}

				return os;
	}
	enum Exceptions { INDEX_NOT_NORMALIZED };

};

bool sortpairs(const pair<document,double> &a,const pair<document,double> &b);


#endif /* INDEXER_H_ */


