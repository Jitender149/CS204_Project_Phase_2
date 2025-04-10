// This is the main file for the RISC-V instruction set simulator

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include"utility.hpp"
#include<fstream>
# include <chrono>  // using this to calculate the time taken by the execution of each instruction
# define ll long long
using namespace std; // using namespace std to avoid writing std:: everywhere
// First define all the variables that we need throughout the program
long long reg[32] = {0}; // register array
long long RS1; // source register 1
long long RS2; // source register 2
long long RD; // destination register
long long RM; // register to be modified
long long RZ; // result of the ALU operation
long long RY; // result of the memory operation
long long RA; // operand 1 for ALU operation
long long RB; // operand 2 for ALU operation
long long PC; // program counter
long long IR; // instruction register
long long MuxB_select; // select the operand for the ALU operation
long long MuxC_select; // select the operand for the memory operation
long long MuxINC_select; // select the operand for the immediate operation
long long MuxY_select; // select the operand for the memory operation
long long MuxPC_select; // select the operand for the PC update
long long MuxMA_select; // select the operand for the memory address
long long RegFileAddrA; // address of the source register 1
long long RegFileAddrB; // address of the source register 2
long long RegFileAddrC; // address of the destination register
long long RegFileInp; // input to the register file
long long RegFileAOut; // output of the register file
long long RegFileBOut; // output of the register file
long long MAR; // memory address register
long long MDR; // memory data register
long long opcode; // opcode of the instruction
long long func3; // function 3 of the instruction
long long func7; // function 7 of the instruction
long long numBytes; // number of bytes to be read/written
long long RF_Write; // write enable for the register file
long long immed; // immediate value
long long PC_Temp; // temporary PC value
long long Mem_Write; // write enable for the memory
long long Mem_Read; // read enable for the memory
long long ALUOp[15] = {0}; // ALU operation array
long long ui, clk=0; // ui is the instruction unit and clk is the clock cycle
long long isStepClicked = 0; // step clicked flag

extern long long RS1,RS2;
// Now we have the maps to store the data and instruction memory
std::map<long long  , std::vector<long long  >> dataMemory;
std::map<long long  , std::vector<std::string>> instructionMemory;
// Printing the contents of dataMemory and instructionMemory 
// Format is kept same as RISC-V ie little endian

// Initial declarations of the functions defined later in the code
bool validateDataSegment(vector<string> a);
bool validateInstruction(vector<string> a);
void run_RISC_simulator();

int main() {
    ifstream mcFile("input.mc");
    bool flag = 0;
    string y;
    while(getline(mcFile, y)) {
        vector<string> x;
        string temp = "";
        for(auto it:y) {
            if(it==' ' || it=='\t') {
                if(temp.size()>1 || (temp!=" " && temp!="\t")) x.push_back(temp);
                temp = "";
                continue;
            }
            temp+=it;
        }
        if(temp.size()>0) x.push_back(temp);
        if(flag==1) {
            if(validateDataSegment(x)==0) {
                cout<<"Invalid Data segment"<<x[0]<<"\n";
                mcFile.close();
                return 1;
            }
            long long x1 = strtoll(x[0].c_str(), nullptr, 16);
            dataMemory[x1].push_back((strtoll(x[1].c_str(), nullptr, 16)) & strtoll("0xFF", nullptr, 16));
            dataMemory[x1].push_back(((strtoll(x[1].c_str(), nullptr, 16)) & strtoll("0xFF00", nullptr, 16))>>8);
            dataMemory[x1].push_back(((strtoll(x[1].c_str(), nullptr, 16)) & strtoll("0xFF0000", nullptr, 16))>>16);
            dataMemory[x1].push_back(((strtoll(x[1].c_str(), nullptr, 16)) & strtoll("0xFF000000", nullptr, 16))>>24);
        }
        for(auto it:x) if(it=="$") flag = 1;
        if(flag == 0) {
            if(validateInstruction(x)==0) {
                cout<<"Invalid Instruction segment"<<x[1]<<"\n";
                mcFile.close();
                return 1;
            }
            long long x1 = strtoll(x[0].c_str(), nullptr, 16);
            for(int i = 0; i < 4; ++i) {
                string temps = "0xFF";
                for(int j = 0; j < 2*i; ++j) temps+="0";
                instructionMemory[x1].push_back(hex((strtoll(x[1].c_str(), nullptr, 16) & strtoll(temps.c_str(), nullptr, 16)) >> (8*i)));
                temps = "";
                if((2-instructionMemory[x1][i].size()) > 0) for(int j = 0; j < (2-instructionMemory[x1][i].size()); ++j) temps+="0";
                instructionMemory[x1][i] = temps + instructionMemory[x1][i];
            }
        }
    }
    mcFile.close();

    // Print all contents of dataMemory
    cout << "DATA MEMORY CONTENTS:\n";
    for (const auto& it : dataMemory) {
        cout << "Address: 0x" << hex << it.first << " Data: ";
        for (const auto& data : it.second) {
            cout << data << " ";
        }
        cout << "\n";
    }

    // Print all contents of instructionMemory
    cout << "INSTRUCTION MEMORY CONTENTS:\n";
    for (const auto& it : instructionMemory) {
        cout << "Address: 0x" << hex << it.first << " Instructions: ";
        for (const auto& instr : it.second) {
            cout << instr << " ";
        }
        cout << "\n";
    }
    cout<< "Now running the simulator: \n";
    run_RISC_simulator();
    return 0;
}

