//Authors
// Martin Spasov 40000916
// Mohamed Omar 40013242
// Loïc Huss - 40000298

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void fillDictionary(const string&, int, int);
void printDictionary(vector<string>&, map<string,vector<int> >&, vector<int>&);

map<string,vector<int> > fullDictionary;
map<string,vector<int> > noStopwordsDictionary;
vector<int> total;
vector<int> noStopwordsTotal;

vector<string> stopWords;

int main(){
    ifstream stopWordStream("stopwords.txt");
    string stopWord;
    //transform the stopword the same way all words will be transformed when added to the dictionary.
    while(stopWordStream >> stopWord){
        //makes the word lowercase
        transform(stopWord.begin(), stopWord.end(), stopWord.begin(), ::tolower);

        //removes punctuation
        for(auto iter = stopWord.begin(); iter != stopWord.end(); iter++){
            if(ispunct(*iter)){
                stopWord.erase(iter);
                break;
            }
        }
        stopWords.push_back(stopWord);
    }
    stopWordStream.close();

    cout << "Please enter the index file name." << endl;
    string indexFileName;
    cin >> indexFileName;

    ifstream inStream(indexFileName);

    if(!inStream){
        cout << "Unable to find index file" << endl;
        return 1;
    }

    vector<string> fileNames;
    string fileName;
    while(inStream >> fileName){
        fileNames.push_back(fileName);
    }
    inStream.close();

    for(unsigned int i = 0; i < fileNames.size(); i++){
        cout << "Reading from " << fileNames[i] << endl;
        fillDictionary(fileNames[i], i, fileNames.size());
    }

    cout << endl << "******* Document Matrix version 1 *********" << endl;
    printDictionary(fileNames, fullDictionary, total);

    cout << endl << "******* Document Matrix version 2 (no stopwords) *********" << endl;
    printDictionary(fileNames, noStopwordsDictionary, noStopwordsTotal);

    string closeMe;
    cin >> closeMe;
    return 0;
}

void fillDictionary(const string& fileName, int currentFile, int totalFile){
    ifstream inStream(fileName);
    string tempString;
    int totalCount = 0, noStopwordsCount = 0;
    while(inStream >> tempString){

        //makes the word lowercase
        transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);

        //removes punctuation
        for(auto iter = tempString.begin(); iter != tempString.end(); iter++){
            if(ispunct(*iter)){
                tempString.erase(iter);
                break;
            }
        }

        bool isNotAStopword = (find(stopWords.begin(),stopWords.end(), tempString) == stopWords.end());

        if(fullDictionary.find(tempString) == fullDictionary.end()){
            //if the word does not yet exist in the dictionary for that file, add it then increment
            for(int i = 0; i < totalFile; i++){
                fullDictionary[tempString].push_back(0);
            }
        }
            fullDictionary[tempString][currentFile]++;

        //do the same thing for stopword dictionary
        if(isNotAStopword) {
            if (noStopwordsDictionary.find(tempString) == noStopwordsDictionary.end()) {
                for (int i = 0; i < totalFile; i++) {
                    noStopwordsDictionary[tempString].push_back(0);
                }
            }
               noStopwordsDictionary[tempString][currentFile]++;
        }

        totalCount++;
        if(isNotAStopword) {
            noStopwordsCount++;
        }
    }
    total.push_back(totalCount);
    noStopwordsTotal.push_back(noStopwordsCount);
}

void printDictionary(vector<string>& fileNames, map<string,vector<int> >& dictionary, vector<int>& totals){
    cout << left << setw(20) << "Dictionary";
    for(unsigned int i=0;i<fileNames.size();++i){
        cout << right << setw(5) << "DOC" << (i+1);
    }
    cout << endl;

    for(map<string,vector<int> >::iterator it = dictionary.begin();it != dictionary.end();++it){
        //first, print the word
        cout << left << setw(20) << it->first;
        //then, iterate through the files and print the occurence of each word in each file
        for(unsigned int i=0;i<it->second.size();i++){
            cout << right << setw(5) << it->second[i];
        }
        cout << endl;
    }

    //After printing every word, display the total.
    cout << left << setw(20) << "Total";
    for(unsigned int i=0;i<totals.size();i++){
        cout << right << setw(5) << totals[i];
    }
    cout << endl;
}
