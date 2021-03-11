#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Graph {
public:

    //find edges and add them to the graph
    void addEge(string& firstWord, string& secondWord, bool graph[][26]) {
        //create a graph
        int wordLength = min(firstWord.length(), secondWord.length());
        //compare the two words and find mismatching character 
        for(int i = 0; i < wordLength; i++) {
            if(firstWord[i] != secondWord[i]) {
                graph[firstWord[i]-'a'][secondWord[i]-'a'] = true;
                break;
            }
        }
    }
    //sort the graph
    bool sort(int vertex, vector<bool>& visited, bool graph[][26], string& result) {
        if(visited[vertex] == true) {
            result = "";
            return true;
        }
        //mark the vertex as visited
        visited[vertex] = true;
        //check all the adjacents to a vertex
        for(int i = 0; i < 26; i++) {
            if(graph[vertex][i] == true && i != vertex) { 
                if(sort(i, visited, graph, result) == true) {
                    return true;
                }
            }
        }

        graph[vertex][vertex] = false;
        visited[vertex] = false;
        char str = vertex + 'a';
        result = str + result;  
        return false;
    }

    //print the alphabets in the correct order 
    string print(vector<string>& words) {
        string result;
        //base case: if no words given
        if(words.size() == 0) {
            return result;
        }
        //if only one word given, return the first character
        if(words.size() == 1) {
            return words[0];
        }
        bool graph[26][26] {false};
        for(char c:words[0]) {
            graph[c-'a'][c-'a'] = true;
        }
        // add an edge from character of the first word to the second word
        for(int i = 1; i < words.size(); i++) {
            for(char c:words[i]) {
                graph[c-'a'][c-'a'] = true;
            }
            addEge(words[i-1], words[i], graph);
        }
        //find the root
        for(int i = 0; i < 26; i++) {
            bool root = graph[i][i];
            if(graph[i][i] == true) { 
                for(int j = 0; j < 26; j++) {
                    if(graph[j][i] == true && j != i) {  
                        root = false;
                        break;
                    }
                }
            }
            if(root == true) { 
                string str = "";
                vector<bool> visited(26, false);
                if(sort(i, visited, graph, str) == true) {  
                    return "";
                }
                else {
                    result += str;
                }
            }
        }
        //return empty string if the vertices have not been visited
        for(int i = 0; i < 26; i++) {
            if(graph[i][i] == true) { 
                return "";
            }
        }
        return result;
    }
};

int main() {
    Graph g;
    vector<string> test1 {"bca", "aaa", "acb"};
    cout << g.print(test1) << endl;
    vector<string> test2 {"ac","ab","zc","zb"};
    cout <<  g.print(test2) << endl;
    vector<string> test3 {"caa","aaa", "aab"};
    cout << g.print(test3) << endl;
    vector<string> test4 {"b", "y"};
    cout << g.print(test4) << endl;

    return 0;
}