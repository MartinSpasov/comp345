

#ifndef QUERY_STRING_H_
#define QUERY_STRING_H_
#include "vector"
#include "document.h"
#include "indexer.h"
#include <algorithm>
using namespace std;


class Query_String{

private:
	vector<pair<document,double> > score;
public:
	Query_String(){}
	const vector<pair<document,double> > & scorevector(){
		return score;
	}
	template<int size>
	vector<pair<document,double> > query(indexer<size>  idx,string s,int n = 10){
		score.clear();
		if(!idx.isNormalize())
		throw idx.INDEX_NOT_NORMALIZED;
		tokenizer t;
		vector<string> tokens = t.tokenize(s);
		vector<string> filtered;
		for(int i=0;i<tokens.size();i++){
			if(!idx.getstpw()(tokens[i]))
			filtered.push_back(tokens[i]);
		}
		map<string,vector<int> > tftdq;
		map<string,vector<double> > wtdq;
		map<string,int> dftq;
		for(int i=0;i<size;i++){
			document d = idx[i];
			vector<string> docwords;
			docwords = t.tokenize(d.content());
			for(int j=0;j<filtered.size();j++){
				if(find(docwords.begin(),docwords.end(),filtered[j]) != docwords.end()){
					tftdq[filtered[j]].push_back(idx.getTFtd2()[filtered[j]][i]);
				}
				else tftdq[filtered[j]].push_back(0);
			}


		}
		for(map<string, vector<int> >::const_iterator it = tftdq.begin();it != tftdq.end();it++){
				string t = it->first;
				int df = 0;
				for(int j=0;j<tftdq[t].size();j++){
					if(tftdq[t][j] > 0)
						df++;
				}
				dftq[t] = df;
			}
			for(map<string, vector<int> >::const_iterator it = tftdq.begin();it != tftdq.end();it++){
				string t = it->first;
				for(int j=0;j<tftdq[t].size();j++){
					double s = size;
					double d = dftq[t];
					double tf = tftdq[t][j];
					double temp1 = 1+((double)log(tf)/(double)log(10));
					double temp2 = (double)log(s/d)/(double)log(10);
					double Wtd = temp1*temp2;
					if(Wtd == -INFINITY || Wtd == INFINITY || isnan(Wtd))
					wtdq[t].push_back(0);
					else
					wtdq[t].push_back(Wtd);
				}
			}

			for(int i=0;i<size;i++){
				double Wiqij = 0;
				double Wiq = 0;
				double Wij = 0;
				for(map<string, vector<double> >::const_iterator it = wtdq.begin();it != wtdq.end();it++){
					if(idx.getWtd()[it->first].size() != 0)
					Wiqij += (it->second[i] * idx.getWtd()[it->first][i]);
					Wiq += pow(it->second[i],2);
					if(idx.getWtd()[it->first].size() != 0)
					Wij += pow(idx.getWtd()[it->first][i],2);
				}
				double sc;
				if(Wiq == 0 || Wij == 0 || Wiqij == 0)
					sc = 0;
				else sc = Wiqij/(sqrt(Wiq)*sqrt(Wij));
				score.push_back(make_pair(idx[i],sc));
			}

			sort(score.begin(),score.end(), sortpairs);
			cout << endl << "******* Top scoring documents for the query \"" << s << "\"  *********" <<endl;
			for(int i=0;i<n;i++){
				cout << left << setw(20) << score[i].first.name() << right << setw(20) << score[i].second << endl;
			}
			return score;
	}

};

bool sortpairs(const pair<document,double> &a,const pair<document,double> &b){
    return (a.second > b.second);
}


#endif /* QUERY_STRING_H_ */
