//
//  ParseSVM.hpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/11/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#ifndef ParseSVM_hpp
#define ParseSVM_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>      // std::stringstream, std::stringbuf
#include "Matrix.h"
#include "Matrix_Operations.hpp"

//
//   We shall try to read the libsvm file line by line and convert it into a simple compressed
//   row storage matrix. 
void get_CRSM_from_svm(Matrix &M, const std::string &filename);
void get_CCSM_from_svm(Matrix &M, const std::string &filename);


#endif /* ParseSVM_hpp */
