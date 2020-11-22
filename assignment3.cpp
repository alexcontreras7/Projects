// Code your design here
//gets everything together by instantiating processor and memory

module top (input clk, reset,output [31:0] writedata, dataadr,output memwrite);

wire [31:0] pc, instr, readdata;

// instantiate processor and memories
mips mips (clk, reset, pc, instr, memwrite, dataadr,
writedata, readdata);

imem imem (pc[7:2], instr); //6-bit address
dmem dmem (clk, memwrite, dataadr, writedata,readdata);
endmodule

//appends two zeros from the right of LSB of 26-bit immediate //field
module sl2 (input [31:0] a, output [31:0] y);
// shift left by 2; does not shift , but appends
assign y = {a[25:0], 2'b00};
endmodule

//copies the 16th bit of the constant field to upper 16 bits //from 17th  to 31st bit
module signext (input [15:0] a,
output [31:0] y);
assign y = {{16{a[15]}}, a};
endmodule

module regfile (input clk, input we3,
input [4:0] ra1, ra2, wa3,
input [31:0] wd3,
output [31:0] rd1, rd2);
reg [31:0] rf[31:0];

// three ported register file
// read two ports combinationally
// write third port on rising edge of clock
// register 0 hardwired to 0

always @ (posedge clk)
if (we3) rf[wa3] <= wd3;
assign rd1 = (ra1 != 0) ? rf[ra1] : 0;
assign rd2 = (ra2 != 0) ? rf[ra2] : 0;
endmodule

//Defines 2-to-1 MUX with the parameter as the width of data //inputs. Please note, it is limited to 8 as both addresses for //instruction and data memory are limited to 6, and data in the //test code are in the range 0-255.  For the real design the //width is 8 

module mux2 # (parameter WIDTH = 8)
(input [WIDTH-1:0] d0, d1, input s,
output [WIDTH-1:0] y);
assign y = s ? d1 : d0;
endmodule

//instatiates modules in MIPS Processor
 
module mips (input clk, reset,
output [31:0] pc,
input [31:0] instr,
output memwrite,
output [31:0] aluout, writedata,
input [31:0] readdata);
wire memtoreg, branch, alusrc, regdst, regwrite, jump;
wire [2:0] alucontrol;
wire ori;
controller c(instr[31:26], instr[5:0], zero,memtoreg, memwrite, pcsrc, alusrc, regdst, regwrite, jump, alucontrol, ori);
datapath dp(clk, reset, memtoreg, pcsrc,
alusrc, regdst, regwrite, jump,
alucontrol,zero, pc, instr,
aluout, writedata, readdata, ori);

endmodule

//takes opcode and produces control signals except branch (this //is done by controller module as an outside logic)

module maindec (input [5:0] op, output memtoreg, memwrite, output branch, alusrc,
                output regdst, regwrite, output jump, output [1:0] aluop, output ori);
  reg [9:0] controls;
assign {regwrite, regdst, alusrc, branch, memwrite, memtoreg, jump, aluop, ori}  = controls;

// checks the opcode and produces 9 control signals as in the //control word table

always @ (* )
 case(op)
6'b000000 :  controls <= 10'b1100000100; 		//Rtyp
6'b100011 :  controls <= 10'b1010010000; 		//LW
6'b101011 :  controls <= 10'b0010100000; 		//SW
6'b000100 :  controls <= 10'b0001000010; 		//BEQ
6'b001000 :  controls <= 10'b1010000000; 		//ADDI
6'b000010 :  controls <= 10'b0000001000; 		//J
6'b001101 :  controls <= 10'b1010000111;		//ORI
default:  controls <= 10'bXXXXXXXXXX; 		// any
endcase
endmodule

//64 word memory is defined here
// .dat. file has a hexadecimal code of instructions

module imem (input [5:0] a, output [31:0] rd);
reg [31:0] RAM[63:0]; // limited memory
initial
begin
$readmemh ("memfile.dat",RAM);//lines of test code in hex
end
assign rd = RAM[a]; // word aligned
endmodule

// D flip-flop is designed in this module
module flopr # (parameter WIDTH = 8)
(input clk, reset,
input [WIDTH-1:0] d,
output reg [WIDTH-1:0] q);
always @ (posedge clk, posedge reset)
if (reset) q <= 0;
else q <= d;
endmodule

module dmem (input clk, we,
input [31:0] a, wd,
output [31:0] rd);
reg [31:0] RAM[63:0];
assign rd = RAM[a[31:2]]; // word aligned
always @ (posedge clk)
if (we)
RAM[a[31:2]] <= wd;
endmodule

//got all control signals
module datapath (input clk, reset,
input memtoreg, pcsrc,
input alusrc, regdst,
input regwrite, jump,
input [2:0] alucontrol,
output zero,
output [31:0] pc,
input [31:0] instr,
output [31:0] aluout, writedata,
input [31:0] readdata,
input ori);
//defines all internal wires
wire [4:0] writereg;
wire [31:0] pcnext, pcnextbr, pcplus4, pcbranch;
wire [31:0] signimm, signimmsh;
wire [31:0] srca, srcb;
wire [31:0] result;
wire [31:0] imm;
wire [31:0] res;
  
zeroExCir ext(instr[15:0], imm);
mux2 #(32) extmux(signimm, imm, ori, res);
  
// next PC logic. Instantiates PC and adders
flopr #(32) pcreg(clk, reset, pcnext, pc);
adder pcadd1 (pc, 32'b100, pcplus4);
sl2 immsh(signimm, signimmsh); 

adder pcadd2(pcplus4, signimmsh, pcbranch);
mux2 #(32) pcbrmux(pcplus4, pcbranch, pcsrc, pcnextbr);
mux2 #(32) pcmux(pcnextbr, {pcplus4[31:28], instr[25:0], 2'b00},jump, pcnext);

// register file logic; instatiates RF
regfile rf(clk, regwrite, instr[25:21],
           instr[20:16], writereg, result, srca, writedata);

//instatiates the number of multiplexers
mux2 #(5) wrmux(instr[20:16], instr[15:11],regdst, writereg);
mux2 #(32) resmux(aluout, readdata, memtoreg, result);
signext se(instr[15:0], signimm);

// ALU logic: defines inputs and instatiates Alu
  mux2 #(32) srcbmux(writedata, res, alusrc, srcb);
alu alu(srca, srcb, alucontrol, aluout, zero);
endmodule

// zero extend circuit 
module zeroExCir(input [15:0] imm, 
output [31:0] vari);
assign vari = {16'b0000000000000000, imm};
endmodule

//instantiates both maind ecoder and ALU decoder
module controller (input [5:0] op, funct,
input zero,
output memtoreg, memwrite,
output pcsrc, alusrc,
output regdst, regwrite,
output jump,
output [2:0] alucontrol,
output ori);
wire [1:0] aluop;
wire branch;
maindec md(op, memtoreg, memwrite, branch,
alusrc, regdst, regwrite, jump,
aluop, ori);
aludec ad (funct, aluop, alucontrol);
assign pcsrc = branch & zero; //does it here because the logic is outside of main decoder and ALU decoder
endmodule

module aludec (input [5:0] funct,
input [1:0] aluop,
output reg [2:0] alucontrol);
always @ (*)

case (aluop)
2'b00: alucontrol <= 3'b010; // add
2'b01: alucontrol <= 3'b110; // sub
2'b10: case(funct) // RTYPE
6'b100000: alucontrol <= 3'b010; // ADD
6'b100010: alucontrol <= 3'b110; // SUB
6'b100100: alucontrol <= 3'b000; // AND
6'b100101: alucontrol <= 3'b001; // OR
6'b101010: alucontrol <= 3'b111; // SLT
endcase
2'b11: alucontrol <= 3'b001;  // or
default: alucontrol <= 3'bxxx; // ???
endcase
endmodule


module alu (a,b,sel, out, zero);
    input [31:0] a,b;
    input [2:0] sel; 
    output reg [31:0] out;
 output reg zero;
  
  initial
  begin
  out = 0;
  zero =1'b0;
  end
    always @ (*) 
    begin 
        case(sel) 
            3'b000: 
	begin
		out=a & b; 
		if (out == 0)
		 zero = 1;  
		else
		zero = 0;
          end                   
            3'b001:
	begin
		out= a | b; 
		if (out == 0)
		 zero = 1;  
		else
		zero = 0; 
end		
            3'b110: 
	begin
		out=a-b;  
		if (out == 0)
		 zero = 1;  
		else
		zero = 0;
          end              
            3'b010: 
	begin
		out=a+b;  
		if (out == 0)
		 zero = 1;  
		else
		zero = 0;
          end         
            3'b111: 
           begin
		 if ( a < b)
		 out = 1;  
		else
		out=0;
          end 
        endcase
    end
endmodule

module adder (input [31:0] a, b, output [31:0] y);
assign y = a + b;
endmodule







// Code your testbench here
// or browse Examples
module testbench();
reg clk;
reg reset;
wire [31:0] writedata, dataadr;
wire memwrite;

// instantiates the  device to be tested (device under test-DUT)
top dut (clk, reset, writedata, dataadr, memwrite);

// initialize test
initial
begin
reset <= 1; # 22; reset <= 0;
end

// generate clock to sequence tests

always
begin
clk <= 1;
 # 5; 
 clk <= 0;
 # 5; // clock duration
end

// check the contents of memory location 12. It must be 5

always @ (negedge clk)
begin
if (memwrite) begin
if (dataadr === 12 & writedata === 5) begin
  $display ("Simulation succeeded \n dataadr read in: %d \n writedata read in: %d ", dataadr, writedata);
  $write(" Expected dataadr: 12 \n Expected writedata: 5 \n");
//$stop;
end 
else if (dataadr === 20 & writedata === 5) begin
  $display ("Simulation succeeded \n dataadr read in: %d \n writedata read in: %d ", dataadr, writedata); 
$write(" Expected dataadr: 20 \n Expected writedata: 5 \n");
$stop; 
end
else if (dataadr !== 12) begin
  $display ("Simulation failed \n dataadr: %d \n writedata: %d ", dataadr, writedata);
$stop;
end 
end
end
endmodule







20070006
20050004
34e70005
10a70009
00e5202a
10800001
20050000
00a7202a
00853820
aca70008
8ca20008
0810000d
20020001
aca20010

