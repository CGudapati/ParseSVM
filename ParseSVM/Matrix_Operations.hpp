//
//  Matrix_Operations.hpp
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/17/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

#ifndef Matrix_Operations_hpp
#define Matrix_Operations_hpp

#include <stdio.h>
#include "Matrix.h"
#include <vector>
#include <iostream>

template <typename T>
void count_labels(const std::vector<T> & vec){
    int positive = 0;
    int negative = 0;
    for(auto elem : vec){
        if (elem > 0) {
            positive++;
        }
        else{
            negative++;
        }
    }
    std::cout << "pos labels: " << positive << " negative labels: " << negative << std::endl;
}


template <typename T>
void print_vector(const std::vector<T> & vec){
    for(auto elem : vec){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

double cumulative_sum( std::vector<int> &Cp, std::vector<int> &col_count, int n);


CCS_Matrix transpose(const CRS_Matrix & A );





#endif /* Matrix_Operations_hpp */
