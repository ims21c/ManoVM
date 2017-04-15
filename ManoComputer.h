/*
	ManoComputer.h

	YY-MM-DD
	2017-04-09

	Dongguk University
	Computer Science and Engineering

	Operating System Course ( Prof. Kangwoo Lee)

	Homework_
	Make Computer in Morris Mano's Computer System Architecture.

	Students_
	2012111938 Jeonghan Seock
	2012111955 Yunjun Seo

	We using supernet29's Assembler
	https://github.com/supernet29/BasicAssembler
*/
#ifndef _MANOCOMPUTER_H_
#define _MANOCOMPUTER_H_

#include <bitset>
#define MEMORY_SIZE 4069

class ManoComputer {
private:
	// Variables
	std::bitset<1> S;			// S Flip-Flop (Start)
	std::bitset<1> E;			// E Flip-Flop (Carry)
	std::bitset<3> SC;		// SC Flip-Flop
	std::bitset<1> IEN;		// IEN Flip-Flop (Interrupt Enable)
	std::bitset<1> FGI;		// FGI Flip-Flop (I/O In)
	std::bitset<1> FGO;		// FGO Flip-Flop (I/O Out)
	std::bitset<1> R;			// R Flip-Flop
	std::bitset<1> I;			// I bit IR(15)

	std::bitset<8> T;			// Decoded SC 
	std::bitset<8> D;			// Decoded IR(12-14)
	std::bitset<8> INPR;		// 8bit Input register
	std::bitset<8> OUTR;		// 8bit Output register

	std::bitset<16> M[MEMORY_SIZE];	// Memory 4096 words 16bits per Word
	std::bitset<16> DR;		// 16bit Data register
	std::bitset<12> AR;		// 12bit Address register
	std::bitset<16> AC;		// 16bit Accumulator
	std::bitset<16> IR;		// 16bit Instruction register
	std::bitset<12> PC;		// 12bit Program counter
	std::bitset<16> TR;		// 16bit Temporary register



public:
	ManoComputer(void);		// Initialization
	
	std::bitset<1> getS(void);	// getS
	void setM(std::bitset<12> address, std::bitset<16> code);	// Binary code insert to memory 

	void run(void);			// Run

	void printStatus(void);		// Print Status
	void printM(std::bitset<12> startAddress, std::bitset<12> endAddress);	// Print Memory Start to End

};
#endif // _MANOCOMPUTER_H_