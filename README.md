# ManoVM
Implementing Virtual Machine for M. Morris Mano's Computer Architecture Book.

# Features
* **8 Registers:** AR(12), PC(12), DR(16), AC(16), IR(16), TR(16), INPR(8), OUTR(8)
* **Memory:** 4096 * 16bit SRAM
* **7 Flip-Flops:** SC(3), T(8)(decoded SC), E(1)(Carry-bit), R(1), IEN(1), I(1)(IR[15]), D(8)(decoded IR[12..14])
* **Control:** Fetch, Decode, Indirect, Interrupt
* **Memory Reference:** AND, ADD, LDA, STA, BUN, BSA, ISZ
* **Register Reference:** CLA, CLE, CMA, CME, CIR, CIL, INC, SPA, SNA, SZA, SZE, HLT
* **Input/Output Reference:** INP, OUT, SKI, SKO, ION, IOF
* **NO Clock Cycle:** It operates by the sequence counter

# Assembler
We used an supernet29's assembler when testing a our virtual machine.

https://github.com/supernet29/BasicAssembler

# Build instructions
* **Visual Studio 2017 for windows**
	1. [Create] new empty project.
	2. [Add] already exist source file main.cpp ManoComputer.cpp to project
	3. [Add] already exist header file ManoComputer.h to project
	4. [Build] and [Run].


* **Make & GNU G++ Compiler for Linux**
	1. make
	2. ./ManoVM


* **GNU G++ Compiler for Linux**
	1. g++ -c ManoComputer.cpp
	2. g++ -c main.cpp
	3. g++ main.o ManoComputer.o –o ManoVM
	4. ./ManoVM
	
# ManoVM Programming

Modify setM() function in main.cpp

**void setM(std::bitset<12> address, std::bitset<16> code);**

# Programming example 1

    /*
    p.146 table 6-5 two numbers add example
		ORG 0	/Origin of program is location 0
		LDA A	/Load operand from location A
		ADD B	/Add operand from location B
		STA C	/Store sum in location C
		HLT	/Halt computer
	A,	DEC 83	/Decimal operand
	B,	DEC –23	/Decimal operand
	C,	DEC 0	/Sum stored in location C
		END
    */
	computer.setM(0x0, 0x2004);
	computer.setM(0x1, 0x1005);
	computer.setM(0x2, 0x3006);
	computer.setM(0x3, 0x7001);
	computer.setM(0x4, 0x53);
	computer.setM(0x5, 0xffe9);
	computer.setM(0x6, 0x0);
 
 # Programming example 2

    /*
	p.162 table 6-14 two numbers multiple example
			ORG 100
		LOP, 	CLE 	/Clear E
		LDA Y	/Load multipler
		CIR	/Transfer multipler bit to E
		STA Y	/Store shifted multiplier
		SZE 	/Check if bit is zero
		BUN ONE	/Bit is one; go to ONE
		BUN ZRO /bit is zero; go to ZRO
	ONE, 	LDA X 	/Load multiplicand
		ADD P 	/Add to partial product
		STA P	/Store partial product
		CLE 	/Clear E
	ZRO, 	LDA X	/Load multiplicand
		CIL	/Shift left
		STA X	/Store shifted multiplicand
		ISZ CTR	/Increment counter
		BUN LOP	/Counter not zero; repeat loop
		HLT	/Conter is zero; halt
	CTR,	DEC -8	/This location serves as a counter
	X,	HEX 000F/Multiplicand stored in here
	Y,	HEX 000B/Multiplier stored in here
	P,	HEX 0	/Product formed here
		END
    */
	computer.setM(0x0, 0x2004);
	computer.setM(0x1, 0x1005);
	computer.setM(0x2, 0x3006);
	computer.setM(0x3, 0x7001);
	computer.setM(0x4, 0x53);
	computer.setM(0x5, 0xffe9);
	computer.setM(0x6, 0x0);
 
 
