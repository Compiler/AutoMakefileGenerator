#include <unordered_map>
#include <vector>
#include <filesystem>
#include <iostream>
#include <string>
#include <EngineName/OtherFolder/OtherFolderFile.h>
#include <EngineName/Test/TestFile.h>
#include <iostream>
#include <fstream>


struct Node{
    std::vector<Node*> next;
    std::vector<Node*> previous;
    std::string current = "NULL";

    Node(std::string next){
        current = next;

    }

};

typedef std::string file;
typedef std::string folder;
typedef std::string dependency;
std::vector<std::string> filePaths;
std::vector<folder> foldersWithFiles;
std::unordered_map<folder, std::vector<file>> dependencies;


std::string recurse(Node* root){
    if(root == nullptr) return "";
    std::cout << "Checking on path '" << root->current << "'\n";
    if(root->current.find('.') == std::string::npos){
        std::cout << "Path is a folder...\n";
        for (const auto & entry : std::filesystem::directory_iterator(root->current)){
            Node* nextNode = new Node(entry.path().u8string());
            root->next.push_back(nextNode);
            recurse(nextNode);
        }   
    }else{
        std::string file = root->current.substr(root->current.find_last_of('.'));
        if(file == ".cpp"){
            std::string curFolder = root->current.substr(0, root->current.find_last_of('\\')) + "\\";
            file = root->current.substr(root->current.find_last_of('\\') + 1);
            foldersWithFiles.push_back(curFolder);
            dependencies[curFolder].push_back(file.substr(0,'.'));
            std::cout << "Added: '" << file << "' from folder: '"<< curFolder << "'\n";
        }
    }

    return root->current;
    


}

void printRoot(Node* root, int deep = 0){
    //static std::vector<
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


void createMakefile(){

    std::ofstream myfile ("example.txt");
    if (myfile.is_open()){
        for(auto curFolder : foldersWithFiles){
            std::string make_folderName;
            int firstBackSlash = curFolder.find_first_of('\\');
            int lastBackSlash = curFolder.find_last_of('\\');
            std::cout << "Current folder being parsed: '" << curFolder << "'\n";
            if(firstBackSlash == lastBackSlash){ //then there isn't an above folder
                make_folderName = curFolder;
            }else{
                std::string tmpFileName = curFolder.substr(0, lastBackSlash);
                std::cout << tmpFileName<<std::endl;
                std::cout << tmpFileName.find_last_of('\\') << std::endl;
                std::cout << tmpFileName.substr(curFolder.find_last_of('\\') - 4) << std::endl;
                make_folderName = tmpFileName.substr(curFolder.find_last_of('\\'));
            }
            std::cout << "Make folder name: " << make_folderName << std::endl;
            //std::locale loc;
           // for (std::string::size_type i=0; i<make_folderName.length(); ++i)
             //   std::cout << std::toupper(make_folderName[i],loc);


            myfile << make_folderName << "_OBJS = ";
            for(int fileInFolder = 0; fileInFolder < dependencies[curFolder].size(); fileInFolder++){
                std::string filename = dependencies[curFolder][fileInFolder];
                filename = filename.substr(0, filename.find('.')) + ".o";
                myfile << filename << " ";
            }
            myfile << '\n';
        }

    myfile.close();
    }else std::cout << "Unable to open file";


}

int main(int argc, char** argv){
    for (int count{ 0 }; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
        std::string startingPath = argv[count];

        Node* root = new Node(startingPath);
        recurse(root);
        printRoot(root);
        std::cout << "\n Creating makefile...\n";
        createMakefile();
        filePaths.clear();
        foldersWithFiles.clear();
        dependencies.clear();
    }
    return 0;
}