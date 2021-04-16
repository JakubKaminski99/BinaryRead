#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Record
{
    short intR;
    char charR;
    char paddingR;
    int int32R;
    float floatR;
    long long fieldR;
};

void readFile( std::string fileName, std::vector<Record> &records )
{
    std::ifstream file;
    file.open( fileName, std::ios::in | std::ios::binary );
    file.seekg( 0, std::ios::end );
    int sizeFile = ( int ) file.tellg();
    file.seekg( 0, std::ios::beg );
    int i { 0 };
    while ( file.tellg() < sizeFile )
    {
        Record r;
        file.read( reinterpret_cast<char*> ( &r.intR ), sizeof( r.intR ));
        file.read( reinterpret_cast<char*> ( &r.charR ), sizeof( r.charR ));
        file.read( reinterpret_cast<char*> ( &r.paddingR ), sizeof( r.paddingR ));
        file.read( reinterpret_cast<char*> ( &r.int32R ), sizeof( r.int32R ));
        file.read( reinterpret_cast<char*> ( &r.floatR ), sizeof( r.floatR ));
        file.read( reinterpret_cast<char*> ( &r.fieldR ), sizeof( r.fieldR ));
        records.push_back( r );
    }
    file.close();
}

void writeFileCSV( std::string fileName, std::vector<Record> records )
{
    std::ofstream exitFile;
    exitFile.open( fileName );
    long long tmp{};
    for ( int i{ 0 }; i < records.size(); i++ )
    {
        tmp = ( 0x3F800 & records.at( i ).fieldR ) >> 11;
        exitFile << records.at( i ).intR << "," << records.at( i ).int32R << "," << records.at( i ).floatR << "," << tmp << std::endl;
    }
    exitFile.close();
}

void writeFileTxt( std::string fileName, std::vector<Record> records )
{
    std::ofstream exitFile;
    exitFile.open( fileName );
    for ( int i{0} ; i < records.size() ; i++ )
        exitFile << records.at( i ).charR;
    exitFile.close();
}

int main()
{
    std::vector<Record> records;
    readFile( "sample_data.bin", records );
    writeFileCSV( "exit.csv", records );
    writeFileTxt( "B.txt", records );
    return 0;
}










































//#include <iostream>
//#include <fstream>
//#include <cstdlib>
//#include <cmath>
//#include <vector>
//#include <string>
//
//struct Record {
//    char charR;
//    char paddingR;
//    short intR;
//    int int32R;
//    float floatR;
//    long long fieldR;
//
//    friend std::ostream &operator<<(std::ostream &os, const Record &record) {
//        os << "charR: " << record.charR << " paddingR: " << record.paddingR << " intR: " << record.intR << " int32R: "
//           << record.int32R << " floatR: " << record.floatR << " fieldR: " << record.fieldR;
//        return os;
//    }
//};
//
//void readFile(std::string fileName, Record *records, int &sizeR) {
//    std::ifstream file;
//    file.open(fileName, std::ios::in | std::ios::binary);
//    file.seekg(0, std::ios::end);
//    int sizeFile = (int) file.tellg();
//    file.seekg(0, std::ios::beg);
//    sizeR = sizeFile / 20;
//    records = new Record[sizeR];
//    int i{0};
//    //std::cout << sizeFile << " gowno " << sizeR << " tgwsoja stara " << sizeof(Record) << " " << sizeof(short) << " " << sizeof(char) << " "<< sizeof(float) << " "<< sizeof(int) << " ";
//    while (file.tellg() < sizeFile) {
//        Record r;
//        file.read(reinterpret_cast<char *>(&r.intR), sizeof(r.intR));
//        file.read(reinterpret_cast<char *>(&r.charR), sizeof(r.charR));
//        file.read(reinterpret_cast<char *>(&r.paddingR), sizeof(r.paddingR));
//        file.read(reinterpret_cast<char *>(&r.int32R), sizeof(r.int32R));
//        file.read(reinterpret_cast<char *>(&r.floatR), sizeof(r.floatR));
//        file.read(reinterpret_cast<char *>(&r.fieldR), sizeof(r.fieldR));
//        long long tmp = (0x3F800 & r.fieldR) >> 11;
//        records[i++] = r;
//        //std::cout << r.intR << ", " << r.int32R << ", " << r.floatR << ", " << tmp << std::endl;
//        //std::cout << r.charR;
//        //std::cout << std::endl << std::endl << r << std::endl ;
//        //std::cout << records[i-1] ;
//    }
//    file.close();
//    for (int i{0}; i<sizeR; i++){
//        std::cout << records[i] << std::endl << std::endl ;
//    }
//
//}
//
//void writeFile(std::string fileName, Record *records, int size) {
//    std::ofstream exitFile;
//    exitFile.open(fileName);
//    for (int i{0}; i < size-1; i++) {
//        //std::cout << records[i].charR;
//        //exitFile << << "," <<  << "," << << "," << << std::endl;
//    }
//    exitFile.close();
//
//}
//
//int main() {
//
//    Record *records;
//    int size{0};
//    readFile("sample_data.bin", records, size);
//    std::cout << records[0];
//
//    writeFile("exit.txt", records, size);
//
//    return 0;
//
//}