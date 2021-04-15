#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>

struct Record {
    short intR;
    char charR;
    char paddingR;
    signed int int32R;
    float floatR;
    long long fieldR;
};

void readFile(std::string fileName, Record *records, int &sizeR) {
    std::ifstream file;
    int size{0};
    file.open(fileName, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    size = (int) file.tellg();
    file.seekg(0, std::ios::beg);
    sizeR = size / sizeof(Record);
    records = new Record[sizeR];
    int i{0};
    while (file.tellg() < size) {
        Record r;
        file.read(reinterpret_cast<char *>(&r.intR), sizeof(r.intR));
        file.read(reinterpret_cast<char *>(&r.charR), sizeof(r.charR));
        file.read(reinterpret_cast<char *>(&r.paddingR), sizeof(r.paddingR));
        file.read(reinterpret_cast<char *>(&r.int32R), sizeof(r.int32R));
        file.read(reinterpret_cast<char *>(&r.floatR), sizeof(r.floatR));
        file.read(reinterpret_cast<char *>(&r.fieldR), sizeof(r.fieldR));
        //long long tmp = (0x3F800 & r.fieldR) >> 11;
        records[i++] = r;
        //std::cout << r.intR << ", " << r.int32R << ", " << r.floatR << ", " << tmp << std::endl;
    }
    file.close();

}

void writeFile(std::string fileName, Record *records, int size){

}

int main() {

    Record *records;
    int size;
    readFile("sample_data.bin", records, size);
    writeFile("exit.txt", records, size);


}