library VLSI;
use VLSI.SI.all;
-------------------------------------
entity example is
	port(   terminal input Vin+, Vin- : electrical;
	  terminal output Vout+, Vout- : electrical;
	  terminal clock clk : electrical;
	  terminal ground gnd : electrical );
end entity example;
-------------------------------------
-------------------------------------
architecture SCHEMATIC of example is

 constant const01 : real := 1.097;
 constant const02 : real := 1.055;
 constant const03 : real := 0.1862;
 constant const04 : real := 0.9605;
 constant const05 : real := 0.8386;
 constant const06 : real := 0.741;
 constant const07 : real := 0.09782;
 constant const08 : real := 0.1498;
--square roots of coefficients 
--   1.04738
--   1.02713
--   0.43151
--   0.98005
--   0.91575
--   0.86081
--   0.31276
--   0.3870
--3rd roots of coefficients 
--   1.03134
--   1.01801
--   0.57103
--   0.98666
--   0.94301
--   0.90491
--   0.46076
--   0.53109

 -- Integrator interface:
 component INT is
    port( terminal input x+,x-  : electrical;
          terminal output y+,y-  : electrical;
          terminal clock clkint : electrical );
 end component INT;

 -- Current Mirror interface:
 component CM is
    generic( coeff1 : real );
    port( terminal input x : electrical;
          terminal output y1 : electrical );
 end component CM
 component CM is
    generic( coeff1,coeff2 : real );
    port( terminal input x : electrical;
          terminal output y1,y2 : electrical );
 end component CM
 component CM is
    generic( coeff1,coeff2,coeff3 : real );
    port( terminal input x : electrical;
          terminal output y1,y2,y3 : electrical );
 end component CM
 component CM is
    generic( coeff1,coeff2,coeff3,coeff4 : real );
    port( terminal input x : electrical;
          terminal output y1,y2,y3,y4 : electrical );
 end component CM

 -- terminals:
 terminal s01+,s01-, s1+,s1-, s2+,s2-, s3+,s3- : electrical;
 terminal s4+,s4-, s5+,s5-, s6+,s6-, s7+,s7- : electrical;

-------------------------------------
begin 

  -- input signals
 s01+ <= Vin+; s01- <= Vin-;
  -- output signals
 s7+ <= Vout+; s7- <= Vout-;

 -- Integrators:
 int0 : INT port map( x+=>s1+, x-=>s1-, y+=>s2+, y-=>s2-, clkint=>clk );
 int1 : INT port map( x+=>s3+, x-=>s3-, y+=>s4+, y-=>s4-, clkint=>clk );
 int2 : INT port map( x+=>s5+, x-=>s5-, y+=>s6+, y-=>s6-, clkint=>clk );

 -- Current Mirrors:
 CM00p : CM generic map ( coeff1=>const01 )
	 port map( x=>s01+, y1=>s1- );
 CM00m : CM generic map ( coeff1=>const01 )
	 port map( x=>s01-, y1=>s1+ );

 CM01p : CM generic map ( coeff1=>const01, coeff2=>const04, coeff3=>const08 )
	 port map( x=>s2+, y1=>s1+, y2=>s3+, y3=>s6- );
 CM01m : CM generic map ( coeff1=>const01, coeff2=>const04, coeff3=>const08 )
	 port map( x=>s2-, y1=>s1-, y2=>s3-, y3=>s6+ );

 CM02p : CM generic map ( coeff1=>const02, coeff2=>const06 )
	 port map( x=>s4+, y1=>s1-, y2=>s5+ );
 CM02m : CM generic map ( coeff1=>const02, coeff2=>const06 )
	 port map( x=>s4-, y1=>s1+, y2=>s5- );

 CM03p : CM generic map ( coeff1=>const03, coeff2=>const05, coeff3=>const07, coeff4=>1 )
	 port map( x=>s6+, y1=>s2-, y2=>s3-, y3=>s5+, y4=>s7- );
 CM03m : CM generic map ( coeff1=>const03, coeff2=>const05, coeff3=>const07, coeff4=>1 )
	 port map( x=>s6-, y1=>s2+, y2=>s3+, y3=>s5-, y4=>s7+ );

end architecture SCHEMATIC;

-------------------------------------
-------------------------------------

