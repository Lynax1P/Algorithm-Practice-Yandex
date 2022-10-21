//
// Created by Chaos Sherill on 10/20/22.
//
#include "iostream"
#include "fstream"
#include "cstdlib"

bool    isMinStr(std::string &last, std::string strNew)
{
    if(last.empty())
        last = strNew;
    else if(last.size() > strNew.size())
        last = strNew;
    else
    {
        for(int i = 0; i < last.size(); ++i){
            if (last[i] == strNew[i])
                continue;
            else if (last[i] < strNew[i])
                return false;
            else{
                last = strNew;
                break;
            }

        }
    }
    return true;
}

bool    algPalind(std::string &arg)
{
    std::string                         strBuf;
    std::string::size_type              len = arg.size();
    int                                 iMinVec = 0;

    for(int j = 0, i = 1; j < len;++j, ++i)
    {
        if(arg[j] == arg[i]) {
            isMinStr(strBuf, arg.substr(j, 2));
        }
        else if (arg[j] == arg[i + 1]){
            isMinStr(strBuf, arg.substr(j, 3));
        }
    }
    if(strBuf.empty())
        return false;
    arg = strBuf;
    return true;
}

int main()
{
    std::ifstream               inFile("../input.txt");
    std::ofstream               outFile("../output.txt");
    std::string                 strInput;
    getline(inFile, strInput);
    if (inFile.fail())
        exit(1);
    if (algPalind(strInput))
        outFile <<  strInput;
    else
        outFile << "-1";
    inFile.close();
    outFile.close();
    return (0);
}