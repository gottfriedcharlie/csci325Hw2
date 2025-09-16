#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <limits>
#include <cctype>
#include <iterator>

using namespace std;

//sort the text into k rows, then find the ioc of k rows and return the largest ioc


//english frequency of letters a-z
static const double english[26] = {
  0.08167,0.01492,0.02782,0.04253,0.12702,0.02228,0.02015,0.06094,0.06966,
  0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.00095,0.05987,
  0.06327,0.09056,0.02758,0.00978,0.02360,0.00150,0.01974,0.00074
};

//convert all to upper and remove spaces
string prepText(string& raw_contents){
    string finalText;
    for (char c : raw_contents){
        c = toupper((unsigned char) c);
        if (c != ' '){
            finalText += c;
        }
    }
    return finalText;
}

//this will return the column of contents of k
//it is a vector of strings beacuse ther could be k cols 
vector<string> coloumns (const string& contents, int k){
    vector<string> coloumn(k); //creates a vector with k elements each element being a string
    for (int i = 0; i < contents.length(); i++){
        coloumn[i % k].push_back(contents[i]);
    }
    return coloumn;
}

double avgIoC(const string& text) {
    int intList[26] = {0};  //array of 26 ints init to 0
    int N = 0;

    for (char ch : text) {
        if (ch >= 'A' && ch <= 'Z') { 
            intList[ch - 'A']++; //increments the letters count
            N++;//every letter counted
        }
    }

    if (N < 2) return 0.0; //added so it stops error it was dividing by zero without 
    long long num = 0; //needed to be long long so longer shit fits
    for (int c : intList) {
        num += 1LL * c * (c - 1);
    }

    return static_cast<double>(num) / (N * (N - 1));
}

//calculates the averge IoC for each K
double KIoc (const string& s, int k){
    vector<string> cols = coloumns(s, k);
    double sum = 0.0;
    for (const string& s : cols) {
         sum += avgIoC(s); 
    }
    return sum / k;
}

double chiSquareShift(const string& col, int s) {
    const int N = static_cast<int>(col.size()); //letter in col
    if (N == 0) return std::numeric_limits<double>::infinity(); //if none make it largest possible chi score

    int counts[26] = {0};

    //this unshifts the text by s, this will return the count for every letter if shift was k
    for (char c : col) {
        int cipher = c - 'A';               
        int possiblePlain = (cipher - s + 26) % 26;    
        counts[possiblePlain]++;                  
    }

    double chi = 0.0;
    for (int i = 0; i < 26; ++i) {
        double expected = N * english[i];   //expected freq in this text
        if (expected > 1e-12) {         //.000000...1
            double diff = counts[i] - expected; //actually freq compared to expected
            chi += (diff * diff) / expected;
        }
    }
    return chi;                     
}


//this gets the lowest chi score for all the shifts for each col
//and returns the 
int bestChiShift(const string& col) {
    double bestChi = numeric_limits<double>::infinity();
    int bestShift = 0;
    for (int s = 0; s < 26; ++s) {
        double chi = chiSquareShift(col, s);
        if (chi < bestChi) { 
            bestChi = chi; 
            bestShift = s; 
        }
    }
    return bestShift;
}


string bestKey(const string& text, int k) {
    vector<string> cols = coloumns(text, k);
    string key(k, 'A'); //key with lenght k, filled with all As to start
    for (int j = 0; j < k; ++j) {
       key[j] += bestChiShift(cols[j]); //add the current key to the placeholder A to get the letter
    }
    return key;
}





int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream input(filename); //open file and read it into string
    string raw_contents((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    //convert all to upper and remove spaces
    string contents;
    contents = prepText(raw_contents);
    cout << contents << endl;

    
    for (int i = 1; i < 21; i++){
        vector<string> cols = coloumns(contents, i);
        double sum = KIoc(contents, i);
        int chi = bestChiShift(contents);
        string key = bestKey(contents, i);
        cout << "For col: " << i << " average IoC is: "<< sum << " The best produced Keyword is "<< key << endl; 
    }

    double max = 0.0;
    int bestCol;
    for(int i = 1; i < 21; i++){
        if(KIoc(contents, i) > max){
            max = KIoc(contents, i);
            bestCol = i;
        }
    }
    string key = bestKey(contents, bestCol);
    cout <<"--------------------------------------------------------------------------------"<<endl;
    cout <<"The most likely keyword is: " << key << endl;
    

    // int idx = 0;
    // for (const string& s : cols) {
    //     cout << "Column " << idx++ << ": " << s << " the IoC of this Column is " << avgIoC(s) << endl;
    // }


    









}