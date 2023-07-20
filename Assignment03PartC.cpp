

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

// Global
enum partOfSpeech { NOUN, VERB, ADJECTIVE, CONJUNCTION, ADVERB, INTERJECTION, PREPOSITION, PRONOUN, NOTVALID, DEFAULT };
static const char* partOfSpeechEnumStrings[] = { "NOUN", "VERB", "ADJECTIVE","CONJUNCTION","ADVERB","INTERJECTION","PREPOSITION","PRONOUN", "NOTVALID", "DEFAULT" };
static const std::string QUIT_SEARCH = "!Q";
static const std::string SEARCH_INFO = "\tPARAMETER HOW - TO, please enter :\n\t1. A search key - then 2. An optional part of speech - then\n\t3. An optional distinct - then 4. An optional reverse";

static const std::string CLEAR = "CLEAR";

struct wordDescription {
    string wordNamePrintVersion;
    vector<vector<string>> totalDefinitionos;
    vector<string> nouns;
    vector<string> verbs;
    vector<string> adjectives;
    vector<string> conjunction;
    vector<string> adverb;
    vector<string> interjection;
    vector<string> preposition;
    vector<string> pronoun;
};

// Function Declarations.

bool compareFunction(string , string );
void printInvalidInput();
void printSourceFileNotFoundMessage(string);
void printWordNotFound();
void printInvalidPartOfSpeech(string);
void printInvalidThirdParameter(string);
void printInvalidFourthParameter(string);
void clear();
void clearXCodeConsole();
void exitMessage();
bool isEqual(const std::string&, const std::string&);
bool fillDictionary(std::map<std::string, wordDescription>*, std::string&);
bool checkDictionary(const std::map<std::string, wordDescription>*, const std::map<std::string, wordDescription>::iterator);
bool validPartOfSpeech(std::string);
const char* getStringForEnum(partOfSpeech);
partOfSpeech getPartOfSpeechString(std::string);
void executeDictionary(map<string,wordDescription>);
void printReverse(map<string, wordDescription>::iterator);
void printPartOfSpeech(map<string, wordDescription>::iterator, string);
void printDistict(map<string, wordDescription>::iterator);
vector<string> getPartOfSpeechVec(const map<string, wordDescription>::iterator, string);
void printAllDefinitions(const map<string, wordDescription>::iterator);
void printPartOfSpeechDistinct(const map<string, wordDescription>::iterator, string);
void printPartOfSpeechReverse(const map<string, wordDescription>::iterator, string);
void printPartOfSpeechReverseDistinct(const map<string, wordDescription>::iterator, string);
void printDistinctReverse(const map<string, wordDescription>::iterator);
int getNumOfKeyWords(map<string, wordDescription>);
int getNumOfDefinitions(map<string, wordDescription>);


