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


double cumulative_sum( std::vector<int> &Cp, std::vector<int> &col_count, int n);


CCS_Matrix transpose(const Matrix & A );





#endif /* Matrix_Operations_hpp */
