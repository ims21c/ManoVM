/*
	ManoComputer.cpp

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
#include "ManoComputer.h"
#include <iostream>
#define MEMORY_SIZE 4069


// Initialization
ManoComputer::ManoComputer(void) {

	this->S.set();
	this->E.reset();
	this->SC.reset();
	this->IEN.reset();
	this->FGI.reset();
	this->FGO.reset();
	this->R.reset();
	this->I.reset();

	this->T.reset();
	this->D.reset();
	this->INPR.reset();
	this->OUTR.reset();

	for (int i = 0; i < MEMORY_SIZE; i++)
		this->M[i].reset();

	this->DR.reset();
	this->AR.reset();
	this->AC.reset();
	this->IR.reset();
	this->PC.reset();
	this->TR.reset();
}// END - ManoComputer(void)


// getS
std::bitset<1> ManoComputer::getS(void) {

	return this->S;
}


// Binary code insert to memory 
void ManoComputer::setM(std::bitset<12> address, std::bitset<16> code) {
	this->M[address.to_ulong()] = code;
}


// Run
void ManoComputer::run(void) {

	// When computer power off 
	if (this->S == false)
		return;

	// Decode SC
	this->T.reset();
	this->T[SC.to_ulong()] = 1;
	this->SC = this->SC.to_ulong() + 1;

	//Fetch
	if (this->R == false && this->T[0] == true) { 
		this->AR = this->PC; 
	}

	else if (this->R == false && this->T[1] == true) {
		this->IR = this->M[this->AR.to_ulong()];
		this->PC = this->PC.to_ulong() + 1;
	}

	// Decode
	else if (this->R == false && this->T[2] == true) {
		std::bitset<3> temp;
		temp.reset();
		temp[0] = this->IR[12];
		temp[1] = this->IR[13];
		temp[2] = this->IR[14];
		this->D.reset();
		this->D[temp.to_ulong()] = 1;

		for (int i = 0; i < 12; i++)
			this->AR[i] = this->IR[i];
	
		this->I[0] = this->IR[15];
	}

	// Indirect
	else if (this->D[7] == false && this->I == true && this->T[3] == true) {
		this->AR = this->M[this->AR.to_ulong()].to_ulong();
	}

	// Interrupt
	else if (this->T[0] == false && this->T[1] == false && this->T[2] == false &&
		this->IEN == true && (this->FGI.to_ulong() + this->FGO.to_ulong()) == true) {
		this->R = 1;
	}

	else if (this->R == true && this->T[0] == true) {
		this->AR.reset();
		this->TR = this->PC.to_ulong();

	}

	else if (this->R == true && this->T[1] == true) {
		this->M[this->AR.to_ulong()] = this->TR;
		this->PC.reset();

	}

	else if (this->R == true && this->T[2] == true) {
		this->PC = this->PC.to_ulong() + 1;
		this->IEN = 0;
		this->R = 0;
		this->SC.reset();
	}

	/*
		Memory-reference
	*/
	// AND
	else if (this->D[0] == true && this->T[4] == true) {
		this->DR = this->M[this->AR.to_ulong()];
	}

	else if (this->D[0] == true && this->T[5] == true) {
		this->AC = this->AC & this->DR;
		this->SC.reset();
	}

	// ADD
	else if (this->D[1] == true && this->T[4] == true) {
		this->DR = this->M[this->AR.to_ulong()];
	}

	else if (this->D[1] == true && this->T[5] == true) {
		/*
			Full-Adder
			http://stackoverflow.com/questions/13282825/adding-binary-numbers-in-c
		*/
		std::bitset <16> a = this->AC;
		std::bitset <16> b = this->DR;
		std::bitset <16> sum = 0x00;
		std::bitset <1> carry = 0;

		// Full Adder
		for (int i = 0; i < 16; i++) {
			sum[i] = ((a[i] ^ b[i]) ^ carry[0]);
			carry = ((a[i] & b[i]) | (a[i] & carry[0])) | (b[i] & carry[0]);
		}

		this->AC = sum;
		this->E = carry;
		this->SC.reset();
	}

	// LDA
	else if (this->D[2] == true && this->T[4] == true) {
		this->DR = this->M[this->AR.to_ulong()];
	}

	else if (this->D[2] == true && this->T[5] == true) {
		this->AC = this->DR;
		this->SC.reset();
	}

	// STA
	else if (this->D[3] == true && this->T[4] == true) {
		this->M[this->AR.to_ulong()] = this->AC;
		this->SC.reset();
	}

	// BUN
	else if (this->D[4] == true && this->T[4] == true) {
		this->PC = this->AR;
		this->SC.reset();
	}

	// BSA
	else if (this->D[5] == true && this->T[4] == true) {
		this->M[this->AR.to_ulong()] = this->PC.to_ulong();
		this->AR = this->AR.to_ulong() + 1;
	}

	else if (this->D[5] == true && this->T[5] == true) {
		this->PC = this->AR;
		this->SC.reset();
	}

	// ISZ
	else if (this->D[6] == true && this->T[4] == true) {
		this->DR = this->M[this->AR.to_ulong()];
	}

	else if (this->D[6] == true && this->T[5] == true) {
		this->DR = this->DR.to_ulong() + 1;
	}

	else if (this->D[6] == true && this->T[6] == true) {
		this->M[this->AR.to_ulong()] = this->DR;
		if (this->DR.to_ulong() == 0)
			this->PC = this->PC.to_ulong() + 1;
		this->SC.reset();
	}

	/*
		Register-reference
	*/
	else if (this->D[7] == true && this->I == false && this->T[3] == true) {
		
		this->SC.reset();	// Common to all register-reference instructions
		
		// CLA
		if (this->IR[11] == true) { this->AC.reset(); }

		// CLE
		else if (this->IR[10] == true) { this->E = 0; }

		// CMA
		else if (this->IR[9] == true) { this->AC.flip(); }

		// CME
		else if (this->IR[8] == true) { this->E.flip(); }

		// CIR
		else if (this->IR[7] == true) {
			this->AC = this->AC >> 1;
			this->AC[15] = this->E[0];
			this->E[0] = this->AC[0];
		}

		// CIL
		else if (this->IR[6] == true) {
			this->AC = this->AC << 1;
			this->AC[0] = this->E[0];
			this->E[0] = this->AC[15];
		}

		// INC
		else if (this->IR[5] == true) { this->AC = this->AC.to_ulong() + 1; }

		// SPA
		else if (this->IR[4] == true) {
			if (this->AC[15] == false)
				this->PC = this->PC.to_ulong() + 1;
		}

		// SNA
		else if (this->IR[3] == true) {
			if (this->AC[15] == true)
				this->PC = this->PC.to_ulong() + 1;
		}

		// SZA
		else if (this->IR[2] == true) {
			if (this->AC.to_ulong() == 0)
				this->PC = this->PC.to_ulong() + 1;
		}

		// SZE
		else if (this->IR[1] == true) {
			if (this->E[0] == false)
				this->PC = this->PC.to_ulong() + 1;
		}

		// HLT
		else if (this->IR[0] == true) { this->S.reset(); }

		else {}
	}// END - Register-reference


	 /*
		Input-output
	 */
	else if (this->D[7] == true && this->I == true && this->T[3] == true) {

		this->SC.reset();	// Common to all input-output instructions

		// INP
		if (this->IR[11] == true) {
			this->AC = this->INPR.to_ulong();
			this->FGI = 0;
		}

		// OUT
		else if (this->IR[10] == true) {
			for (int i = 0; i < 8; i++)
				this->OUTR[i] = this->AC[i];
			this->FGO = 0;
		}

		// SKI
		else if (this->IR[9] == true) {
			if (this->FGI[0] = true)
				this->PC = this->PC.to_ulong() + 1;
		}

		// SKO
		else if (this->IR[8] == true) {
			if (this->FGO[0] = true)
				this->PC = this->PC.to_ulong() + 1;
		}

		// ION
		else if (this->IR[7] == true) {
			this->IEN = 1;
		}

		// IOF
		else if (this->IR[6] == true) {
			this->IEN = 0;
		}

		else {}
	}// END - Input-output

	else {}
}// END - void run(void)

