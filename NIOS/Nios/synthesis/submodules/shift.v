// synopsis translate_off
`timescale 1 ps / 1 ps
// synopsis translate_on

module shift (  
    input           aclr,
    input           clk_en,
    input           clock,
    input  [31:0]   dataa,
    input  [31:0]   datab,
    output [31:0]   result
);

    assign result = dataa[15:0] << datab[15:0];

endmodule