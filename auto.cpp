#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, int> dmap_type;


void print_vec (std::vector<std::string> vec){
	for(auto it = vec.begin(); it!= vec.end(); it++){
		std::cout<< (*it) << '\n';
	}	
}

void deletion (std::string &s, std::vector<std::string> &vec){
	std::string temp;
	for( size_t i = 0; i <s.length(); i++){
		temp = s;
		temp.erase(i,1);
		vec.push_back(temp);
//		std::cout<<temp <<std::endl;
	}
}

void insertion (std::string &s, std::vector<std::string> &vec) {	
	std::string temp;
	for( size_t i = 0; i <s.length()+1; i++){
		for( size_t j = 'A'; j <= 'Z'; j++){
			temp = s;
			temp.insert(i,1,j);
			vec.push_back(temp);
//			std::cout<<temp <<std::endl;
		}
		
	}

}

void substitution (std::string &s, std::vector<std::string> &vec) {
	std::string temp;
	for( size_t i = 0; i <s.length(); i++){
		for( size_t j = 'A'; j <= 'Z'; j++){
		temp = s;
		
		std::string str = "";
		str += (char)j;
		temp.replace(i,1,str);
		vec.push_back(temp);
//		std::cout<<temp <<std::endl;
		}

//		std::cout<< std::endl;
	}

}

void suggest (std::string &s, std::vector<std::string> &vec){
	
	int n = s.length();
	int vec_size = n + 26 * (n+1) + 25* n;
	vec.reserve(vec_size);

	deletion(s,vec);
	insertion(s,vec);
	substitution(s,vec);	

}

int main(int argc, char* argv[]){

	std::map<std::string, int> dmap;

	std::fstream fs;
	fs.open(argv[1]);
	if(!fs) {
		std::cout <<"Check input file";
		return -1;
	}

	std::string word; int frequency = 0;
	while(fs >> word && !fs.eof()){
		fs >> frequency;	
		dmap.insert(dmap_type::value_type(word,frequency));
	}
	
	std::string query;
	while (std::cin >> query){
		auto found = dmap.find(query);
		//If query is not in dictionary, check sugestions
		if(found == dmap.end()){
			std::vector<std::string> suggestions;
			suggest(query,suggestions);
//			print_vec(suggestions);
			
			frequency = 0;
			std::string correction;
			
			//Iterate throught Vector of Suggestions
			for(auto it = suggestions.begin(); it != suggestions.end(); it++){
				found = dmap.find(*it);
				
				//If suggestions is in dictionary
				if(found != dmap.end()){
					//Then store suggestion with the highest frequency
					if((*found).second > frequency){
						correction = (*found).first;
						frequency = (*found).second;		
					}		
				}
			
			}
			// If suggestion is in dictionary then print it.
			if(frequency != 0){
				std::cout<< correction << ' ' << frequency << std::endl;
			}
			// If its not in dictionary then add it.
			else{
				dmap.insert(dmap_type::value_type(query,1));
				std::cout<< '-' << ' ' << 1 << std::endl;
			}
		

		}
		// If the word is in the dictionary, print and update.
		else{
			std::cout<< (*found).first << ' ' << (*found).second << std::endl; 
		   	(*found).second++;
		}
	}
/*	
			std::vector<std::string> vec;
			std::string s = "JON";
			deletion(s,vec);
			insertion(s,vec);
			substitution(s,vec);	
			print_vec(vec);
*/		
		
return 0;
}