// Print Status
void ManoComputer::printStatus(void) {
	std::cout << "S    : " << this->S << std::endl;
	std::cout << "SC   : " << this->SC << std::endl;
	std::cout << "IEN  : " << this->IEN << std::endl;
	std::cout << "FGI  : " << this->FGI << std::endl;
	std::cout << "FGO  : " << this->FGO << std::endl;
	std::cout << "R    : " << this->R << std::endl;
	std::cout << "I    : " << this->I << std::endl;
	std::cout << "T    : " << this->T << std::endl;
	std::cout << "D    : " << this->D << std::endl;
	std::cout << "DR   : " << this->DR << std::endl;
	std::cout << "AR   : " << this->AR << std::endl;
	std::cout << "AC   : " << this->AC << std::endl;
	std::cout << "IR   : " << this->IR << std::endl;
	std::cout << "PC   : " << this->PC << std::endl;
	std::cout << "TR   : " << this->TR << std::endl;
	std::cout << "INPR : " << this->INPR << std::endl;
	std::cout << "OUTR : " << this->OUTR << std::endl;
}


 // Print Memory Start to End
void ManoComputer::printM(std::bitset<12> startAddress, std::bitset<12> endAddress) {
	for (int i = startAddress.to_ulong(); i <= endAddress.to_ulong(); i++)
		std::cout << "M [" << i << "] : " << this->M[i] << std::endl;
}