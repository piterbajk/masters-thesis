module macci(input  wire  clk,
             input  wire  clk_en,
             input  wire  reset,
             input  wire  [7:0]  n,
             input  wire  start,
             output reg   done,
             input  wire  [31:0] dataa,
             input  wire  [31:0] datab,
             output reg   [31:0] result);

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
            acc <= 32'h0; 
            done <= 1'b1;
        end
    else if (clk_en & start & (n == 8'd3))
        begin
            acc  <= dataa * datab;
            done <= 1'b1;
        end
    end
end

endmodule