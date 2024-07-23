library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mul1 is
Generic (N: NATURAL:=16);
Port ( 
clk: in std_logic;
	a0, a1, a2, a3 : in SIGNED(N-1 downto 0);
        b0, b1, b2, b3 : in SIGNED(N-1 downto 0);
        y0, y1, y2, y3 : out SIGNED(2*N-1 downto 0)	
);
end mul1;

architecture Flow of mul1 is
begin
process(clk,a0,a1,a2,a3,b0,b1,b2,b3)
begin
if rising_edge(clk) then
y0 <= a0*b0-a1*b1-a2*b2-a3*b3;
y1 <= a0*b1+a1*b0+a2*b3-a3*b2;
y2 <= a0*b2+a2*b0+a3*b1-a1*b3;
y3 <= a0*b3+a3*b0+a1*b2-a2*b1;
end if;
end process;
end Flow;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity hadamard is
	Generic (N: NATURAL:=16);
	Port (
	x0, x1, x2, x3 : in SIGNED(N-1 downto 0);
	y0, y1, y2, y3 : out SIGNED(N-1 downto 0)
);
end hadamard;

architecture Flow of hadamard is
signal t0, t1, t2, t3 : SIGNED(N-1 downto 0);
begin
	t0 <= x0+x2;
	t1 <= x1+x3;
	t2 <= x0-x2;
	t3 <= x1-x3;
	y0 <= t0+t1;
	y2 <= t0-t1;
	y1 <= t2+t3;
	y3 <= t2-t3;
end Flow;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mul is
Generic (N: NATURAL:=16);
Port ( 
clk: in std_logic;
	a0, a1, a2, a3 : in SIGNED(N-1 downto 0);
        b0, b1, b2, b3 : in SIGNED(N-1 downto 0);
        y0, y1, y2, y3 : out SIGNED(2*N-1 downto 0)	
);
end mul;


architecture RTL of mul is
component hadamard is
Generic (N: NATURAL:=16);
	Port (
	x0, x1, x2, x3 : in SIGNED(N-1 downto 0);
	y0, y1, y2, y3 : out SIGNED(N-1 downto 0));
end component;
signal t0, t1, t2, t3: SIGNED(N-1 downto 0);
signal s0, s1, s2, s3 : SIGNED(N-1 downto 0); 
signal s4, s5, s6, s7 : SIGNED(N-1 downto 0);
signal m0, m1, m2, m3 : SIGNED(2*N-1 downto 0);
signal m4 ,m5 ,m6, m7: SIGNED(2*N-1 downto 0);
signal mm4 ,mm5 ,mm6, mm7: SIGNED(2*N-1 downto 0);
signal o0, o1, o2, o3: SIGNED(2*N-1 downto 0); 
begin
u1: hadamard generic map(N=>N) port map (a0, a1, a2, a3, t0, t1, t2, t3);
u2: hadamard generic map(N=>N) port map (b0, b1, b2, b3, s0, s1, s2, s3);
u3: hadamard generic map(N=>2*N) port map (mm4, mm5, mm6, mm7, o0, o1, o2, o3);
s7<=b0(N-2 downto 0)&'0';
s6<=b2(N-2 downto 0)&'0';
s5<=b3(N-2 downto 0)&'0';
s4<=b1(N-2 downto 0)&'0';
m0<=a0*s7;
m1<=a3*s6;
m2<=a1*s5;
m3<=a2*s4;
m4<=t0*s0;
m5<=t2*s2;
m6<=t1*s1;
m7<=t3*s3;
mm4<=(m4(2*N-1)&m4(2*N-1)&m4(2*N-1 downto 2));
mm5<=(m5(2*N-1)&m5(2*N-1)&m5(2*N-1 downto 2));
mm6<=(m6(2*N-1)&m6(2*N-1)&m6(2*N-1 downto 2));
mm7<=(m7(2*N-1)&m7(2*N-1)&m7(2*N-1 downto 2));
process(clk,o0,o1,o2,o3,m0,m1,m2,m3)
begin
if rising_edge(clk) then
y0<=-o0+m0;
y1<=o2-m1;
y2<=o1-m2;
y3<=o3-m3;
end if;
end process;
end RTL;	
