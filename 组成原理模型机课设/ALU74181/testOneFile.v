
`timescale 1ns/1ns  
module testOne181;
  reg [3:0] A;
  reg [3:0] B;
  reg C0;
  reg M;  
  reg [3:0] S;
  wire C4;
  wire [3:0] F;
  wire AequB0;
  wire P0;
  wire G0;
  ALU181 uut0(.A(A[3:0]), .B(B[3:0]), .C0(C0), .M(M), .S(S), .C4(C4), .F(F[3:0]), .AequB(AequB0), .P(P0), .G(G0));
  initial
    begin
      A = 4'h5;
      B = 4'h7;
      C0 = 1;
      S = 4'b0000;
      M = 0;    
    end
    
always #10  C0 = ~C0;
always #20  M = ~M;
always #40  S = S+1;
  
initial #680 $finish;   

endmodule

