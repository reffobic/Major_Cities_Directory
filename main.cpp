
//

#include <iostream>

#include <iostream>
#include "BinaryTree.h"
#include <fstream>

using namespace std;

struct CityData{
    string country;
    string latitude;
    string longitude;
};

struct Latitude{
    int degrees;
    int minutes;
    int seconds;
    char direction;
};

struct Longitude{
    int degrees;
    int minutes;
    int seconds;
    char direction;
};

void convertDMS(CityData &data, string x, string y)
{//latitude
    char degPos = x.find((char)176);
    char minPos = x.find('\'');
    string degStr = x.substr(0,degPos);
    string minStr = x.substr(degPos+1, minPos-1);
    string direction = x.substr(minPos+1);

    int deg = stoi(degStr);
    int min = stoi(minStr);

    data.latitude.degrees = deg;
    data.latitude.minutes = min;
    data.latitude.direction= direction[0];
//longitude
    degPos = y.find((char)176);
    minPos = y.find('\'');
    degStr = y.substr(0,degPos);
    minStr = y.substr(degPos+1, minPos-1);
    direction = y.substr(minPos+1);

    deg = stoi(degStr);
    min = stoi(minStr);

    data.longitude.degrees = deg;
    data.longitude.minutes = min;
    data.longitude.direction= direction[0];

}

void enterData(binaryTree<string,CityData> &x)
{
    CityData d;
    string city;
    cout<<"Enter the city, country, latitude and longitude: ";
    cin>>city>>d.country>>d.lat>>d.lon;

    x.insert(city, d);
}

void citySearch(binaryTree<string,CityData> &x, string city)
{
    string lat, lon,count;
    CityData d;
    x.retrieve(city, d);
    lat = d.lat;
    lon = d.lon;
    count = d.country;

    cout<<city<<" "<<count<<" "<<lat<<" "<<lon<<endl;
}

CityData cityInfo(binaryTree<string,CityData> &x, string city, string &lat, string &lon, string &count)
{
    CityData d;
    x.retrieve(city, d);
    lat = d.lat;
    lon = d.lon;
    count = d.country;
    convertDMS(d,lat, lon);
    return d;
}

double distanceEQ(double lat1, double lat2, double lon1, double lon2)
{
    const double R = 6371.137; //Earth radius

    //convert decimal degrees to radians
    lat1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    double deltaLat = lat2-lat1;
    double deltaLong = lon2-lon1;

    double a = pow(sin(deltaLat/2),2)+ cos(lat1)*cos(lat2)*pow(sin(deltaLong/2),2);
    double c = 2*atan2(sqrt(a),sqrt(1-a));
    double dist = R*c;

    return dist;

}

double convertDeci(int deg, int min, int sec, char direction)
{
    double deciDeg = deg + min / 60.0 + sec/3600.0;
    if(direction == 'S' || direction == 'W') //swap sign because of angle
    {
        deciDeg = -deciDeg;
    }
    return deciDeg;
}

double getDistance(string city1, string city2, binaryTree<string,CityData> &x)
{
    string lat1, lat2, lon1,lon2,count1,count2;
    CityData d1 = cityInfo(x, city1, lat1, lon1, count1);
    CityData d2 =  cityInfo(x, city2, lat2, lon2, count2);

    double latDec1 = convertDeci(d1.latitude.degrees,d1.latitude.minutes,d1.latitude.seconds,d1.latitude.direction);
    double longDec1 = convertDeci(d1.longitude.degrees,d1.longitude.minutes,d1.longitude.seconds,d1.longitude.direction);
    double latDec2 = convertDeci(d2.latitude.degrees,d2.latitude.minutes,d2.latitude.seconds,d2.latitude.direction);
    double longDec2 = convertDeci(d2.longitude.degrees,d2.longitude.minutes,d2.longitude.seconds,d2.longitude.direction);

    return distanceEQ(latDec1,longDec1,latDec2,longDec2);

}

int main(){

    ifstream a;
    a.open("MCity List.txt");
    int x;
    CityData temp;
    string tempcity;
    while(a>>x){
        a >> tempcity >> temp.latitude >> temp.longitude >> temp.country;
        cout << x << " " << temp.latitude << " " << temp.longitude << temp.country << " " << endl;
    }
    a.close();
}
