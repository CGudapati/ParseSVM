//
//  ParseSVM.cpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/11/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#include "ParseSVM.hpp"

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




void get_CRSM_from_svm(CRS_Matrix &M, const std::string &file_path){
    std::cout << "Starting the processing of the SVM file" << std::endl;
    std::string path =  file_path;
    
    std::ifstream libsvm_file(path);
    if (libsvm_file.is_open()) {
        std::cout << "Processing the SVM file" << std::endl;
        std::string observation;
        M.row_ptr.push_back(0); //First is always 0 ???
        M.n = 0; //This will be used to store the number of columns
        while (getline(libsvm_file, observation)) {

            //Splitting on whitespace as some SVMS have more than one space charcater or a tab character
            std::istringstream iss_obs(observation);
            std::vector<std::string> splitString(std::istream_iterator<std::string>{iss_obs}, std::istream_iterator<std::string>());
            //I am pusing back the label to the y_label vector
            M.y_label.push_back(std::stoi(splitString[0]));
            
//            This will iterate from the second eleemnet onwards, then split at : and push the first
//            value into col_index and second values into the values vectors.
            for (auto iter = std::next(splitString.begin()); iter != splitString.end(); ++iter) {
                auto col_value = split(*iter, ':');
                M.col_index.push_back(std::stoi(col_value[0])-1);
                M.values.push_back(std::stod(col_value[1]));
                if (M.n < std::stoi(col_value[0])) {  //We keep track of the largest n which will give us the value of largest feature number
                    M.n = std::stoi(col_value[0]);
                }
            }
            M.row_ptr.push_back(static_cast<int>(M.col_index.size()));
        }
        libsvm_file.close();
    }
    else {
        std::cout << "Could not find the SMV file, check again!" << std::endl;
    }
    //numRows will be given by the rowpointer size -1
    M.m = static_cast<int>(M.row_ptr.size())-1;
    M.nzmax = static_cast<long long>(M.values.size());
    std::cout << "Finished processing the LIBSVM file. " << M.m << " observations and " << M.n << " features were read" << std::endl;
}


//I will just transpose the matrix from CRS to CCS
void get_CCSM_from_svm(CCS_Matrix &M_t, const std::string &file_path){
    CRS_Matrix M;
    get_CRSM_from_svm(M, file_path);
    M_t = transpose(M);  //The process switches the m and n values. Beware!
}
