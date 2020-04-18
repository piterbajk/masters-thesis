module ci_shift
    # ( parameter LATENCY=0 )
    (
        input           reset,
        input           clk,
        input           clk_en,
        input  [31:0]   dataa,
        input  [31:0]   datab, 
        input           start,
        output [31:0]   result, 
        output          done
    );

    wire [31:0] result_;

    shift inst_shift(
            .aclr   (reset),
            .clk_en (clk_en),
            .clock  (clk),
            .dataa  (dataa),
            .datab  (datab),
            .result (result_)
    );

    reg [4:0] state_sync;

    always @(posedge clk) begin
        if  (reset) begin
            state_sync <= 0;
        end else if (start & clk_en) begin
            state_sync <= LATENCY;
        end else if (clk_en) begin
            state_sync <= state_sync - 1;
        end else begin
            state_sync <= 0;
        end
    end

    assign done = (state_sync == 1) & clk_en;
    assign result = result_;

endmodule