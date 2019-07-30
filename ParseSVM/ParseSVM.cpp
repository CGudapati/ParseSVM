//
//  ParseSVM.cpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/11/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#include <iterator>
#include "ParseSVM.hpp"

//#code taken from fluent cpp which splits a string into a vector using delimiters
void split(std::vector<std::string>& tokens, const std::string& s, char delimiter)
{
    tokens.clear();
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    
}


void get_CRSM_from_svm(Classification_Data_CRS &M, const std::string &file_path){
    std::string path =  file_path;
    
    std::vector<std::string> tokens(2);
    
    std::ifstream libsvm_file(path);
    if (libsvm_file.is_open()) {
        std::cout << "Processing the SVM file" << std::endl;
        std::string observation;
        M.row_ptr.push_back(0); //First is always 0 ???
        M.n = 0; //This will be used to store the number of columns
        while (getline(libsvm_file, observation)) {
            
            //Splitting on whitespace as some SVMS have more than one space character or a tab character
            std::istringstream iss_obs(observation);
            std::vector<std::string> splitString(std::istream_iterator<std::string>{iss_obs}, std::istream_iterator<std::string>());
            //I am pushing back the label to the y_label vector
            M.y_label.push_back(std::stoi(splitString[0]));
            
            //            This will iterate from the second element onwards, then split at : and push the first
            //            value into col_index and second values into the values vectors.
            for (auto iter = std::next(splitString.begin()); iter != splitString.end(); ++iter) {
                split(tokens, *iter, ':');
                auto& col_value = tokens;
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
    
    //Normaliztion of the problem data. This is just normalizing each observation.
    
    for (std::size_t i = 0; i < M.row_ptr.size(); i++) {
        //Let us normalize the feature values of each observation
        // Step 1) calculate the norm of all the features belonging to a single observation
        // Step 2) divide each feature value of every observation using the respective observation's norm

        //Step 1):
        auto norm_sqrd = 0.0;
        for(auto j = M.row_ptr[i]; j < M.row_ptr[i+1]; j++){
            norm_sqrd += std::pow(M.values[j], 2);
        }
        auto norm = std::sqrt(norm_sqrd);

        //Step 2):
        for(auto j = M.row_ptr[i]; j < M.row_ptr[i+1]; j++){
            M.values[j] = M.values[j]/norm;
        }
    }
    
    
    
    
    std::cout << "Finished processing the LIBSVM file. " << M.m << " observations and " << M.n << " features were read. The total number of non-zero elements are: " << M.nzmax << std::endl;
}


//I will just transpose the matrix from CRS to CCS
void get_CCSM_from_svm(Classification_Data_CCS &M_t, const std::string &file_path){
    Classification_Data_CRS M;
    get_CRSM_from_svm(M, file_path);
    M_t = transpose(M);  //The process switches the m and n values. Beware!
}
