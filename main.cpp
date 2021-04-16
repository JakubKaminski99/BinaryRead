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

void readFile( std::string fileName, std::vector<Record> &records )  //Odpowiada za odczyt pliku binarnego oraz zapis wektora
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
