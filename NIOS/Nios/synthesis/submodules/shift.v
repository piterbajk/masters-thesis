// synopsis translate_off
`timescale 1 ps / 1 ps
// synopsis translate_on

module shift (  
    input           aclr,
    input           clk_en,
    input           clock,
    input  [7:0]    n,
    input  [31:0]   dataa,
    input  [31:0]   datab,
    output [31:0]   result
);

  reg signed [31:0] acc;

  always @(posedge clk or posedge reset)
  begin
    if (reset) 
    begin
      acc <= 32'h0; 
      done <= 1'b0;
    end
    else begin
    done <= 1'b0;
    if (clk_en & start & (n == 8'd1))
        begin
          acc  <= acc + (dataa * datab);
          done <= 1'b1;
          end
      else if (clk_en & start & (n == 8'd2))
          begin
          result <= acc[31:0];
          done <= 1'b1;       
          end
      end
    end

endmodule


    // reg c00[3:0];
    // reg c10[3:0];
    // reg c01[3:0];
    // reg c11[3:0];

    // c00 = dataa[15:12] * datab[15:12] + dataa[11:8] * datab[7:4];
    // c10 = dataa[15:12] * datab[11:8]  + dataa[11:8] * datab[3:0];
    // c01 = dataa[7:4]   * datab[15:12] + dataa[3:0]  * datab[7:4];
    // c11 = dataa[7:4]   * datab[11:8]  + dataa[3:0]  * datab[3:0];

    // assign result[15:0] = { c00[3:0], c10[3:0], c01[3:0], c11[3:0] };
    // assign result = {dataa[15:8] * datab[15:8], dataa[7:0] * datab[7:0]};