int main() {

    std::map<std::string, wordDescription>* dictionary = new std::map<std::string, wordDescription>();
    std::map<std::string, wordDescription>::iterator wordItr;
    std::string sourceFile("./Data.CS.SFSU.txt");
    std::stringstream tokens;
    std::string line, inputWord, inputPartOfSpeech, inputExcess;
    bool reverse = false;
    bool distinct = false;
    bool keepSearching = true;
    int counter = 0;


    
    
    
    fstream ioFile;
    cout << "! Opening data file...";
   do{
       
       cin >> sourceFile;
       fstream ioFile(sourceFile);
       //clear the input
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       if (!ioFile.is_open()) {
           printSourceFileNotFoundMessage(sourceFile);
       }
       else {
           break;
       }
       
   } while (!ioFile.is_open());

    if (fillDictionary(dictionary, sourceFile)) {
        int keywords = getNumOfKeyWords(*dictionary);
        int definitions = getNumOfDefinitions(*dictionary);
        cout << "\n====== DICTIONARY 340 C++ =====" << endl;
        cout << "------ Keywords: " << keywords << endl;
        cout << "------ Definitions: "<< definitions << endl;


        while (keepSearching) {
            inputPartOfSpeech.clear();
            reverse = false;
            distinct = false;// Begin Searching
            string input2;
            string input3;
            string input4;
            counter += 1;
            cout << "Search [" << counter << "]:";                // Ask for input

            getline(cin, line);                // Parse input
            tokens << line;
            tokens >> inputWord;
            tokens >> input2;
            tokens >> input3;
            tokens >> input4;
            tokens >> inputExcess;
            //input2
            if (isEqual(input2, "distinct")) {
                distinct = true;
            }
            else if (isEqual(input2, "reverse")) {
                reverse = true;
            }
            else {
                inputPartOfSpeech = input2;
            }
            //input3
            if (isEqual(input3, "distinct")) {
                distinct = true;
            }
            else if (isEqual(input3, "reverse")) {
                reverse = true;
            }
            //input4
            if (isEqual(input4, "reverse")) {
                reverse = true;
            }


            cout << "\n\t|" << endl;
            //make sure I have an inputword
            if (isEqual(inputWord, QUIT_SEARCH)) {        // Quit program
                keepSearching = false;
                continue;
            }

            else if (isEqual(inputWord, "!HELP")) {
                cout << SEARCH_INFO << endl;

            }
            else if (inputWord.empty() || !inputExcess.empty()) {           // No entries, or way to many entries.
                cout << SEARCH_INFO << endl;

            }
            else {
                //error messages for 3rd parameter
                if (!input3.empty()){
                    if (!isEqual(input3, "distinct") && !isEqual(input3, "reverse")) {
                        printInvalidThirdParameter(input3);
                   }
                }
                //error messages for  4th parameter
                if (!input4.empty() && !isEqual(input4, "reverse")) {

                        printInvalidFourthParameter(input4);
                    
                }

                //search the inputword in my dictionary
                transform(inputWord.begin(), inputWord.end(), inputWord.begin(), toupper);
                wordItr = dictionary->find(inputWord);

                if (checkDictionary(dictionary, wordItr)) {


                    //only word
                    if (inputPartOfSpeech.empty() && !reverse && !distinct) {                    // Only one entry, check dictionary
                        printAllDefinitions(wordItr);
                    }
                    //word + partofSpeech 
                    else if (!inputPartOfSpeech.empty() && !reverse && !distinct) {
                        printPartOfSpeech(wordItr, inputPartOfSpeech);
                    }
                    //word + partofSpeech + reverse
                    else if (!inputPartOfSpeech.empty() && reverse && !distinct) {
                        printPartOfSpeechReverse(wordItr, inputPartOfSpeech);
                    }
                    //word + partOfSpeech + distinct
                    else if (!inputPartOfSpeech.empty() && !reverse && distinct) {
                        printPartOfSpeechDistinct(wordItr, inputPartOfSpeech);
                    }
                    //word + distinct + reverse
                    else if (inputPartOfSpeech.empty() && reverse && distinct) {
                        printDistinctReverse(wordItr);

                    }
                    //word + reverse
                    else if (inputPartOfSpeech.empty() && reverse && !distinct) {
                        printReverse(wordItr);

                    }
                    //word + distinct
                    else if (inputPartOfSpeech.empty() && !reverse && distinct) {
                        printDistict(wordItr);
                    }
                    //word+ partOfSpeech + distinct + reverse
                    else if (!inputPartOfSpeech.empty() && reverse && distinct) {
                        printPartOfSpeechReverseDistinct(wordItr, inputPartOfSpeech);
                    }
                }

                else {
                    printWordNotFound();
                    
                }
            }
         



                std::cout << "\t|" << std::endl;
               
            
            // Reset all streams to read next line.
            tokens.ignore(INT8_MAX, '\n');
            tokens.clear();
            std::cin.clear();
            inputWord.clear();
            inputPartOfSpeech.clear();
            inputExcess.clear();
            wordItr = dictionary->end();                // Set wordItr to "null"
        }
    }
    else {
        printSourceFileNotFoundMessage(sourceFile);
    }
        

    wordItr = dictionary->end();
    delete dictionary;
    dictionary = nullptr;
    exitMessage();
    return 0;
}



/**
 * Function used to confirm that the word is inside the dictionary.
 * Since one of the parameters in an iterator pointer obtained from
 * calling the 'find' method, this function does not conduct another
 * search. So, if the iterator pointer is not pointing to 'end()',
 * then the word is in the dictionary, and the function returns true,
 * and false otherwise.
 * @param dictionary is a pointer to a map.
 * @param wordPtr is an iterator pointer given from the 'find' function.
 * @rethrn true if the word is in the dictionary, false otherwise.
 */
