#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <filesystem>

using namespace std;

//This function takes the PlainText and key and ciphers the plaintext
void encrypt (const string& plainText, const string& key){
    //cout << "function encrypt called";
    ifstream input("plainText.txt");
    string contents((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    string noSpacePT;
    for (char c : contents){
        if ( c != ' ')
            noSpacePT += c;
    }



    ofstream outputFile("cipherText.txt");
    int counter = 0; //counter for the key so it can loop around
    //cout << "the text to be proccesed is " << noSpacePT;
    //cout << noSpacePT.length();
    for(int i = 0; i < noSpacePT.length(); i++){
        //cout << "encryption loop enetered...\n";
        int plain = toupper(noSpacePT[i]) - 'A';
        int keyI   = toupper(key[counter])   - 'A';
        counter = (counter + 1) % key.length();

        int newChar = (plain + keyI) % 26;
        char cipChar = newChar + 'A';
        //cout << cipChar << "\n";
        outputFile << cipChar;

    }

}



//This function takes the ciphertext and key and deCiphers it
void decrypt (const string& cipherText, const string& key){
    //cout << "function dencrypt called";
    ifstream input("cipherText.txt");
    string contents((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());


    ofstream outputFile("plainText.txt");
    int counter = 0; //counter for the key so it can loop around
    //cout << "the text to be proccesed is " << contents;
    //cout << contents.length();
    for(int i = 0; i < contents.length(); i++){
        //cout << "encryption loop enetered...\n";
        int cipher = toupper(contents[i]) - 'A';
        int keyI   = toupper(key[counter])   - 'A';
        counter = (counter + 1) % key.length();

        int newChar = (cipher - keyI + 26) % 26;
        char plainChar = newChar + 'A';
        //cout << plainChar << "\n";
        outputFile << plainChar;

    }

}




int main () {
    int choice;
    cout << "Welcome to Vigenere \n" "___________________\n" 
    "0 - To use added files\n" "1 - To input information\n";
    cin >> choice;

    //User wants to use added files
    if (choice == 0){
        char a;
        cout << "Using added files \n";
        cout << "Would you like to Encrypt (e) or Decrypt (d)? ";
        cin >> a;
        if (a == 'e'){
            string plainText;
            string key;
            cout << "Enter the name of the file you would like to Encrypt: ";
            cin >> plainText;
            ifstream inputFile(plainText);
            inputFile.close();
            cout << "Enter the key to Encrypt: ";
            cin >> key;
            encrypt(plainText ,key);   

            //Encrypt
        } else if(a == 'd'){
            string cipherText;
            string key;
            cout << "Enter the name of the file you would like to Decrypt: ";
            cin >> cipherText;
            ifstream inputFile(cipherText);
            ofstream outputFile("cipherKnownKeyTest.txt");
            cout << "Enter the key to Encrypt: ";
            cin >> key;
            //Decrypt
        } else {
            cout << "Select either Encrypt or Decrypt!\n";
        }

    //User wants input information
    } else if(choice == 1){
        char a; 
        cout << "Would you like to Encrypt (e) or Decrypt (d)? ";
        cin >> a;
        if (a == 'e'){
            string plainText;
            string key;
            char x;
            cout << "Enter the plaintext: ";
            getline(cin >> ws, plainText); //removes whitespace that causing getline to skip
            ofstream inputFile("plainText.txt");
            inputFile.write(plainText.c_str(), plainText.length());
            cout << "Enter the key: ";
            cin >> key;
            inputFile.close();
            encrypt( "plainText.txt" ,key);
            //Encrypt
        } else if(a == 'd'){
            string cipherText;
            string key;
            char x;
            cout << "Enter the cipherText: ";
            getline(cin >> ws, cipherText); //removes whitespace that causing getline to skip
            ofstream inputFile("cipherText.txt");
            inputFile.write(cipherText.c_str(), cipherText.length());
            cout << "Enter the key: ";
            cin >> key;
            inputFile.close();
            decrypt( "cipherText.txt" ,key);
            //Decrypt
        } else {
            cout << "Select either Encrypt or Decrypt!\n";
        }

    } else {
        return 0;
    }


}