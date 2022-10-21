#include <iostream>
#include <fstream>
#include <cstdlib>
bool    algMirrored(int &m, int &h){
    if ((m > 60 || m < 0) || (h > 12 || h < 0))
        return false;
    if (h != 0)
        h = 12 - h;
    if(m != 0)
        m = 60 - m;
    return true;
}

int main() {
    int     iHours = 0, iMinutes = 0;
    std::ifstream               inFile("input.txt");
    std::ofstream               outFile("output.txt");
    std::string                 strInput;
    std::string::size_type      len;
    getline(inFile, strInput);
//    if (inFile.fail())
//        exit(1);
    len = strInput.find(' ');
    iHours = std::stoi(strInput, &len);
    iMinutes = std::stoi(strInput.substr(len), &len);
//    if (!algMirrored(iMinutes, iHours)){
//        inFile.close();
//        outFile.close();
//        exit(1);
//    }
    outFile << iHours << ' ' << iMinutes;
//    inFile.close();
//    outFile.close();
    return 0;
}
