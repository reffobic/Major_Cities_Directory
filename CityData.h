//
// Created by Mohamed El-Refai on 24/10/2023.
//

#ifndef ASSIGN_3_CITYDATA_H
#define ASSIGN_3_CITYDATA_H

#include <string>

using namespace std;

struct CityData {
    string country;
    struct DMS {
        int degrees;
        int minutes;
        int seconds;
        char direction;
    } latitude, longitude;
    string lat;  // Add this line for latitude
    string lon;  // Add this line for longitude
};

#endif // ASSIGN_3_CITYDATA_H
