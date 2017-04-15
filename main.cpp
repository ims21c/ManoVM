/*
	main.cpp

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
#include <iostream>
#include <string>
#include "ManoComputer.h"

int main() {

	ManoComputer computer;
	std::string cmd;

	std::cout << "Morris Mano Computer" << std::endl << std::endl << std::endl;
	std::cout << "Cmmand >>" << std::endl;
	std::cout << "f : full-line code run" << std::endl;
	std::cout << "o : one-line run" << std::endl;
	std::cout << "s : print status (register & flip-flops)" << std::endl;
	std::cout << "m : print memory" << std::endl;
	std::cout << "e : exit" << std::endl;
	std::cout << std::endl << std::endl;


	/*
		p.146 table 6-5 two numbers add example

		ORG 0
		LDA A
		ADD B
		STA C
		HLT
	A,	DEC 83
	B,	DEC -23
	C,	DEC 0
		END
	*/

	computer.setM(0x0, 0x2004);
	computer.setM(0x1, 0x1005);
	computer.setM(0x2, 0x3006);
	computer.setM(0x3, 0x7001);
	computer.setM(0x4, 0x53);
	computer.setM(0x5, 0xffe9);
	computer.setM(0x6, 0x0);


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
	
	/*
	computer.setM(0x100, 0x7400);
	computer.setM(0x101, 0x2113);
	computer.setM(0x102, 0x7080);
	computer.setM(0x103, 0x3113);
	computer.setM(0x104, 0x7002);
	computer.setM(0x105, 0x4107);
	computer.setM(0x106, 0x410b);
	computer.setM(0x107, 0x2112);
	computer.setM(0x108, 0x1114);
	computer.setM(0x109, 0x3114);
	computer.setM(0x10a, 0x7400);
	computer.setM(0x10b, 0x2112);
	computer.setM(0x10c, 0x7040);
	computer.setM(0x10d, 0x3112);
	computer.setM(0x10e, 0x6111);
	computer.setM(0x10f, 0x4100);
	computer.setM(0x110, 0x7001);
	computer.setM(0x111, 0xfff8);
	computer.setM(0x112, 0xf);
	computer.setM(0x113, 0xb);
	computer.setM(0x114, 0x0);
	*/
	

	while (true) {

		std::cout << ">> ";
		std::cin >> cmd;

		if (cmd == "f") {
			while (computer.getS() == true)
				computer.run();
		}

		else if (cmd == "o") {
			computer.run();
		}

		else if (cmd == "s") {
			computer.printStatus();
		}

		else if (cmd == "m") {
			int start;
			int end;
			std::cout << "Start Address : ";
			std::cin >> start;
			std::cout << "End   Address : ";
			std::cin >> end;
			computer.printM(start, end);
		}

		else if (cmd == "e") {
			break;
		}

		else {}


	}// END - while (true)

	return 0;
}