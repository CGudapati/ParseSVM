//
//  main.cpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/10/19.
//  A Simple library to read the libsvm files and return a sparse matrix
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#include <iostream>
#include <string>
#include "ParseSVM.hpp"

int main(int argc, const char * argv[]) {
    
    const std::string file_name = "demo.txt";
    
    Matrix M;
    
    get_CCSM_from_svm(M, file_name);
    
    
    return 0;
}
