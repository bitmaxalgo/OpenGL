
#include <vector>

#include "text.h"


std::vector<float> ogltext::generateMap(NUM choice) {
    std::vector<float> ndc_coordinates;
    if (choice == ZERO) {
        for (int i = 0; i < zero.size(); i ++) {
            int row  = (zero.size() / 5) - i / 5;    
            int column = i % 5;

            float yoffset = 0.05f * row;    
            float xoffset = 0.05f * column;
            if (zero.at(i) == 1) {
                ndc_coordinates.push_back(xoffset);
                ndc_coordinates.push_back(yoffset);
            }
        }
    } else if (choice == ONE) {
        for (int i = 0; i < one.size(); i ++) {
            int row  = (one.size() / 5) - i / 5;    
            int column = i % 5;

            float yoffset = 0.05f * row;    
            float xoffset = 0.05f * column;
            if (one.at(i) == 1) {
                ndc_coordinates.push_back(xoffset);
                ndc_coordinates.push_back(yoffset);
            }
        }
    }


    return ndc_coordinates;
}


std::vector<float> ogltext::zero = {
        1,1,1,1,1,
        1,0,0,0,1,
        1,0,0,0,1,
        1,0,0,0,1,
        1,0,0,0,1,
        1,0,0,0,1,
        1,0,0,0,1,
        1,1,1,1,1
};

std::vector<float> ogltext::one {
        0,1,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,1,1,1,0
};