//
//  ParseSVM.cpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/11/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#include "ParseSVM.hpp"

template <typename T>
void print_vector(const std::vector<T> & vec){
    for(auto elem : vec){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


//#code taken from fluent cpp which splits a string into a vector using delimiters
std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}




void get_CRSM_from_svm(Matrix &M, const std::string &filename){
    std::cout << "Starting the processing of the SVM file" << std::endl;
    std::string path = "../../ParseSVM/data/" + filename;
    
    std::ifstream libsvm_file(path);
    if (libsvm_file.is_open()) {
        std::cout << "Processing the SVM file" << std::endl;
        std::string observation;
        M.row_ptr.push_back(0); //First is always 0 ???
        M.n = 0; //This will be used to store the number of columns
        while (getline(libsvm_file, observation)) {
//            printf("%s", observation.c_str());
//            printf("\n");
            
            std::vector<std::string> splitString = split(observation, ' ');
//            std::cout << "num of elements: " << splitString.size() << "\n";
//            std::cout << "Label is " << std::stoi(splitString[0]) << "\n";
            for (auto iter = std::next(splitString.begin()); iter != splitString.end(); ++iter) {
                auto col_value = split(*iter, ':');
//                std::cout << "position: " << col_value[0] << "  " << "value: " << col_value[1] << std::endl;
                M.col_index.push_back(std::stoi(col_value[0])-1);
                M.values.push_back(std::stod(col_value[1]));
                if (M.n < std::stoi(col_value[0])) {
                    M.n = std::stoi(col_value[0]);
                }
            }
            M.row_ptr.push_back(static_cast<int>(M.col_index.size()));
            // using printf() in all tests for consistency
        }
        libsvm_file.close();
    }
    else {
        std::cout << "Could not find the SMV file, check again!" << std::endl;
    }
    //numRows will be given by the rowpointer size -1
    M.m = static_cast<int>(M.row_ptr.size())-1;
    M.nzmax = static_cast<long long>(M.values.size());
    std::cout << "Size of values: " << M.values.size() << "\n";
    std::cout << "Size of col_index: " << M.col_index.size() << "\n";
    std::cout << "Size of row_pointer: " << M.row_ptr.size() << "\n";
    std::cout << "num cols: " << M.n << std::endl;
    std::cout << "num rows: " << M.m << std::endl;
    std::cout << "nzMax : " << M.nzmax << std::endl;
    
    print_vector(M.values);
    print_vector(M.col_index);
    print_vector(M.row_ptr);


}


//I will just transpose the matrix from CRS to CCS  But this can wait
void get_CCSM_from_svm(Matrix &M, const std::string &filename){
    get_CRSM_from_svm(M, filename);
    CCS_Matrix M_t = transpose(M);
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "Size of values: " << M_t.values.size() << "\n";
    std::cout << "Size of row_index: " << M_t.row_index.size() << "\n";
    std::cout << "Size of col_ptr: " << M_t.col_ptr.size() << "\n";
    std::cout << "num cols: " << M_t.n << std::endl;
    std::cout << "num rows: " << M_t.m << std::endl;
    std::cout << "nzMax : " << M_t.nzmax << std::endl;

    print_vector(M_t.values);
    print_vector(M_t.row_index);
    print_vector(M_t.col_ptr);
    
}
