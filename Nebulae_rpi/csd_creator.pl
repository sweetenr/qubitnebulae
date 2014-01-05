# Copyright 2014 Qu-Bit Electronix
# Author: Andrew Ikenberry (andrewikenberry@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# See http://creativecommons.org/licenses/MIT/ for more information.
#
# -----------------------------------------------------------------------------

use 5.010;

open FILE, "/var/tmp/fileNames";

$i = 1;
$sr = 22050;
$ksmps = 16;
$number_of_files = 0;
$max_size = 420;
$size = 0;
$max_size_flag = 0;
$volume = .82;

while (<FILE>) {

	chomp $_;

	$files[$i] = "$_";
	$i++;
	$number_of_files++;

}

open (MYCSD, '>/var/tmp/nebulae.csd');

	print MYCSD "Andrew Ikenberry && Jason Lim\n";
	print MYCSD "2013\n";

	print MYCSD "<CsoundSynthesizer>\n";
	print MYCSD "<CsOptions>\n";
	print MYCSD "-odac\n";
	print MYCSD "--sched\n";
	print MYCSD "-d\n";
	print MYCSD "-+rtaudio=alsa\n";
	print MYCSD "-Ma\n";
	print MYCSD "-b512\n";
	print MYCSD "-B1024\n";
	print MYCSD "-m 0\n";
	print MYCSD "</CsOptions>\n";
	print MYCSD "<CsInstruments>\n";

	print MYCSD "sr = $sr\n";
	print MYCSD "ksmps = $ksmps\n";
	print MYCSD "nchnls = 1\n";
	print MYCSD "0dbfs = 1\n";

	print MYCSD "giCosine		ftgen	0, 0, 512, 9, 1, 1, 90\n";
	print MYCSD "giWin		ftgen	0, 0, 512, 20, 6, 1\n";

	
	print MYCSD "pyinit\n";
	print MYCSD "pyruni {{\n";
	print MYCSD "def writetofile(P,a,b,c,d,e,f,g,h,i,j,k,l,m):\n";
	print MYCSD "	if P == 2:\n";
	print MYCSD "		fo = open(\"/mnt/memory/preset1.txt\", \"w\")\n";
	print MYCSD "	elif P == 3:\n";
	print MYCSD "		fo = open(\"/mnt/memory/preset2.txt\", \"w\")\n";
	print MYCSD "	elif P == 4:\n";
	print MYCSD "		fo = open(\"/mnt/memory/preset3.txt\", \"w\")\n";

	print MYCSD "	newline = \"\"\"