bool validateDataSegment(vector<string> a) {
    if(a.size() != 2) return 0;
    string addr = a[0];
    string data = a[1];
    if((addr[0]!='0'&& addr[1]!='x') || (data[0]!='0' && data[1]!='x')) return 0;
    try
    {
        if(strtoll(addr.c_str(), nullptr, 16) < strtoll("0x10000000", nullptr, 16)) return 0;
        strtoll(data.c_str(), nullptr, 16);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 1;
}

bool validateInstruction(vector<string> a) {
    if(a.size() != 2) return 0;
    string addr = a[0];
    string data = a[1];
    try
    {
        strtoll(addr.c_str(), nullptr, 16);
        strtoll(data.c_str(), nullptr, 16);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 1;
}

void run_RISC_simulator() {
    bool flag = 1;
    ofstream out("output.txt");
    ofstream json("out.json");
    long long i = 0;
    json<<"{\n";
    while((instructionMemory.find(strtoll(("0x"+hex(PC)).c_str(), nullptr, 16)) != instructionMemory.end()) && flag) {
        json<<"\t\""<<i<<"\": {\n";
        auto start = std::chrono::high_resolution_clock::now();
        string msg1 = fetch1();
        json<<"\t\t\"FETCH\": \n\t\t\t\"Reading word from memory: 0x" << hex(PC) << "\",\n";
        json << "\t\t\t\"IR\": " << msg1 << ",\n";
        string msg = Decode();
        json << "\t\t\"Decode\":{\n";
        json << "\t\t\t\"Opcode\": " << opcode << ",\n";
        json << "\t\t\t\"RD\": " << RD << ",\n";
        json << "\t\t\t\"Func3\": " << func3 << ",\n";
        json << "\t\t\t\"RS1\": " << RS1 << ",\n";
        json << "\t\t\t\"RS2\": " << RS2 << ",\n";
        json << "\t\t\t\"Func7\": " << func7 << ",\n";
        json << "\t\t\t\"Immediate\": " << immed << "},\n";
        json<<"\t\t\t\"Message\": \""<<msg<<"\",\n";
        // now we need to print the control signals
        json << "\t\t\t\"Control Signals\":{\n";
        json << "\t\t\t\t\"RF_Write\": " << RF_Write << ",\n";
        json << "\t\t\t\t\"MuxB_select\": " << MuxB_select << ",\n";
        json << "\t\t\t\t\"MuxY_select\": " << MuxY_select << ",\n";
        json << "\t\t\t\t\"Mem_Write\": " << Mem_Read << ",\n";
        json << "\t\t\t\t\"Mem_Read\": " << Mem_Write << "},\n";
        // write rest all the control signal as welll
        json << "\t\t\t\t\"MuxPC_select\": " << MuxPC_select << ",\n";
        json << "\t\t\t\t\"MuxMA_select\": " << MuxMA_select << ",\n";
        json << "\t\t\t\t\"MuxINC_select\": " << MuxINC_select << ",\n";
        json << "\t\t\t\t\"MuxC_select\": " << MuxC_select << ",\n";
        
        Execute();
        json << "\t\t\"Execute\":{\n";
        // # reading registers
        // # A:
        // # B:
        // # alu.operand1
        // # alu.operand2
        // # alu.RM
        // # alu.RZ
        // # alu.RY
        json << "\t\t\t\"alu.RA\": " << RA << ",\n";
        json << "\t\t\t\"alu.RB\": " << RB << ",\n";
        json << "\t\t\t\"ALU_Result\": " << RZ << ",\n";
        json << "\t\t\t\"MuxB_Result\": " << MuxB_select << ",\n";
        json << "\t\t\t\"MuxY_Result\": " << MuxINC_select << "},\n";

        std::string msg3 = MemoryAccess();
        json << "\t\t\"MemoryAccess\":{\n";
        json << "\t\t\t\"RY\": " << RY << ",\n";
        json << "\t\t\t\"MAR\": " << MAR << ",\n";
        json << "\t\t\t\"MDR\": " << MDR << ",\n";
        json << "\t\t\t\"Updating PC\": \"" << msg3 << "\"},\n";
        std::string msg4 = RegisterUpdate();
        auto end = std::chrono::high_resolution_clock::now();   
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        json << "\t\t\"RegisterUpdate\": \n\t\t\t\"" << msg4 << "\",\n";
        clk += 1;
        json<< "\t\t\"Clock\": " << clk << ",\n";
        json << "\t\t\"Time taken (in microseconds)\": " << duration.count() << " ,\n";
        if(isStepClicked==1) {
            isStepClicked=0;
            flag=0;
        }
        json<<"\t\t\"PC\":"<<PC<<",\n";
        json<<"\t\t\"Reg\": ["; for(int i = 0; i < 31; ++i) json<<reg[i]<<", "; json<<reg[31]<<"],\n";
        json<<"\t\t\"Data\": {\n";
        for(auto it:dataMemory) {
            json<<"\t\t\t\"0x"<<hex(it.first)<<"\": ["; 
            for(auto j:it.second) json<<j<<" , ";
            json.seekp(-3, std::ios_base::end);
            json<<"],\n";
        }
        json.seekp(-3, std::ios_base::end); json<<"\n";
        json<<"\t\t}\n";
        json<<"\t},\n";
        ++i;
    }
    json.seekp(-3, std::ios_base::end); json<<"\n";
    json<<"}";
    json.close();
    out<<"REGISTERS :\n";
    for(auto it:reg) out<<it<<"\n";
    out<<"DATA :\n";
    for(auto it:dataMemory) {out<<hex(it.first)<<" "; for(auto j:it.second) out<<j<<" "; out<<"\n";}
    out.close();
    return;
}