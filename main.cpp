//
// Created by Chaos Sherill on 10/20/22.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#define     FIRST   -9
struct s_obj {
    char       type;
    float       x;
    float       y;
};

struct s_vec {
    char       type;
    float       x;
    float       y;
};

bool    isValidZeroVec(s_vec compare, s_vec vecTemp)
{
    if((compare.x == 0 && vecTemp.x != 0) || (compare.y == 0 && vecTemp.y != 0))
        return false;
    else if((compare.y == 0 && vecTemp.x == 0 ) || (compare.x == 0 && vecTemp.y == 0))
        return true;
    else if(compare.y == 0)
    {
        // vecTemp || compare => compare == (k * vecTemp.x) : (k * vecTemp.y)  >> where k = compare.x / vecTemp.x
        float ll = (((compare.x) / (vecTemp.x)) * vecTemp.x);
        if(compare.x != ll)
            return false;
    }
    else if (compare.x == 0)
    {
        // vecTemp || compare => compare == (k * vecTemp.x) : (k * vecTemp.y)  >> where k = compare.y / vecTemp.y
        if(compare.y != ((compare.y / (vecTemp.y)) * vecTemp.y))
            return false;
    }
    return true;
}

bool    isValidVec(s_vec compare, s_vec vecTemp){
    if (vecTemp.x / compare.x == vecTemp.y / compare.y)
       return (true);
    return (false);
}

int algCol(int **crd, int type)
{
    static s_vec    compare = {-1};
    static s_obj    firstObj = {-1};
    s_vec           vecTemp = {};

    if (firstObj.type == -1){
        if(type == 1)
            firstObj = { 1, (float)crd[0][0] + ((float)(crd[3][0] - crd[0][0])/2),
                         (float)crd[1][1] + ((float)(crd[2][1] - crd[1][1])/2)};
        else
            firstObj = {(char)0,(float)crd[0][0], (float)crd[0][1]};
        return FIRST;
    }
    else if (compare.type == -1)
    {
        if(type == 1)
            compare = {1, (float)crd[0][0] + ((float)(crd[3][0] - crd[0][0])/2) - firstObj.x,
                       (float)crd[1][1] + ((float)(crd[2][1] - crd[1][1])/2) - firstObj.y};
        else
            compare = {0, (float)crd[0][0] - firstObj.x, (float)crd[0][1] - firstObj.y};
        return FIRST;
    }
    else if(compare.x == 0 || compare.y == 0){
        if (type == 1)
            vecTemp = {2, (float)((float)crd[0][0] + ((float)(crd[3][0] - crd[0][0]) / 2) - firstObj.x),
                    (float)((float)crd[1][1] + ((float) (crd[2][1] - crd[1][1]) / 2) - firstObj.y)};
        else
            vecTemp = {2, (float)crd[0][0] - firstObj.x, (float)crd[0][1] - firstObj.y};
        return (isValidZeroVec(compare,vecTemp));
    }
    else {
        if (type == 1)
            vecTemp = {2, (float)((float)crd[0][0] + ((float)(crd[3][0] - crd[0][0]) / 2) - firstObj.x),
                       (float) ((float)crd[1][1] + ((float) (crd[2][1] - crd[1][1]) / 2) - firstObj.y)};
        else
            vecTemp = {2, (float)crd[0][0] - firstObj.x, (float)crd[0][1] - firstObj.y};
        return (isValidVec(compare,vecTemp));
    }
}

int main()
{
//    std::ifstream           inFile("input.txt");
//    std::ofstream           outFile("output.txt");
    std::ifstream           inFile("../input.txt");
    std::ofstream           outFile("../output.txt");
    int                     countObj;
    int                     type;
    int                     **crd;
    int                     status;

    if(inFile.fail())
        exit(1);
    inFile >> countObj;
    if (countObj <= 0)
        outFile << "No";
    else if (countObj == 1 || countObj == 2)
        outFile << "Yes";
    else {
        crd = new int*[4];
        for(int i = 0; i < 4; ++i)
            crd[i] = new int[2];
        while(countObj--) {
            if(!(inFile >> type))
                break;
            if (type == 1){
                inFile >> (crd)[0][0];
                inFile >> (crd)[0][1];
                inFile >> (crd)[1][0];
                inFile >> (crd)[1][1];
                inFile >> (crd)[2][0];
                inFile >> (crd)[2][1];
                inFile >> (crd)[3][0];
                inFile >> (crd)[3][1];
            }
            else if (type == 0){
                inFile >> (crd)[1][0];
                inFile >> (crd)[0][0];
                inFile >> (crd)[0][1];
            }
            else {
                outFile << "No";
                status = 0;
                break;
            }
            status = algCol((crd), type);
            if(status == FIRST)
                continue;
            else if (status == 1)
                continue;
            else {
                outFile << "No";
                break;
            }
        }
        if(status == 1)
            outFile << "Yes";
        for(int i = 0; i < 4; ++i)
            delete crd[i];
        delete crd;
    }
    inFile.close();
    outFile.close();
    return (0);
}