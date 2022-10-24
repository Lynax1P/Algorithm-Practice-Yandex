//
// Created by Chaos Sherill on 10/24/22.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#define     X 0
#define     Y 1
struct s_obj{
    int     type;
    float   xCentre;
    float   yCentre;
};

struct s_vec{
    float   xLine;
    float   yLine;
};

s_obj   objectA = {-1};
s_vec   vectorAB = {0,0};

int findPositionMinCord(float **crd){
    int temp = 0;
    for(int i = 1; i < 2; ++i)
        if(crd[temp][0] > crd[i][0])
            temp = i;
    if(crd[temp][0] == crd[(temp+1)%4][0]) {
        if (crd[temp][1] > crd[(temp + 1) % 4][1])
            temp = (temp + 1) % 4;
    }
    else
    {
        if (temp == 0 && crd[temp][1] > crd[temp + 3][1])
            temp += 3;
        else if(temp != 0 && crd[temp][1] > crd[(temp-1)][1])
            temp = temp - 1;
    }
    return temp;
}

void    initObjectA(int *countObj, float  **crd, std::ifstream *inFile){
    int         type;
    int         posMin;

    (*countObj) -= 1;
    (*inFile) >> type;
    if(type == 1) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 2; ++j)
                (*inFile) >> crd[i][j];
        posMin = findPositionMinCord(crd);
        objectA = {type, crd[posMin][0] + (crd[(posMin + 2)%4][0] - crd[posMin][0]),
                            crd[posMin][1] + (crd[(posMin + 2)%4][0] - crd[posMin][0])};
    }
    else
    {
        (*inFile) >> crd[1][0];
        (*inFile) >> crd[0][0];
        (*inFile) >> crd[0][1];
        objectA = {type, crd[0][0], crd[0][1]};
    }
}

void    initCompareVector(int *countObj, float  **crd, std::ifstream *inFile, bool *status){
    int     type;
    s_obj   objectB;
    int     posMin;

    for(;*countObj > 0;--*countObj)
    {
        if(!((*inFile) >> type)) {
            (*status) = true;
            break;
        }
        if(type == 1){
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 2; ++j)
                    (*inFile) >> crd[i][j];
            posMin = findPositionMinCord(crd);
            objectB = {type, crd[posMin][0] + (crd[(posMin + 2)%4][0] - crd[posMin][0]),
                       crd[posMin][1] + (crd[(posMin + 2)%4][0] - crd[posMin][0])};
        }
        else {
            (*inFile) >> crd[1][0];
            (*inFile) >> crd[0][0];
            (*inFile) >> crd[0][1];
            objectB = {type, crd[0][0], crd[0][1]};
        }
        if(objectB.xCentre == objectA.xCentre && objectB.yCentre == objectA.yCentre)
            continue;
        else {
            //The construction of the vector is based on the bases, the path from A -> B
            //AB => (Bx-Ax;By-Ay)
            vectorAB = {objectB.xCentre - objectA.xCentre,objectB.yCentre - objectA.yCentre};
            break;
        }
    }
}

bool isColZeroVector(s_vec vectorAC)
{
    //AB(0,Y) != AC(X,0)
    if(vectorAB.xLine == 0 != vectorAC.xLine || vectorAB.yLine == 0 != vectorAC.yLine)
        return false;
    //AB (0,Y) => ABy == (ABy / ACy) * ACy => AB||AC
    else if (vectorAB.xLine == 0 &&
                    vectorAB.yLine != (vectorAB.yLine/vectorAC.yLine) * vectorAC.yLine)
        return false;
    //AB (X,0) => ABx == (ABx / ACx) * ACx => AB||AC
    else if (vectorAB.yLine == 0 &&
                    vectorAB.xLine != (vectorAB.xLine/vectorAC.xLine) * vectorAC.xLine)
        return false;
    else
        return true;
}

bool isColVector(s_vec vectorAC)
{
    if(vectorAC.xLine * vectorAB.yLine == vectorAC.yLine * vectorAB.xLine)
        return true;
    return false;
}

//The construction of the vector is based on the bases, the path from A -> C
//AC => (Cx-Ax;Cy-Ay)
//This fnc check collinearity AB||AC
bool algCollinearity(s_obj objectC){
    s_vec  vectorAC = {objectC.xCentre - objectA.xCentre, objectC.yCentre - objectA.yCentre};

    if (vectorAC.xLine == 0 && vectorAC.yLine == 0)
        return true;
    else if (vectorAC.xLine == 0 || vectorAC.yLine == 0)
        return isColZeroVector(vectorAC);
    else
        return isColVector(vectorAC);
}

int main(){
    std::ifstream   inFile("../input.txt");
    std::ofstream   outFile("../output.txt");
    int             countObj = 0;
    s_obj           objTemp;

    if(inFile.fail())
        exit(1);
    else if (!(inFile >> countObj) || countObj <= 0)
        outFile << "No";
    else {
        float** crd = new float*[4];
        bool    status = false;
        for(int i = 0; i < 4; ++i)
            crd[i] = new float[2];
        initObjectA(&countObj,crd, &inFile);
        initCompareVector(&countObj, crd, &inFile, &status);
        if(countObj == 0)
            status = true;
        for(int type;countObj > 0;--countObj){
            if(!(inFile >> type))
                break;
            else if(type == 1) {
                for (int i = 0; i < 4; ++i)
                    for (int j = 0; j < 2; ++j)
                        (inFile) >> crd[i][j];
                int posMin = findPositionMinCord(crd);
                objTemp = {type, crd[posMin][0] + (crd[(posMin + 2)%4][0] - crd[posMin][0]),
                           crd[posMin][1] + (crd[(posMin + 2)%4][0] - crd[posMin][0])};
            }
            else {
                (inFile) >> crd[1][0];
                (inFile) >> crd[0][0];
                (inFile) >> crd[0][1];
                objTemp = {type, crd[0][0], crd[0][1]};
            }
            if (!(status = algCollinearity(objTemp)))
                break;
            else
                continue;
        }
        if(status)
            outFile << "Yes";
        else
            outFile << "No";
    }
    inFile.close();
    outFile.close();
}