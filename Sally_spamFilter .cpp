//Name:Sally Manasrah ID:206644

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

std::vector<string> userEmailWords;

// This function (splitWord) take the sentence entered by the user , 
//then split the words ,and then add each one into userEmailWords vector 

 void splitWord(string str) 
{ 
    string word = ""; 
    for (auto x : str)  
    { 
        if (x == ' ') 
        { 
            userEmailWords.push_back(word);
            word = ""; 
        } 
        else { 
            word = word + x; 
        } 
    } 
    userEmailWords.push_back(word);
} 

int main() {
 double spamTotalEmail = 3;//Total number of spam emails
 double inboxTotalEmail = 5;//Total number of inbox emails
 double totalEmails = spamTotalEmail + inboxTotalEmail;//Spam and Inbox emails
 double dictVocab = 12;//Dictionary vacabulary
 double k=1;//To be used in laplace smoothing
 double noOfClasses = 2;//Cardinallity to be used in laplace smoothing
 string str;// The sentence enter by the user

  
 std::map<std::string, double> mapOf_SpamWordsProb;//Store each spam word with the corresponding probability in the map
 std::map<std::string, double> mapOf_InboxWordsProb;//Store each inbox word with the corresponding probability in the map 
 
// Words given spam probabilities 
 
 mapOf_SpamWordsProb.insert({"offer",(1+k)/(9+(dictVocab*k))});
 mapOf_SpamWordsProb.insert({"is",(1+k)/(9+(dictVocab*k))});
 mapOf_SpamWordsProb.insert({"secret",(3+k)/(9+(dictVocab*k))});
 mapOf_SpamWordsProb.insert({"click",(1+k)/(9+(dictVocab*k))});
 mapOf_SpamWordsProb.insert({"link",(2+k)/(9+(dictVocab*k))});
 mapOf_SpamWordsProb.insert({"sport",(1+k)/(9+(dictVocab*k))});
 
// Words given inbox probabilities
 
 mapOf_InboxWordsProb.insert({"play",(2+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"sport",(5+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"today",(2+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"went",(1+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"secret",(1+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"event",(1+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"is",(1+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"cost",(1+k)/(15+(dictVocab*k))});
 mapOf_InboxWordsProb.insert({"money",(1+k)/(15+(dictVocab*k))});
 
 // Spam probability 
 double spamProb=(spamTotalEmail+k)/(totalEmails+(k*noOfClasses));
  
 // Inbox probability
 double inboxProb=(inboxTotalEmail+k)/(totalEmails+(k*noOfClasses));
 
 
 cout<<"Enter Your Email content,please ! "<<endl;
 getline(cin,str);
 splitWord(str);
 double total1=1,total2=1;
 
 // This loop calaculate the multiplication of spam words probability 
// and return the multiplication result of these probabilities 

 for(auto word : userEmailWords)
    {
        double temp,rounded;
        auto position = mapOf_SpamWordsProb.find(word);
        if (position != mapOf_SpamWordsProb.end())
        { 
          temp = position->second;
          rounded = (int)(temp * 10000.0)/10000.0;
        }
        else
        {rounded=(0+k)/(9+(dictVocab*k));}// if the word is not exist in spam email 
        
        total1=total1*rounded;
    }
    
    double numerator=total1*spamProb;//The numerator calculated by multiply spam words probability with the spam probability 
    
 // This loop calaculate the multiplication of inbox words probability 
// and return the multiplication result of these probabilities 

 for(auto word : userEmailWords)
    {
        double temp,rounded;
        auto position = mapOf_InboxWordsProb.find(word);
        if (position != mapOf_InboxWordsProb.end())
        { 
          temp = position->second;
          rounded = (int)(temp * 10000.0)/10000.0;
        }
        else
        {rounded=(0+k)/(15+(dictVocab*k));}// if the word is not exist in inbox email 
        
        total2=total2*rounded;
    }
    
    double denumerator=numerator+(total2*inboxProb);//The denumerator calculated by add the multiplication of spam word probabilites and inbox probability
    
    // The spam given sentence probability calculated by devide the numerator over denumerator
    double probability = numerator/denumerator;
    
    cout<<endl<<"The probability is "<<setprecision(4)<<probability<<endl;
    if (probability >0.5)
    {cout << "So, it is a spam email"<<endl<<"Bye Bye !";}
    else 
    {cout<<"So, it is not a spam email"<<endl<<"Bye Bye !";}
    
return 0; 
}
