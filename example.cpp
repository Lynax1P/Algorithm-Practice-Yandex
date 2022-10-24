//
// Created by Chaos Sherill on 10/20/22.
//
#include <iostream>
#include <cstdlib>
#include <fstream>

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

s_vec    compare = {-1};
s_obj    firstObj = {-1};

bool    isValidZeroVec(s_vec vecTemp)
{
    if((compare.x == 0 && vecTemp.x != 0) || (compare.y == 0 && vecTemp.y != 0))
        return false;
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

bool    isValidVec(s_vec vecTemp){
    if (vecTemp.x * compare.y == vecTemp.y * compare.x)
       return (true);
    return (false);
}

int algCol(int **crd, int type)
{
    s_vec           vecTemp = {};
    if (type == 1) {
        float y = (float) (crd[1][1] - crd[0][1]) / 2;
        vecTemp = {2, (float) ((float) crd[0][0] + ((float) (crd[3][0] - crd[0][0]) / 2) - firstObj.x),
                   (float) ((float) crd[0][1] + ((float) (crd[1][1] - crd[0][1]) / 2) - firstObj.y)};
    }
    else
        vecTemp = {2, (float)crd[0][0] - firstObj.x, (float)crd[0][1] - firstObj.y};
    if(vecTemp.x == 0 && vecTemp.y == 0)
        return true;
    else if(compare.x == 0 || compare.y == 0)
        return (isValidZeroVec(vecTemp));
    else
        return (isValidVec(vecTemp));
}

int findCompareVector(std::ifstream *inFile, int **crd, int *count)
{
    int type;
    for(;(*count) != 0;(--*count)){
        if(!((*inFile) >> type))
            return 2;
        if (type == 1){
            (*inFile) >> (crd)[0][0];
            (*inFile) >> (crd)[0][1];
            (*inFile) >> (crd)[1][0];
            (*inFile) >> (crd)[1][1];
            (*inFile) >> (crd)[2][0];
            (*inFile) >> (crd)[2][1];
            (*inFile) >> (crd)[3][0];
            (*inFile) >> (crd)[3][1];
            if (firstObj.type == -1) {
                firstObj = {1, (float) crd[0][0] + (float)((float)(crd[3][0] - crd[0][0]) / 2),
                            (float) crd[0][1] + ((float)(crd[1][1] - crd[0][1])/2) };
            }
            else if(compare.type == -1){
                float x = ((float)crd[3][0] - (float)crd[0][0])/2;
                float y = ((float)(crd[1][1] - crd[0][1])/2);;
                compare = {-1, (float)crd[0][0] + ((float)(crd[3][0] - crd[0][0])/2) - firstObj.x,
                           (float)crd[0][1] + y - firstObj.y};
                if(compare.y == 0 && compare.x == 0)
                    compare = {-1};
                else
                    break;
            }
        }
        else if (type == 0){
            (*inFile) >> (crd)[1][0];
            (*inFile) >> (crd)[0][0];
            (*inFile) >> (crd)[0][1];
            if (firstObj.type == -1)
                firstObj = {(char) 0, (float) crd[0][0], (float) crd[0][1]};
            else if(compare.type == -1){
                compare = {1, (float)crd[0][0] - firstObj.x, (float)crd[0][1] - firstObj.y};
                if(compare.y == 0 && compare.x == 0)
                    compare = {-1};
            } else
                break;
        if (compare.type != -1)
            break;
        }
    }
    return true;
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
        crd = new int*[5];
        for(int i = 0; i < 5; ++i)
            crd[i] = new int[2];
        if (findCompareVector(&inFile, crd, &countObj) == 2 || countObj == 0)
            status = 1;
        for(;countObj != 0; countObj--) {
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
                status = 0;
                break;
            }
            status = algCol((crd), type);
            if (status == 1)
                continue;
            else
                break;
        }
        if(status == 1)
            outFile << "Yes";
        else
            outFile << "No";
        for(int i = 0; i < 4; ++i)
            delete crd[i];
        delete crd;
    }
    inFile.close();
    outFile.close();
    return (0);
}