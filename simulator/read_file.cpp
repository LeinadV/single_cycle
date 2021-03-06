#include"single_cycle.h"
#include<fstream>
#include<vector>
#include<bitset>

void read_file(std::vector<unsigned char>& dimage, uint& sp, std::vector<uint>& iimage, uint& pc, uint& amt_inst){
    std::ifstream ifile("iimage.bin", std::ios::binary|std::ios::ate|std::ios::in);
    
    char* iimage_char;
    
    if(ifile.is_open()){
        auto size=ifile.tellg();
        iimage_char=new char[size];
        ifile.seekg(0, std::ios::beg);
        ifile.read(iimage_char, size);
        ifile.close();
        
        pc=0;
        for(int i=0;i<4;++i){
            pc<<=8;
            pc+=(uint)((unsigned char)(iimage_char[i]));
        }
        if(pc%4) return;//add more information
        amt_inst=0;
        for(int i=4;i<8;++i){
            amt_inst<<=8;
            amt_inst+=(uint)((unsigned char)(iimage_char[i]));
        }
        uint temp;
        iimage.clear();
        for(int i=0;i<256;++i) iimage.push_back(0);
        for(int i=8;i<size;i+=4){
            temp=0;
            for(int j=i;j<i+4;++j){
                temp<<=8;
                temp+=(uint)((unsigned char)(iimage_char[j]));
            }
            if(pc+i-8<1024) iimage[(pc+i-8)/4]=temp;//add more information
            
        }
    }else std::cout << "Cannot open iimage.bin\n";
    
    std::ifstream dfile("dimage.bin", std::ios::binary|std::ios::ate|std::ios::in);
    
    char* dimage_char;
    if(dfile.is_open()){
        auto size2=dfile.tellg();
        dimage_char=new char[size2];
        dfile.seekg(0, std::ios::beg);
        dfile.read(dimage_char, size2);
        dfile.close();
        
        sp=0;
        for(int i=0;i<4;++i){
            sp<<=8;
            sp+=(uint)((unsigned char)(dimage_char[i]));
        }
        uint amt_data=0;
        for(int i=4;i<8;++i){
            amt_data<<=8;
            amt_data+=(uint)((unsigned char)(dimage_char[i]));
        }
        amt_data*=4;
        dimage.clear();
        for(int i=0;i<1024;++i) dimage.push_back('\0');
        for(int i=8;i<size2;++i){
            if(i-8<1024) dimage[i-8]=(unsigned char)(dimage_char[i]);//add more information
        }
    }else std::cout << "Cannot open dimage.bin\n";
    
    return;
}