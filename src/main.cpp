#include <unordered_map>
#include <vector>
#include <filesystem>
#include <iostream>
#include <string>
#include <EngineName/OtherFolder/OtherFolderFile.h>
#include <EngineName/Test/TestFile.h>


struct Node{
    std::vector<Node*> next;
    std::vector<Node*> previous;
    std::string current = "NULL";

    Node(std::string next){
        current = next;

    }

};

typedef std::string file;
typedef std::string dependency;
std::vector<std::string> filePaths;
std::unordered_map<file, dependency> dependencies;
std::string recurse(std::string startingPath, std::vector<std::string>& paths){
    std::cout << "Checking on path '" << startingPath << "'\n";
    if(startingPath.find('.') == std::string::npos){
        std::cout << "Path is a folder...\n";
        for (const auto & entry : std::filesystem::directory_iterator(startingPath)){
            recurse(entry.path().u8string(), paths);
        }   
    }else{
        std::string file = startingPath.substr(startingPath.find_last_of('.'));
        if(file == "cpp" || file == "h"){
            paths.push_back(startingPath);
            std::cout << "Added: '" << startingPath << "'\n";
            return startingPath;
        }
    }

    


}

std::string recurse2(Node* root){
    if(root == nullptr) return "";
    std::cout << "Checking on path '" << root->current << "'\n";
    if(root->current.find('.') == std::string::npos){
        std::cout << "Path is a folder...\n";
        for (const auto & entry : std::filesystem::directory_iterator(root->current)){
            Node* nextNode = new Node(entry.path().u8string());
            root->next.push_back(nextNode);
            recurse2(nextNode);
        }   
    }else{
        std::string file = root->current.substr(root->current.find_last_of('.'));
        if(file == "cpp" || file == "h"){
            std::cout << "Added: '" << root->current << "'\n";
        }
    }

    return root->current;
    


}

void printRoot(Node* root, int deep = 0){
    if(root){
        std::string tabs;
        for(int i = 0; i < deep; i++){
            tabs += "\t";
        }
        std::cout << tabs << root->current << std::endl;
        for(Node* next : root->next)
            printRoot(next, deep+1);
    }

}

int main(){

    std::string startingPath = "src/";
    recurse(startingPath, filePaths);


    Node* root = new Node(startingPath);
    recurse2(root);
    printRoot(root);
    return 0;
}