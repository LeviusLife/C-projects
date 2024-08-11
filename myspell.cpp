#include <iostream>
#include "hashtable.h"
#include <set>

#include <sstream>
#include <algorithm>

using namespace cop4530;
using namespace std;



void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}







int main(int argc, char* argv[]) {
	std::set<char> allowedChar = {'l', 'a', 'r', 'c', 'f', 'd', 's', 'w', 'x'};
	std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	
	//this vector is supposed to hold the words that could be the correct word.
	std::vector<string> candidates;
	

	int index;
	char choice;

	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************
	//this portion of the code is when the program is called with no command line arguments
	if(argc == 1) {
		

		char decision = '\0';
		int hashStart = 0;

		
		cout << "Enter preferred hash table capacity: ";
		cin >> hashStart;

		//|| !(cin >> hashStart)

		if(hashStart < 2) {

			cout << "\n** input too small" << endl;
			cout << "set to default capacity" << endl;
			cout << "11";

			//hashStart = 101;
			hashStart = default_capacity;
			cin.clear(); // Clear the error flag
    		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		else {

			cout << hashStart << endl;

		}

		HashTable<string> hashTest(hashStart);



		while(decision != 'x') {
			

				//this do while loop is responsible for validating the decision of the user. While the while loop above
				//is for ensuring that the menu continues to display after every decision is made (unless the decision is x of course)
				//
			 do {
            menu();
            std::cin >> decision;
            decision = std::tolower(decision);

            if (allowedChar.count(decision) > 0) {
                // Valid input, exit the loop
                break;
            } else {
                std::cout << '\n' << "*****Error: Invalid entry. Try again." << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        	} while (true);

			
			
			if(decision == 'l') {

				string lfilename;
				cout << "Enter dictionary filename to load from: ";
				cin.ignore();
				getline(cin, lfilename);
				


				if(hashTest.load(lfilename.c_str()) == true) {

					cout << "Dictionary loaded succcessfully." << endl;
				}


				else {

					cout << "Cannot open file " << lfilename << endl;
				
				}


			}

			if(decision == 'a') {

				std::string addWord;

				cout << "Enter word: ";
				cin >> addWord;

				if(hashTest.insert(addWord) == true) {

					cout << '\n' << "Word " << addWord << " added." << endl;

				}	else {

						cout << '\n' << "*****: Word already exists. Could not add. " << endl;

				}

				cin.ignore();


			}

			if(decision == 'r') {

				std::string removeWord;

				cout << "Enter word: ";
				cin >> removeWord;

				if(hashTest.remove(removeWord) == true) {

					cout << '\n' << "Word " << removeWord << " deleted." << endl;

				}	else {

						cout << '\n' << "*****: Word not found. Could not delete " << endl;

				}

				cin.ignore();


			}

			if(decision == 'c') {

				hashTest.clear();

			}

			if(decision == 'f') {

				std::string word;

				cout << "Enter word: ";
				cin >> word;

				if(hashTest.contains(word) == true) {

					cout << '\n' << "Word " << word << " found." << endl;

				}	else {

						cout << '\n' << "Word " << word << " not found." << endl;

				}

				cin.ignore();

			}

			if(decision == 'd') {

				
				hashTest.dump();


			}


			if(decision == 's') {

				cout << "Size of hashtable: " << hashTest.hashSize() << endl;

			}

			if(decision == 'w') {

					std::string wfilename;

					cout << "Enter dictionary file name to write to: ";
					cin.ignore();
					getline(cin, wfilename);

					if(hashTest.write_to_file(wfilename.c_str()) == true) {

						cout << "Written successfully." << endl;

					}

					else {

						cout << "Cannot open file " << wfilename << " to write to." << endl;

					}






			}

			if(decision == 'x') {

				break;

			}






		}

       

		/*
		while (!decision == 'x') {

		}
		*/
		


	}

	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************








	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************
	//this portion of the code is for the actual spell checker part. So this is when 
	else if ( argc == 4) {

		const char* dictionary = argv[1];
		const char* checkFile = argv[2];
		const char* outputFile = argv[3];
		
		HashTable<string> dictionaryHash(58);
		dictionaryHash.load(dictionary);
		std::vector<string> regurg;

		//dictionaryHash.dump();

		ifstream my_reader(checkFile);

		if (my_reader.is_open()) {
            
			std::string line;
			

			//this loop is responsible for reading each individual line of the check file
			while(std::getline(my_reader, line)) {

				std::istringstream iss(line);
				std::string individWord;
				std::string copySentence(line);
				std::string finalSentence;
				std::string punct;

				//regurg.emplace_back(line);
				//this loop is responsible for reading each individual word within the line
				while ( iss >> individWord) {
						
						
						
					
					
						//if the word is not in the hashtable
						std::string newWord;
						std::string resultT;
						
						//std::remove_copy_if(individWord.begin(), individWord.end(), std::back_inserter(newWord), std::ispunct());
						

						
						//looping through the word char by char. If the char is a letter than its added to newWord, if 
						//not then it will be ignored for now.
						newWord.clear();
										//copyWord
						for(char & ch : (individWord)) {
							if(std::isalpha(ch)) {

								newWord += (ch);
							}

								/*
									else {
        						std::cout << "Non-alphabetic character found: " << static_cast<int>(ch) << std::endl;
   							 }
								*/
							
						}

						//at this point newWord still has all of the respective capitalizations but all of the 
						//non-alphabetical characters are gone
						//tl;dr newWord = word with capitalizations and no spaces or non-alphabet characters
						std::string copyWord(newWord);




						//convert the copy word to lower case so that no words at the begin of sentences will be counted as
						//not in the dictionary. Words with random capitalizations will referred to as not in the dictionary.
											//copyWord						
						for(auto &  feck : copyWord) {

							feck = std::tolower((feck));

						}

						//copyWord is the word that is completely lowercase in order to compare it to the dictionary
						//it also has no spaces nor does it have any non-alphabetical characters


			

						
						
							
								//if the word is not found in the dictionary then 
								//we will take newWord and use that to find the same value in copySentence.
								//From there we're going to take the value of 
							
							
			
						if(dictionaryHash.contains(copyWord) != true) {
							
							size_t found = copySentence.find(newWord);

							while (found != std::string::npos) {

								for (size_t i = found; i < found + newWord.length(); ++i) {

									copySentence[i] = std::toupper(copySentence[i]);

								}


								found = copySentence.find(newWord, found + 1);

							}

							cout << copySentence << endl;
							cout << "====================================" << endl;
							
							//im going to loop through the copyWord now and check for any candidate words. Quick note: before looping 
							//store the original letter of copyWord even if its wrong then loop through. Before leaving the loop place the letter back
							//where it was.

							for(auto & ye : copyWord) {

								char originalL = ye;

								for(auto & uhuh : alphabet) {

									ye = uhuh;

									//cout << copyWord << endl;

									if(dictionaryHash.contains(copyWord) == true) {
										if (candidates.size() <= 10)
											candidates.emplace_back(copyWord);

									}



									else {

										; //do nothing

									}


								}
								ye = originalL;
							}

								/*
								
									//This part should be able to print out all of the items in candidate now. I loop tthrough the 
									//candidate vector to see if I'm doing this right or not. Quick note: once done with this words candidates
									//clear the candidates vector for the next word.
									for (int i = 0; i < candidates.size(); ++i) {

										cout << i << "): " << candidates.at(i) << endl;


									}

									cout << "n (no change): " << endl;
									cout << "====================================" << endl;
							
								
								*/
							
							//this loop will validate the user's input. If the user does not choose
							// 'n' or an int that represents an index within the vector candidates then they
							//will have to re-enter their input.
							do {


								for (int i = 0; i < candidates.size(); ++i) {

								cout << i << "): " << candidates.at(i) << endl;


								}

								cout << "n (no change): " << endl;
								cout << "====================================" << endl;





								cout << "Your choice: ";
								cin >> choice;

								if (choice == 'n')
									break; // at this point the user would like to exit the program

									//if the choice that they make is a int then that number will be put into 
									//choice. isdigit will test if choice has a valid digit within it and if it does 
									//have a valid digit then we will subtract the character 0 from it. 
									//Both the character 0 and choice have ASCII values, so if i subtract that 0 from choice
									//I'll get the ASCII value of a integer.

								if (isalpha(choice)) {

									cout << "invalid choice" << endl;
									cout << "====================================" << endl;
									std::cin.ignore();

								}



								if (std::isdigit(choice)) {

									index = choice - '0'; //

										if(index < candidates.size() && index >= 0) {

											break; // if the index that the user chose is within the range
											//of candidates index then it's valid and the program should break out of the loop.

										}

										else {

											cout << "invalid choice" << endl;
											cout << "====================================" << endl;
											std::cin.ignore();
										}


								}


							
							} while(true);



							//what happens if you choose 'n'? Does the system go back to the original sentence and uncapitalize
							//everything? or what?

							//my other issue is that I have not stored a vector of the correpsponding 
							


							

							//now what? Based off of the choice the user makes I need to insert the word
							//from candidates into the copySentence. Eventually once Im done with all of the words
							//I need to store the whole corrected sentence into a vector finalSentence.

							//if 'n' is chosen then the program will insert the word using the newWord variable. Reminder
							//newWord has the value of the word with it's original capitalizations and no non-alphabetical
							//characters attached. The only issue is that the word that I'm trying to replace is currently all
							//capitalized and find is case sensitive. So, to solve that problem I will take copyWord, again, and convert that
							//back to all 

							if (choice == 'n') {

								for(auto & king : copyWord) {

									king = std::toupper((king));


									}


								size_t found = copySentence.find(copyWord);

								while (found != std::string::npos) {

									copySentence.replace(found, copyWord.length(), newWord);
									found = copySentence.find(copyWord, found + newWord.length());

								}


							}	else {

								

								std::string correctWord(candidates.at(index));

								for (std::size_t i = 0; i < correctWord.length() && i < newWord.length(); ++i ) {

										if (std::isupper(newWord[i])) {
											correctWord[i] = std::toupper(correctWord[i]);
										}	else if (std::islower(newWord[i])) {

											correctWord[i] = std::tolower(correctWord[i]);

										}


								}


								for(auto & queen : copyWord) {

									queen = std::toupper((queen));


									}

								size_t found = copySentence.find(copyWord);

								while (found != std::string::npos) {

									copySentence.replace(found, copyWord.length(), correctWord);
									found = copySentence.find(copyWord, found + correctWord.length());

								}

								



							}










					

					
						
						
							candidates.clear();
						
						} // end of if statement for when the word is not found in the dictionary








				} // End of the loop for reading each individual word. 

				regurg.emplace_back(copySentence);



			} // End of the loop responsible for reading each individual line.
            
            
            
        } // end of if statement if(my_reader.is_open)

        

        else {
            
            std::cout << "Cannot open up file. Please try again with different method." << std::endl;
        
        }

        my_reader.close();
    

		//write lines to output file
		ofstream my_writer(outputFile);

		if (my_writer.is_open()) {
            
            for(auto gum : regurg) {
				my_writer << gum << std::endl;
			}
            
        }

        

        else {
            
            std::cout << "Cannot open up file. Please try again with different method." << std::endl;
        }

        my_writer.close();
    







	}

	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************





	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************
	//if the program isnt run with all three arguments (dictionary, check file, and the output file)
	else {

		cout << "./myspell dictionary check_file output_file " << endl;

	}


	//**********************************************************************
	//*																	   *
	//*																	   *
	//*																	   *
	//*																	   *
	//**********************************************************************



	/*
	const char* fileS;
std::string fileX;


cout << "Let's test the load function with the dictionary within linux: " << endl;
cout << "What is the name of the file? ";
std::getline(std::cin, fileX);

HashTable<string> something(58);

something.load(fileX.c_str());

cout << "Now let's just dump the dictionary: " << endl;
something.dump();


cout << "How many elements are in this file: ";
cout << something.hashSize();






	
	*/







/*

HashTable<int> something(58);

something.insert(5);
something.insert(57);
something.insert(500);
something.insert(98+64);

cout << "Is 5 in this hashtable: " << something.contains(5) << endl;
cout << "Is 57 in this hashtable: " << something.contains(57) << endl;
cout << "Is 789 in this hashtable: " << something.contains(789) << endl;
cout << "Is -54 in this hashtable: " << something.contains(- 54) << endl;


int myHero = 1;

cout << "inserting a value using a lvalue now!" << endl;
something.insert(myHero);

cout << "Is the value in myHero in this hashtable: " << something.contains(myHero) << endl;

cout << "Removing value of myHero from the hashTable!" << endl;
something.remove(myHero);
cout << "is the value of myHero in hashtable anymore: " << something.contains(myHero) << endl;


cout << "Printing out everything in something's hashtable: " << endl;
something.dump();



*/

/*

cout << '\n' << "Deleting all the elements in something's hashtable now!" << endl;
something.clear();
cout << "Is 5 in something's hashtable anymore: " << something.contains(5) << endl;
cout << "Is 57 in something's hashtable anymore: " << something.contains(57) << endl;
cout << "Is 500 in something's hashtable anymore: " << something.contains(500) << endl;
cout << "Is 98 + 64 in something's hashtable anymore: " << something.contains(98+64) << endl;
cout << "Is myHero in something's hashtable anymore: " << something.contains(myHero) << endl;


*/

//cout << "How many elements are in the hashtable: " << something.hashSize() << std::endl;



}