\"\"\"\n";
	print MYCSD "	string1 = str(a)\n";
	print MYCSD "	string2 = str(b)\n";
	print MYCSD "	string3 = str(c)\n";
	print MYCSD "	string4 = str(d)\n";
	print MYCSD "	string5 = str(e)\n";
	print MYCSD "	string6 = str(f)\n";
	print MYCSD "	string7 = str(g)\n";
	print MYCSD "	string8 = str(h)\n";
	print MYCSD "	string9 = str(i)\n";
	print MYCSD "	string10 = str(j)\n";
	print MYCSD "	string11 = str(k)\n";
	print MYCSD "	string12 = str(l)\n";
	print MYCSD "	string13 = str(m)\n";
	print MYCSD "	outString = string1+newline+string2+newline+string3+newline+string4+newline+string5+newline+string6+newline+string7+newline+string8+newline+string9+newline+string10+newline+string11+newline+string12+newline+string13\n";
	print MYCSD "	fo.write(outString)\n";
	print MYCSD "	fo.close()\n";
	print MYCSD "	return\n";
	print MYCSD "}}\n";

	print MYCSD "instr 1\n";

	for ($i = 1; $i <= $number_of_files; $i++) {

		print MYCSD "gSfile$i = \"$files[$i]\"\n";
		print MYCSD "gilength$i filelen gSfile$i\n";
		print MYCSD "gilength$i = gilength$i*2\n";
		print MYCSD "gifile$i ftgen $i, 0, 0, 1, gSfile$i, 0, 0, 0\n";
		$j++;
	}

	print MYCSD "ginumberofaudiofiles = $number_of_files\n";

	print MYCSD "turnoff \n";
	print MYCSD "turnon 2\n";
	print MYCSD "endin\n";

	print MYCSD "	instr 2\n";

	print MYCSD "kcurrentaudiofile init 1\n";
	print MYCSD "kflag init 0\n";
	print MYCSD "koldaudiofile init 1\n";
	print MYCSD "kaudiofileflag init 0\n";
	print MYCSD "kfreezeflag init 0\n";
	print MYCSD "knextaudiofilemode init 1\n";
	print MYCSD "krange init 1\n";
	print MYCSD "kflag2 init 1\n";
	print MYCSD "ksetpresetflag init 0\n";
	print MYCSD "koldfreezeflag init 0\n";
	print MYCSD "koldfreeze init 0\n";
	print MYCSD "koldrange init 0\n";
	print MYCSD "krangeflag init 0\n";
	print MYCSD "knewaudiofiles init 0\n"; 
	
	$presets2[1]  = "kpreset2_portamento";
	$presets2[2]  = "kpreset2_mix";
	$presets2[3]  = "kpreset2_speed";
	$presets2[4]  = "kpreset2_pitch";
	$presets2[5]  = "kpreset2_grainrate";
	$presets2[6]  = "kpreset2_grainsize";
	$presets2[7]  = "kpreset2_loopstart";
	$presets2[8]  = "kpreset2_loopstartgrain";
	$presets2[9]  = "kpreset2_loopend";
	$presets2[10] = "kpreset2_loopendgrain";
	$presets2[11] = "kpreset2_freeze";
	$presets2[12] = "kpreset2_currentaudiofile";
	$presets2[13] = "kpreset2_range";

	$presets3[1]  = "kpreset3_portamento";
	$presets3[2]  = "kpreset3_mix";
	$presets3[3]  = "kpreset3_speed";
	$presets3[4]  = "kpreset3_pitch";
	$presets3[5]  = "kpreset3_grainrate";
	$presets3[6]  = "kpreset3_grainsize";
	$presets3[7]  = "kpreset3_loopstart";
	$presets3[8]  = "kpreset3_loopstartgrain";
	$presets3[9]  = "kpreset3_loopend";
	$presets3[10] = "kpreset3_loopendgrain";
	$presets3[11] = "kpreset3_freeze";
	$presets3[12] = "kpreset3_currentaudiofile";
	$presets3[13] = "kpreset3_range";

	$presets4[1]  = "kpreset4_portamento";
	$presets4[2]  = "kpreset4_mix";
	$presets4[3]  = "kpreset4_speed";
	$presets4[4]  = "kpreset4_pitch";
	$presets4[5]  = "kpreset4_grainrate";
	$presets4[6]  = "kpreset4_grainsize";
	$presets4[7]  = "kpreset4_loopstart";
	$presets4[8]  = "kpreset4_loopstartgrain";
	$presets4[9]  = "kpreset4_loopend";
	$presets4[10] = "kpreset4_loopendgrain";
	$presets4[11] = "kpreset4_freeze";
	$presets4[12] = "kpreset4_currentaudiofile";
	$presets4[13] = "kpreset4_range";

	print MYCSD "; Presets\n";

	open FILE3, "/mnt/memory/preset1.txt";

	$i = 1;
	while (<FILE3>){

		chomp $_;
		print MYCSD "$presets2[$i] init $_\n";
		$i++;

	}
	close (FILE3);

	open FILE4, "/mnt/memory/preset2.txt";

	$i = 1;

	while (<FILE4>){

		chomp $_;
		print MYCSD "$presets3[$i] init $_\n";
		$i++;

	}
	close (FILE4);

	open FILE5, "/mnt/memory/preset3.txt";

	$i = 1;
	while (<FILE5>){

		chomp $_;
		print MYCSD "$presets4[$i] init $_\n";
		$i++;

	}

	close (FILE5);

	print MYCSD "; MIDI Controls\n";

	print MYCSD "ksystem system 1, \"umount /dev/sda1 \"\n";

	print MYCSD "ksystem system 1, \"/home/scripts/fileLoadFeedback \"\n";

	print MYCSD "; Portamento\n";
	print MYCSD "kporta     ctrl7 1, 70, 0, .175\n";
	
	print MYCSD "; Mix\n";
	print MYCSD "initc7 1, 8, 1\n";
	print MYCSD "kmix       ctrl7 1, 8, 0, 1\n";
	print MYCSD "kmix portk kmix, .07\n";
	
	print MYCSD "; Speed\n";
	print MYCSD "if (krange <= 1) then\n";
	print MYCSD "	kspeed ctrl14 1, 1, 2, -3, 3\n";
	print MYCSD "	kpitch ctrl14 1, 15, 16, -2, 3\n";
	print MYCSD "	kpitch pow 2, kpitch\n";
	print MYCSD "elseif (krange <= 50) then\n";
	print MYCSD "	kspeed ctrl14 1, 1, 2, -2, 2\n";
	print MYCSD "	kpitch ctrl14 1, 15, 16, 0, 2\n";
	print MYCSD "elseif (krange >= 60) then\n";
	print MYCSD "	kspeed ctrl14 1, 1, 2, -7, 7\n";
	print MYCSD "	kpitch ctrl14 1, 15, 16, 0, 30\n";
	print MYCSD "endif\n";
	print MYCSD "kpitch portk kpitch, kporta\n";

	print MYCSD "; Grain Rate\n";
	print MYCSD "kgrainrate ctrl7 1, 5, 1, 23\n";

	print MYCSD "; Grain Size\n";
	print MYCSD "kgrainsize ctrl7 1, 4, .01, 78\n";

	print MYCSD "; System Utility\n";
	print MYCSD "kutility ctrl7 1, 23, 0, 127\n";
	
	print MYCSD "; Loop Start\n";	
	
	print MYCSD "if (kcurrentaudiofile == 1) then\n";
	print MYCSD "	kloopstart ctrl14 1, 9, 10, 0, (gilength1)-0.01\n";

	print MYCSD "	kloopstartgrain ctrl14 1, 9, 10, 0, 1\n";
	print MYCSD "	kloopstartgrain portk kloopstartgrain, .01\n";

	for ($i = 2; $i <= $number_of_files; $i++) {

		print MYCSD "elseif (kcurrentaudiofile == $i) then\n";
		print MYCSD "	kloopstart ctrl14 1, 9, 10, 0, (gilength$i)-0.01\n";
		print MYCSD "	kloopstartgrain ctrl14 1, 9, 10, 0, 1\n";
		print MYCSD "	kloopstartgrain portk kloopstartgrain, .01\n";
	}
	print MYCSD "endif\n";

	print MYCSD "; Loop End\n";

	print MYCSD "if (kcurrentaudiofile == 1) then\n";
	print MYCSD "	kloopsize ctrl14 1, 11, 12, 0.01, (gilength1)\n";

	print MYCSD "	kloopsizegrain ctrl14 1, 11, 12, 0, 1\n";
	print MYCSD "	kloopsizegrain portk kloopsizegrain, .01\n";

	print MYCSD "	if ((kloopsize+kloopstart) > gilength1) then\n";
	print MYCSD "		kloopsize = gilength1-kloopstart\n";
	print MYCSD "	endif\n";

	print MYCSD "	if (kloopsizegrain+kloopstartgrain > 1) then\n";
	print MYCSD "		kloopsizegrain = 1-kloopstartgrain\n";
	print MYCSD "	endif\n";

	for ($i = 2; $i <= $number_of_files; $i++) {

		print MYCSD "elseif (kcurrentaudiofile == $i) then\n";
		print MYCSD "	kloopsize ctrl14 1, 11, 12, 0.01, (gilength$i)\n";
		print MYCSD "	kloopsizegrain ctrl14 1, 11, 12, 0, 1\n";
		print MYCSD "	kloopsizegrain portk kloopsizegrain, .01\n";
		print MYCSD "	if ((kloopsize+kloopstart) > gilength$i) then\n";
		print MYCSD "		kloopsize = gilength$i-kloopstart\n";
		print MYCSD "		kloopsizegrain = gilength$i-kloopstartgrain\n";
		print MYCSD "	endif\n";
		print MYCSD "	if (kloopsizegrain+kloopstartgrain > 1) then\n";
		print MYCSD "		kloopsizegrain = 1-kloopstartgrain\n";
		print MYCSD "	endif\n";
	}

	print MYCSD "endif\n";

	print MYCSD "; Spectral Freeze\n";
	print MYCSD "if (kutility == 1) then\n";
	print MYCSD "	kfreezeflag = 1\n";
	print MYCSD "elseif (kutility == 2) then\n";
	print MYCSD "	kfreezeflag = 0\n";
	print MYCSD "; Next Audio File\n";
	print MYCSD "elseif (kutility == 3 && kflag == 0) then\n";
	print MYCSD "	kflag = 1\n";
	print MYCSD "	if (knextaudiofilemode == 1) then\n";
	print MYCSD "		kcurrentaudiofile = kcurrentaudiofile+1\n";
	print MYCSD "	elseif (knextaudiofilemode == 2) then\n";
	print MYCSD "		kcurrentaudiofile = kcurrentaudiofile-1\n";
	print MYCSD "	elseif (knextaudiofilemode == 3) then\n";
	print MYCSD "		krandom trandom 1, 1, (ginumberofaudiofiles+1)\n";
	print MYCSD "		krandom = int(krandom)\n";
	print MYCSD "		kcurrentaudiofile = krandom\n";
	print MYCSD "	endif\n";
	print MYCSD "	koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "elseif (kutility == 4) then\n";
	print MYCSD "	kflag = 0\n";
	print MYCSD "elseif (kutility == 5) then\n";
	print MYCSD "	knextaudiofilemode = 1\n";
	print MYCSD "elseif (kutility == 6) then\n";
	print MYCSD "	knextaudiofilemode = 2\n";
	print MYCSD "elseif (kutility == 7) then\n";
	print MYCSD "	knextaudiofilemode = 3\n";
	print MYCSD "elseif (kutility == 8) then\n";
	print MYCSD "	krange = 1\n";
	print MYCSD "elseif (kutility == 9) then\n";
	print MYCSD "	krange = 50\n";
	print MYCSD "elseif (kutility = 10) then\n";
	print MYCSD "	krange = 60\n";

	print MYCSD "; Call Preset\n";

	print MYCSD "elseif (kutility == 12) then\n";
	print MYCSD "	if (krangeflag == 0) then\n";
	print MYCSD "		koldrange = krange\n";
	print MYCSD "		krangeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (koldfreezeflag == 0) then\n";
	print MYCSD "		koldfreeze = kfreezeflag\n";
	print MYCSD "		koldfreezeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (kaudiofileflag == 0) then\n";
	print MYCSD "		koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "		kaudiofileflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	kporta			= kpreset2_portamento\n";
	print MYCSD "	kmix			= kpreset2_mix\n";
	print MYCSD "	kspeed			= kpreset2_speed\n";
	print MYCSD "	kpitch			= kpreset2_pitch\n";
	print MYCSD "	kgrainrate		= kpreset2_grainrate\n";
	print MYCSD "	kgrainsize		= kpreset2_grainsize\n";
	print MYCSD "	kloopstart		= kpreset2_loopstart\n";
	print MYCSD "	kloopstartgrain		= kpreset2_loopstartgrain\n";
	print MYCSD "	kloopsize		= kpreset2_loopend\n";
	print MYCSD "	kloopsizegrain		= kpreset2_loopendgrain\n";
	print MYCSD "	kfreezeflag		= kpreset2_freeze\n";
	print MYCSD "	kcurrentaudiofile	= kpreset2_currentaudiofile\n";
	print MYCSD "	krange			= kpreset2_range\n";

	print MYCSD "elseif (kutility == 13) then\n";
	print MYCSD "	if (krangeflag == 0) then\n";
	print MYCSD "		koldrange = krange\n";
	print MYCSD "		krangeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (koldfreezeflag == 0) then\n";
	print MYCSD "		koldfreeze = kfreezeflag\n";
	print MYCSD "		koldfreezeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (kaudiofileflag == 0) then\n";
	print MYCSD "		koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "		kaudiofileflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	kporta			= kpreset3_portamento\n";
	print MYCSD "	kmix			= kpreset3_mix\n";
	print MYCSD "	kspeed			= kpreset3_speed\n";
	print MYCSD "	kpitch			= kpreset3_pitch\n";
	print MYCSD "	kgrainrate		= kpreset3_grainrate\n";
	print MYCSD "	kgrainsize		= kpreset3_grainsize\n";
	print MYCSD "	kloopstart		= kpreset3_loopstart\n";
	print MYCSD "	kloopstartgrain		= kpreset3_loopstartgrain\n";
	print MYCSD "	kloopsize		= kpreset3_loopend\n";
	print MYCSD "	kloopsizegrain		= kpreset3_loopendgrain\n";
	print MYCSD "	kfreezeflag		= kpreset3_freeze\n";
	print MYCSD "	kcurrentaudiofile	= kpreset3_currentaudiofile\n";
	print MYCSD "	krange			= kpreset3_range\n";

	print MYCSD "elseif (kutility == 14) then\n";
	print MYCSD "	if (krangeflag == 0) then\n";
	print MYCSD "		koldrange = krange\n";
	print MYCSD "		krangeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (koldfreezeflag == 0) then\n";
	print MYCSD "		koldfreeze = kfreezeflag\n";
	print MYCSD "		koldfreezeflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	if (kaudiofileflag == 0) then\n";
	print MYCSD "		koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "		kaudiofileflag = 1\n";
	print MYCSD "	endif\n";
	print MYCSD "	kporta			= kpreset4_portamento\n";
	print MYCSD "	kmix			= kpreset4_mix\n";
	print MYCSD "	kspeed			= kpreset4_speed\n";
	print MYCSD "	kpitch			= kpreset4_pitch\n";
	print MYCSD "	kgrainrate		= kpreset4_grainrate\n";
	print MYCSD "	kgrainsize		= kpreset4_grainsize\n";
	print MYCSD "	kloopstart		= kpreset4_loopstart\n";
	print MYCSD "	kloopstartgrain		= kpreset4_loopstartgrain\n";
	print MYCSD "	kloopsize		= kpreset4_loopend\n";
	print MYCSD "	kloopsizegrain		= kpreset4_loopendgrain\n";
	print MYCSD "	kfreezeflag		= kpreset4_freeze\n";
	print MYCSD "	kcurrentaudiofile	= kpreset4_currentaudiofile\n";
	print MYCSD "	krange			= kpreset4_range\n";

	print MYCSD "elseif (kutility == 16) then\n";
	print MYCSD "	kcurrentaudiofile = koldaudiofile\n";
	print MYCSD "	kaudiofileflag = 0\n";
	print MYCSD "	kfreezeflag = koldfreeze\n";
	print MYCSD "	koldfreezeflag = 0\n";
	print MYCSD "	krange = koldrange\n";
	print MYCSD "	krangeflag = 0\n";

	print MYCSD "; Set Preset\n";

	print MYCSD "elseif (kutility == 18 && ksetpresetflag == 0) then\n";
	print MYCSD "	if (ksetpresetflag == 0) then\n";
	print MYCSD "		ksetpresetflag = 1\n";
	print MYCSD "	endif\n";

	print MYCSD "	ksystem system 1, \"mount /dev/sda1 /mnt/memory\"\n";

	print MYCSD "	kpreset2_portamento 	= kporta\n";
	print MYCSD "	kpreset2_mix		= kmix\n";
	print MYCSD "	kpreset2_speed		= kspeed\n";
	print MYCSD "	kpreset2_pitch		= kpitch\n";
	print MYCSD "	kpreset2_grainrate 	= kgrainrate\n";
	print MYCSD "	kpreset2_grainsize 	= kgrainsize\n";
	print MYCSD "	kpreset2_loopstart 	= kloopstart\n";
	print MYCSD "	kpreset2_loopstartgrain = kloopstartgrain\n";
	print MYCSD "	kpreset2_loopend 	= kloopsize\n";
	print MYCSD "	kpreset2_loopendgrain 	= kloopsizegrain\n";
	print MYCSD "	kpreset2_freeze		= kfreezeflag\n";
	print MYCSD "	kpreset2_currentaudiofile = kcurrentaudiofile\n";
	print MYCSD "	kpreset2_range		= krange\n";
	
	print MYCSD "	pycall \"writetofile\", 2, kpreset2_portamento, kpreset2_mix, kpreset2_speed, kpreset2_pitch, kpreset2_grainrate, kpreset2_grainsize, kpreset2_loopstart, kpreset2_loopstartgrain, kpreset2_loopend, kpreset2_loopendgrain, kpreset2_freeze, kpreset2_currentaudiofile, kpreset2_range\n";		

	print MYCSD "	ksystem system 1, \"umount /dev/sda1\"\n";

	print MYCSD "elseif (kutility == 19 && ksetpresetflag == 0) then\n";
	print MYCSD "	if (ksetpresetflag == 0) then\n";
	print MYCSD "		ksetpresetflag = 1\n";
	print MYCSD "	endif\n";

	print MYCSD "	ksystem system 1, \"mount /dev/sda1 /mnt/memory\"\n";

	print MYCSD "	kpreset3_portamento 	= kporta\n";
	print MYCSD "	kpreset3_mix		= kmix\n";
	print MYCSD "	kpreset3_speed		= kspeed\n";
	print MYCSD "	kpreset3_pitch		= kpitch\n";
	print MYCSD "	kpreset3_grainrate 	= kgrainrate\n";
	print MYCSD "	kpreset3_grainsize 	= kgrainsize\n";
	print MYCSD "	kpreset3_loopstart 	= kloopstart\n";
	print MYCSD "	kpreset3_loopstartgrain = kloopstartgrain\n";
	print MYCSD "	kpreset3_loopend 	= kloopsize\n";
	print MYCSD "	kpreset3_loopendgrain 	= kloopsizegrain\n";
	print MYCSD "	kpreset3_freeze		= kfreezeflag\n";
	print MYCSD "	kpreset3_currentaudiofile = kcurrentaudiofile\n";
	print MYCSD "	kpreset3_range		= krange\n";
	
	print MYCSD "	pycall \"writetofile\", 3, kpreset3_portamento, kpreset3_mix, kpreset3_speed, kpreset3_pitch, kpreset3_grainrate, kpreset3_grainsize, kpreset3_loopstart, kpreset3_loopstartgrain, kpreset3_loopend, kpreset3_loopendgrain, kpreset3_freeze, kpreset3_currentaudiofile, kpreset3_range\n";		

	print MYCSD "	ksystem system 1, \"umount /dev/sda1\"\n";

	print MYCSD "elseif (kutility == 20 && ksetpresetflag == 0) then\n";
	print MYCSD "	if (ksetpresetflag == 0) then\n";
	print MYCSD "		ksetpresetflag = 1\n";
	print MYCSD "	endif\n";

	print MYCSD "	ksystem system 1, \"mount /dev/sda1 /mnt/memory\"\n";

	print MYCSD "	kpreset4_portamento 	= kporta\n";
	print MYCSD "	kpreset4_mix		= kmix\n";
	print MYCSD "	kpreset4_speed		= kspeed\n";
	print MYCSD "	kpreset4_pitch		= kpitch\n";
	print MYCSD "	kpreset4_grainrate 	= kgrainrate\n";
	print MYCSD "	kpreset4_grainsize 	= kgrainsize\n";
	print MYCSD "	kpreset4_loopstart 	= kloopstart\n";
	print MYCSD "	kpreset4_loopstartgrain = kloopstartgrain\n";
	print MYCSD "	kpreset4_loopend 	= kloopsize\n";
	print MYCSD "	kpreset4_loopendgrain 	= kloopsizegrain\n";
	print MYCSD "	kpreset4_freeze		= kfreezeflag\n";
	print MYCSD "	kpreset4_currentaudiofile = kcurrentaudiofile\n";
	print MYCSD "	kpreset4_range		= krange\n";
	
	print MYCSD "	pycall \"writetofile\", 4, kpreset4_portamento, kpreset4_mix, kpreset4_speed, kpreset4_pitch, kpreset4_grainrate, kpreset4_grainsize, kpreset4_loopstart, kpreset4_loopstartgrain, kpreset4_loopend, kpreset4_loopendgrain, kpreset4_freeze, kpreset4_currentaudiofile, kpreset4_range\n";		

	print MYCSD "	ksystem system 1, \"umount /dev/sda1\"\n";

	print MYCSD "elseif (kutility == 22) then\n";
	print MYCSD "	ksetpresetflag = 0\n";
	print MYCSD "elseif (kutility == 23) then\n";
	print MYCSD "	knewaudiofiles = 1\n";
	print MYCSD "elseif (kutility == 24) then\n";
	print MYCSD "	ksystem system 1, \"echo 1 > /var/tmp/start_flag\"\n";
	print MYCSD "	event \"e\", 0, 0, 0\n";
	print MYCSD "endif\n";

	print MYCSD "; Load New Files\n";		
	print MYCSD "if (knewaudiofiles == 1) then\n";	
	print MYCSD "	ksystem system 1, \"echo 3 > /var/tmp/start_flag\"\n";
	print MYCSD "	event \"e\", 0, 0, 0\n";
	print MYCSD "endif\n";	

	print MYCSD "if (kcurrentaudiofile > ginumberofaudiofiles) then\n";
	print MYCSD "	kcurrentaudiofile = 1\n";
	print MYCSD "	koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "elseif (kcurrentaudiofile < 1) then\n";
	print MYCSD "	kcurrentaudiofile = ginumberofaudiofiles\n";
	print MYCSD "	koldaudiofile = kcurrentaudiofile\n";
	print MYCSD "endif\n";

	print MYCSD "; Freeze Current Audio Stream\n";
	print MYCSD "if (kfreezeflag == 1) then\n";
	print MYCSD "	kspeed = 0\n";
	print MYCSD "endif\n";
	
	print MYCSD "aphs        phasor (1/kloopsize)*kspeed\n";
	print MYCSD "atimpt      = kloopstart + (kloopsize*aphs) \n";
	print MYCSD "kgrainrange = kloopsizegrain\n";
	
	print MYCSD "	asig  mincer atimpt, $volume, kpitch, kcurrentaudiofile, 1, 1024, 4\n";
				
	print MYCSD "; Partikkel Initialization\n";
	print MYCSD "azero		= 0\n";
	print MYCSD "izero		= 0\n";
	print MYCSD "ineg_one		= -1\n";
	print MYCSD "ione		= 1\n";
	print MYCSD "ihalf		= 0.5\n";
	print MYCSD "iamp		= .5\n";
	print MYCSD "kcentrand		rand izero\n";

	print MYCSD "if (kcurrentaudiofile == 1)then\n";
	print MYCSD "	korig	= 1 / gilength1\n";

	for ($i = 2; $i <= $number_of_files; $i++) {

		print MYCSD "elseif (kcurrentaudiofile == $i) then\n";
		print MYCSD "	korig	= 1 / gilength$i\n";
	}

	print MYCSD "endif\n";

	print MYCSD "kwavfreq		= ((korig * cent(kcentrand))*kpitch)\n";
	print MYCSD "aphs = (aphs*kgrainrange)+kloopstartgrain\n";

	print MYCSD "; Partikkel\n";
	print MYCSD "agrain		partikkel kgrainrate, ione, ineg_one, azero, ione, giWin, \\\n";
	print MYCSD "ineg_one, ineg_one, ihalf, ihalf, kgrainsize, iamp, ineg_one, \\\n";
	print MYCSD "kwavfreq, izero, ineg_one, ineg_one, azero, \\\n";
	print MYCSD "ineg_one, ineg_one, giCosine, kgrainrate, ione, \\\n";
	print MYCSD "ione, ineg_one, izero, kcurrentaudiofile, kcurrentaudiofile, kcurrentaudiofile, kcurrentaudiofile, \\\n";
	print MYCSD  "ineg_one, aphs, aphs, aphs, aphs, \\\n";
	print MYCSD "ione, ione, ione, ione, 25\n";

	print MYCSD "out (agrain*kmix)+(asig*(1-kmix))\n";
	
	print MYCSD "	endin\n";
	
	print MYCSD "</CsInstruments>\n";
	print MYCSD "<CsScore>\n";
	print MYCSD "f0 \$INF\n";
	print MYCSD "i1 0 10\n";

	print MYCSD "</CsScore>\n";
	print MYCSD "</CsoundSynthesizer>\n";

close (MYCSD);

system("perl /home/scripts/one_shot.pl");	