bool checkDictionary(const std::map<std::string, wordDescription>* dictionary, const std::map<std::string, wordDescription>::iterator wordPtr) {
    if (wordPtr != dictionary->end())
        return true;
    else
        return false;
}

/**
 * Function used to extract data from text file and populate the dictionary map.
 * @param dictionary is a pointer to a map.
 * @param source is the path to the source file.
 * @return true operation was succesful, false otherwise.
 */
bool fillDictionary(std::map<std::string, wordDescription>* dictionary, std::string& source) {
    cout << "! Loading data..." << endl;
   
    std::fstream ioFile(source);
    std::stringstream ssLine, ssPOfSpeech,ssDefinition;
    std::string line, sentence, wordName, pOfSpeech, description, definition;
    long position = 0;
    if (ioFile.is_open()) {
        while (getline(ioFile, line)) {
            ssLine << line;
            getline(ssLine, wordName, '|');
            wordDescription def;

            while (getline(ssLine, sentence, '|')) {
                ssPOfSpeech << sentence;
               
                getline(ssPOfSpeech, pOfSpeech, ' ');
                getline(ssPOfSpeech, description,'|');
                
                position = description.find(">");
                definition = description.substr(position + 2);
                definition[1] = toupper(definition[1]);

                //Setup wordnameprintversion
                if (wordName[0] != 'c') {
                    std::transform(wordName.begin(), wordName.end(), wordName.begin(), tolower);
                    wordName[0] = toupper(wordName[0]);
                    def.wordNamePrintVersion = wordName;
                }
                else {
                    std::transform(wordName.begin(), wordName.end(), wordName.begin(), toupper);
                }
                def.wordNamePrintVersion = wordName;
                std::transform(wordName.begin(), wordName.end(), wordName.begin(), toupper);

                

                // fill def structure vectors.
                if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::NOUN))) {
                   
                    def.nouns.push_back("\t"+def.wordNamePrintVersion + " [noun] : " + definition);
                    
                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::VERB))) {
                    def.verbs.push_back("\t" + def.wordNamePrintVersion + " [verb] : " + definition);
                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADJECTIVE))) {
                    def.adjectives.push_back("\t" + def.wordNamePrintVersion + " [adjective] : " + definition);
                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADVERB))) {
                    def.adverb.push_back("\t" + def.wordNamePrintVersion + " [adverb] : " + definition);
                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::INTERJECTION))) {
                    def.interjection.push_back("\t" + def.wordNamePrintVersion + " [interjection] : " + definition);

                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::PREPOSITION))) {
                    def.preposition.push_back("\t" + def.wordNamePrintVersion + " [preposition] : " + definition);
                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::PRONOUN))) {
                    def.pronoun.push_back("\t" + def.wordNamePrintVersion + " [pronoun] : " + definition);

                }
                else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::CONJUNCTION))) {
                    def.conjunction.push_back("\t" + def.wordNamePrintVersion + " [conjuction] : " + definition);

                }
                ssPOfSpeech.clear();
                
            }
            
            
            
            //push to matrix & sort vectors alphabetically

            if (!def.adjectives.empty()) {
                sort(def.adjectives.begin(), def.adjectives.end(), compareFunction);
                def.totalDefinitionos.push_back(def.adjectives);
            }
            if (!def.adverb.empty()) {
                sort(def.adverb.begin(), def.adverb.end(), compareFunction);
                def.totalDefinitionos.push_back(def.adverb);
            }
            if (!def.conjunction.empty()) {
                sort(def.conjunction.begin(), def.conjunction.end(), compareFunction);
                def.totalDefinitionos.push_back(def.conjunction);
            }
            if (!def.interjection.empty()) {
                sort(def.interjection.begin(), def.interjection.end(), compareFunction);
                def.totalDefinitionos.push_back(def.interjection);
            }
            if (!def.nouns.empty()) {
                sort(def.nouns.begin(), def.nouns.end(), compareFunction);
                def.totalDefinitionos.push_back(def.nouns);
            }
            if (!def.preposition.empty()) {
                sort(def.preposition.begin(), def.preposition.end(), compareFunction);
                def.totalDefinitionos.push_back(def.preposition);
            }
            if (!def.pronoun.empty()) {
                sort(def.pronoun.begin(), def.pronoun.end(), compareFunction);
                def.totalDefinitionos.push_back(def.pronoun);

            }
            if (!def.verbs.empty()) {
                sort(def.verbs.begin(), def.verbs.end(), compareFunction);
                def.totalDefinitionos.push_back(def.verbs);
            }
            
            
            
           
            
            
            
     
            
            dictionary->emplace(wordName, def);
            ssLine.ignore();
            ssPOfSpeech.ignore();
            ssPOfSpeech.clear();
            ssLine.clear();
            
            
            

        }
        cout << "! Loading completed..." << endl;
        cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
        ioFile.close();
        return true;
    }
    else
        return false;
}

