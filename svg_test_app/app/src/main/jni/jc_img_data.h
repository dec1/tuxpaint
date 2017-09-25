
#pragma once

//-------------------------------------------------
#include <cstdint>
#include <vector>

class JcImgData
{
public:
    JcImgData(const std::vector<uint32_t> & data, int w, int h);
    JcImgData();
    int w = 0;
    int h = 0;
    std::vector<uint32_t> data;
    bool isEmpty(){ return w <=0 && h <=0;}
};



