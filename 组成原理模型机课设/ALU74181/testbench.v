`timescale 1ns/1ns  
module tb_alu181;
  reg [7:0] A;
  reg [7:0] B;
  reg C0;
  reg M;  
  reg [3:0] S;
  wire C4, C8;
  wire [7:0] F;
  wire AequB0, AequB1;
  wire P0, P1;
  wire G0, G1;
  ALU181 uut0(.A(A[3:0]), .B(B[3:0]), .C0(C0), .M(M), .S(S), .C4(C4), .F(F[3:0]), .AequB(AequB0), .P(P0), .G(G0));
  ALU181 uut1(.A(A[7:4]), .B(B[7:4]), .C0(C4), .M(M), .S(S), .C4(C8), .F(F[7:4]), .AequB(AequB1), .P(P1), .G(G1)); 
  
  
//  ALU181A uut0(.A(A[3:0]), .B(B[3:0]), .C0(C0), .M(M), .S(S), .CN(C4), .F(F[3:0]), .AequB(AequB0), .P(P0), .G(G0));
//  ALU181A uut1(.A(A[7:4]), .B(B[7:4]), .C0(C4), .M(M), .S(S), .CN(C8), .F(F[7:4]), .AequB(AequB1), .P(P1), .G(G1));  
//TopLevel74181b U1(S, A[3:0], B[3:0], M, C0, F[3:0], G0, P0, C4, AequB0);
// TopLevel74181b U2(S, A[7:4], B[7:4], M, C4, F[7:4], G1, P1, C8, AequB1);
  initial
    begin
      A = 8'h65;
      B = 8'hA7;
      C0 = 1;
      S = 4'b0000;
      M = 0;    
    end
    
always #10  C0 = ~C0;
always #20  M = ~M;
always #40  S = S+1;
  
initial #680 $finish;   

endmodule