/**
 * Validate part of speech
 * @param inputPartOfSpeech is a string representing part of speech input.
 * @return true if part of speech is true, false otherwise.
 */
bool validPartOfSpeech(const std::string inputPartOfSpeech) {
    for (int i = 0; i < 10; i++) {
        if (isEqual(inputPartOfSpeech, partOfSpeechEnumStrings[i])) {
            return true;
        }
    }
    return false;
}

/**
 * Get part of speech value from partOfSpeech enum
 * @param pOfSpeech is string representing part of speech input.
 * @return partOfSpeech value.
 */
partOfSpeech getPartOfSpeechString(const std::string pOfSpeech) {
    if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::NOUN)))
        return partOfSpeech::NOUN;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::VERB)))
        return partOfSpeech::VERB;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADJECTIVE)))
        return partOfSpeech::ADJECTIVE;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::CONJUNCTION)))
        return partOfSpeech::CONJUNCTION;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADVERB)))
        return partOfSpeech::ADVERB;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::INTERJECTION)))
        return partOfSpeech::INTERJECTION;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::PREPOSITION)))
        return partOfSpeech::PREPOSITION;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::PRONOUN)))
        return partOfSpeech::PRONOUN;
    else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::DEFAULT)))
        return partOfSpeech::DEFAULT;
    else
        return partOfSpeech::NOTVALID;
}

/**
 * Function used to get string value of partOfSpeech.
 * @param pOfSpeech to be converted to string
 * @return char* representing the string value of a particluar part of
 *         speech value.
 */
const char* getStringForEnum(partOfSpeech pOfSpeech) {
    switch (pOfSpeech)
    {
    case partOfSpeech::NOUN:        return partOfSpeechEnumStrings[0];
    case partOfSpeech::VERB:        return partOfSpeechEnumStrings[1];
    case partOfSpeech::ADJECTIVE:   return partOfSpeechEnumStrings[2];
    case partOfSpeech::CONJUNCTION:   return partOfSpeechEnumStrings[3];
    case partOfSpeech::ADVERB:   return partOfSpeechEnumStrings[4];
    case partOfSpeech::INTERJECTION:   return partOfSpeechEnumStrings[5];
    case partOfSpeech::PREPOSITION:   return partOfSpeechEnumStrings[6];
    case partOfSpeech::PRONOUN:   return partOfSpeechEnumStrings[7];
    case partOfSpeech::NOTVALID:    return partOfSpeechEnumStrings[8];
    case partOfSpeech::DEFAULT:     return partOfSpeechEnumStrings[9];
    };
}

/**
 * Function used to see if two strings are equal.
 * @param s1 string to be compared.
 * @param s2 string to be compared.
 * @return true if strings are equal, false otherwise.
 */
bool isEqual(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size())
        return false;
    for (int i = 0; i < s1.size(); i++) {
        if (toupper(s1[i]) != toupper(s2[i]))
            return false;
    }
    return true;
}

//get the vector of the speech

vector<string> getPartOfSpeechVec(const map<string, wordDescription>::iterator dict, string partOfSpeechToSearch) {

    partOfSpeech pOfSpeech = getPartOfSpeechString(partOfSpeechToSearch);

    vector<string> vec;

    switch (pOfSpeech) {
    case NOUN:
        vec = dict->second.nouns;
        break;
    case VERB:
        vec = dict->second.verbs;
        break;
    case ADJECTIVE:
        vec = dict->second.adjectives;
        break;
    case ADVERB:
        vec = dict->second.adverb;
        break;
    case CONJUNCTION:
        vec = dict->second.conjunction;
        break;
    case INTERJECTION:
        vec = dict->second.interjection;
        break;
    case PREPOSITION:
        vec = dict->second.preposition;
        break;
    case PRONOUN:
        vec = dict->second.pronoun;
        break;

    }
    return vec;



}

