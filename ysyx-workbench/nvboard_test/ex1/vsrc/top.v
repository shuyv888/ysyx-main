module ex1(
  input   [1:0]X0,X1,X2,X3,
  input   y1,
  input   y2,
  output  [1:0]F
  );

  assign  F = ({2{~y2&~y1}}&X0) | ({2{~y2&y1}}&X1) | ({2{y2&~y1}}&X2) | ({2{y2&y1}}&X3);

endmodule
