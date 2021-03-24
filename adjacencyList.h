#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;
class Lista{
private:
    map<float, map<string, string> > vinos;
public:
    int addVino(string country, string title, string points, string price, string province, string region, string variety, string pricePerPoint);
};
int Lista::addVino(string country, string title, string points, string price, string province, string region, string variety, string pricePerPoint){
    float ppp = stof(pricePerPoint);
    map<string, string> props;
    props.emplace("country", country);
    props.emplace("points", points);
    props.emplace("price", price);
    props.emplace("province", province);
    props.emplace("region", region);
    props.emplace("variety", variety);
    props.emplace("pricePerPoint", pricePerPoint);
    props.emplace("title", title);

    vinos.emplace(ppp, props);

    return 1;
    
    }