//print word
void printAllDefinitions(const map<string, wordDescription>::iterator dict) {
    vector<vector<string>> matrix = dict->second.totalDefinitionos;
    
    for (int i = 0; i < matrix.size(); i++) {
        vector<string> vec = matrix[i];
        for (int j = 0; j < vec.size(); j++) {
            cout << vec[j] << endl;
        }

    }

}

//Print word + reverse
void printReverse(const map<string, wordDescription>::iterator dict) {
    vector<vector<string>> matrix = dict->second.totalDefinitionos;
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); i++) {
        vector<string> vec = matrix[i];
        reverse(vec.begin() , vec.end());
        for (int j = 0; j < vec.size(); j++) {
            cout << vec[j] << endl;
        }

    }
}
//Print word + distinct
void printDistict(const map<string, wordDescription>::iterator dict) {
    vector<vector<string>> matrix = dict->second.totalDefinitionos;
    
   
    for (int i = 0; i < matrix.size(); i++) {
        vector<string> vec = matrix[i];
        vector<string>::iterator ip;
        ip = unique(vec.begin(), vec.begin() + vec.size());
        vec.resize(distance(vec.begin(), ip));
        for (int j = 0; j < vec.size(); j++) {
            
            ip = unique(vec.begin(), vec.begin() + vec.size());
            vec.resize(distance(vec.begin(), ip));
            cout << vec[j] << endl;
        }

    }
}
//Print word distinct + reverse
void printDistinctReverse(const map<string, wordDescription>::iterator dict) {
    vector<vector<string>> matrix = dict->second.totalDefinitionos;
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); i++) {
        vector<string> vec = matrix[i];
        vector<string>::iterator ip;
        ip = unique(vec.begin(), vec.begin() + vec.size());
        vec.resize(distance(vec.begin(), ip));
        reverse(vec.begin(), vec.end());
        for (int j = 0; j < vec.size(); j++) {
            cout << vec[j] << endl;
        }

    }
}

//print word + partofSpeech 
void printPartOfSpeech(const map<string, wordDescription>::iterator dict, string partOfSpeechToSearch) {
    if (validPartOfSpeech(partOfSpeechToSearch)) {
        vector<string> vec = getPartOfSpeechVec(dict,partOfSpeechToSearch);
        if (vec.empty()) {
            printWordNotFound();
        }
        else {
            for (int j = 0; j < vec.size(); j++) {
                cout << vec[j] << endl;
            }
        }
        
    }
    else {
        printInvalidPartOfSpeech(partOfSpeechToSearch);
        printAllDefinitions(dict);

    }
}
//word+ partOfSpeech + distinct
void printPartOfSpeechDistinct(const map<string, wordDescription>::iterator dict, string partOfSpeechToSearch) {
    if (validPartOfSpeech(partOfSpeechToSearch)) {
        vector<string> vec = getPartOfSpeechVec(dict, partOfSpeechToSearch);
        vector<string>::iterator ip;
        ip = unique(vec.begin(), vec.begin() + vec.size());
        vec.resize(distance(vec.begin(), ip));
            for (int j = 0; j < vec.size(); j++) {
                cout << vec[j] << endl;
            }

        

    }
    else {
        printInvalidPartOfSpeech(partOfSpeechToSearch);
        printDistict(dict);

    }
}
//word+ partOfSpeech +  reverse
void printPartOfSpeechReverse(const map<string, wordDescription>::iterator dict, string partOfSpeechToSearch) {
    if (validPartOfSpeech(partOfSpeechToSearch)) {
        vector<string> vec = getPartOfSpeechVec(dict, partOfSpeechToSearch);

        reverse(vec.begin(), vec.end());
        for (int j = 0; j < vec.size(); j++) {
            cout << vec[j] << endl;
        }



    }
    else {
        printInvalidPartOfSpeech(partOfSpeechToSearch);
        printReverse(dict);

    }
}
//word+ partOfSpeech + distinct + reverse

void printPartOfSpeechReverseDistinct(const map<string, wordDescription>::iterator dict, string partOfSpeechToSearch) {
    if (validPartOfSpeech(partOfSpeechToSearch)) {
        vector<string> vec = getPartOfSpeechVec(dict, partOfSpeechToSearch);
        vector<string>::iterator ip;
        ip = unique(vec.begin(), vec.begin() + vec.size());
        vec.resize(distance(vec.begin(), ip));
        reverse(vec.begin(), vec.end());
        for (int j = 0; j < vec.size(); j++) {
            cout << vec[j] << endl;
        }



    }
    else {
        printInvalidPartOfSpeech(partOfSpeechToSearch);
        printDistinctReverse(dict);

    }
}


