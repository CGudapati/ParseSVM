//
//  Matrix.h
//  ParseSVM
//
//  Created by Naga V Gudapati on 1/10/19.
//  Copyright © 2019 Naga V Gudapati. All rights reserved.
//

// This defines a struct which has all the necessary information like the row_index, col_ptr
// and nzvales

#ifndef Matrix_h
#define Matrix_h

#include <vector>

struct CRS_Matrix{
    
    long long nzmax;  //maximum number of entries
    int m;  //Number of rows
    int n;  //number of columns
    
    std::vector<double> values;
    std::vector<int> col_index;
    std::vector<int> row_ptr;
    
    std::vector<int> y_label;

    CRS_Matrix() = default;
    
    CRS_Matrix(int m, int n, long long nzmax) {
        this->m = m;
        this->n = n;
        this->nzmax = nzmax;
        this->row_ptr = std::vector<int>((n + 1));
        this->col_index = std::vector<int>(nzmax);
        this->values = std::vector<double >(nzmax);
    }
    
   
};

struct CCS_Matrix{
    
    long long nzmax;  //maximum number of entries
    int m;  //Number of rows
    int n;  //number of columns
    
    std::vector<double> values;
    std::vector<int> row_index;
    std::vector<int> col_ptr;
    
    std::vector<int> y_label;


    CCS_Matrix() = default;
    
    CCS_Matrix(int m, int n, long long nzmax) {
        this->m = m;
        this->n = n;
        this->nzmax = nzmax;
        this->col_ptr = std::vector<int>((n + 1));
        this->row_index = std::vector<int>(nzmax);
        this->values = std::vector<double >(nzmax);
    }
    
};


#endif /* Matrix_h */