/**
 * Function used to print the 'not found' message.
 */
void printWordNotFound() {
    cout << "\t<NOT FOUND> To be considered for the next release. Thank you." << endl;
    cout << "\t|" << endl;
    cout << "\t|" << endl;
    cout << "\tPARAMETER HOW - TO, please enter : \n\t1.A search key - then 2. An optional part of speech - then\n\t3.An optional distinct - then 4. An optional reverse" <<endl;
}

/**
 * Function used to print 'invalid part of speech' message.
 */
void printInvalidPartOfSpeech(string partOfSpeech) {
    cout << "\t<The entered 2nd parameter '" << partOfSpeech << "' is NOT a part of speech.>" << endl;
    cout << "\t<The entered 2nd parameter '"<< partOfSpeech <<" is NOT 'distinct'.>" << endl;
    cout << "\t<The entered 2nd parameter '"<< partOfSpeech <<"' is NOT 'reverse'.>" << endl;
    cout << "\t<The entered 2nd parameter '"<< partOfSpeech <<"' was disregarded.>" << endl;
    cout << "\t<The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
    cout << "\t|"<< endl;
    cout << "\t|" << endl;
}
void printInvalidThirdParameter(string partOfSpeech) {
    
    cout << "\t<The entered 3rd parameter '" << partOfSpeech << "' is NOT 'distinct'.>" << endl;
    cout << "\t<The entered 3rd parameter '" << partOfSpeech << "' is NOT 'reverse'.>" << endl;
    cout << "\t<The entered 3rd parameter '" << partOfSpeech << "' was disregarded.>" << endl;
    cout << "\t<The 3nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
    cout << "\t|" << endl;
    cout << "\t|" << endl;
}
void printInvalidFourthParameter(string partOfSpeech) {
    
    cout << "\t<The entered 4th parameter '" << partOfSpeech << "' is NOT 'reverse'.>" << endl;
    cout << "\t<The entered 4th parameter '" << partOfSpeech << "' was disregarded.>" << endl;
    cout << "\t<The 4th parameter should be 'reverse'.>" << endl;
    cout << "\t|" << endl;
    cout << "\t|" << endl;
}
/**
 * Function used to print 'invalid input' message.
 */
void printInvalidInput() {
    std::cout << "\t<Please enter a search key (and a part of speech)>" << std::endl;
}

/**
 * Function used to 'clear' the screen.
 */
void clear() {
    std::cout << "\033\143" << std::endl;
   
}

/**
 * Function used to print the 'thank you' message.
 */
void exitMessage() {
    std::cout << "\033\143" << std::endl;
    std::cout << "---------- THANK YOU ----------" << "\n" << std::endl;
}

/**
 * Function used to print the 'source file not found' message.
 */
void printSourceFileNotFoundMessage(string source) {
    std::cout << "<!>ERROR<!> ===> File could not be opened." << std::endl;
    std::cout << "<!>ERROR<!> ===> Provided file path: "<< source << std::endl;
    std::cout << "<!>Enter the CORRECT data file path:  ";
}

/**
 * Function used to clear the screen in XCode.
 */
void clearXCodeConsole() {
    std::system("clear");
}

/**
 * Function used to print the 'exit' message.
 */
void exit(int number) {
    std::system("pause");
    _Exit(EXIT_SUCCESS);
}

int getNumOfKeyWords(map<string, wordDescription> dict) {
    int count = 0;
    for (map<string, wordDescription>::const_iterator itr{dict.begin()}; itr != dict.end(); ++itr) {
        count++;
    }
    return count;
}

int getNumOfDefinitions(map<string, wordDescription> dict) {
    int count =1 ;
    for (map<string, wordDescription>::const_iterator itr{dict.begin()}; itr != dict.end(); ++itr) {
        vector<vector<string>> matrix = itr->second.totalDefinitionos;

        for (int i = 0; i < matrix.size(); i++) {
            vector<string> vec = matrix[i];
            for (int j = 0; j < vec.size(); j++) {
                count++;
            }

        }
    }
    return count;
}

bool compareFunction(std::string a, std::string b) { return a < b; }