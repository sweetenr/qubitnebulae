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

$number_of_files = 0;
$inst_num = 2;
$max_files_allowed = 8;
$i = 1;
$sr = 22050;
$pitch_msb = 9;
$pitch_lsb = 10;

while (<FILE>) {

	chomp $_;
	$files[$i] = $_;
	$number_of_files++;
	$i++;

}

close (FILE);

open (MYCSD, '>/var/tmp/nebulae_oneshot.csd');

	if ($number_of_files < $max_files_allowed) {
		
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
		print MYCSD "ksmps = 8\n";
		print MYCSD "nchnls = 1\n";
		print MYCSD "0dbfs = 1\n";
	
		for ($i = 1; $i <= $number_of_files; $i++) {
		
			print MYCSD "gkpitch$i init 0\n";
		
		}

		print MYCSD "instr 1\n";

		print MYCSD "ksystem system 1, \"/home/scripts/fileLoadFeedback \"\n";

		print MYCSD "killall ctrl7 1, 28, 0, 127\n";

		print MYCSD "	kutility ctrl7 1, 23, 0, 127\n";

		print MYCSD "	if (kutility == 28) then\n"; # load new files
		print MYCSD "		ksystem system 1, \"umount -l /dev/sda1 \"\n";
		print MYCSD "		ksystem system 1, \"echo 4 > /var/tmp/start_flag\"\n";
		print MYCSD "		event \"e\", 0, 0, 0\n";
		print MYCSD "	elseif (kutility == 26) then\n"; # go back to looping mode
		print MYCSD "		ksystem system 1, \"echo 0 > /var/tmp/start_flag\"\n";
		print MYCSD "		event \"e\", 0, 0, 0\n";
		print MYCSD "	endif\n";

		print MYCSD "	if (killall == 127) then\n";

		for ($i = 2; $i <= $number_of_files+1; $i++) {
		
			print MYCSD "	turnoff2 $i, 0, 0\n";	
		
		}

		print MYCSD "	endif\n";

		for ($i = 1; $i <= $number_of_files; $i++) {

			print MYCSD "	initc7 1, $i, 0\n";
			print MYCSD "	ktrigger$i ctrl7 1, $i, 0, 127\n";
			print MYCSD "	kflag$i init 0\n";

			print MYCSD "	gkpitch$i ctrl14 1, $pitch_msb, $pitch_lsb, -3, 1\n";
		
			$pitch_msb += 2;
			$pitch_lsb += 2;

			if ($pitch_msb == 23) {
		
				$pitch_msb++;
				$pitch_lsb++;
			
			}

		}
		
		for ($i = 1; $i <= $number_of_files; $i++) {

			print MYCSD "	if (kflag$i == 0) then\n";
			print MYCSD "		if (ktrigger$i == 127) then\n";
			print MYCSD "				event \"i\", $inst_num, 0, 99999\n";
			print MYCSD "				turnoff2 $inst_num, 1, 0\n";
			print MYCSD "				kflag$i = 1\n";
			print MYCSD "		elseif (ktrigger$i == 63) then\n";
			print MYCSD "			turnoff2 $inst_num, 0, 0\n";
			print MYCSD "		endif\n";
			print MYCSD "	endif\n";

			print MYCSD "	if (ktrigger$i == 0) then\n";
			print MYCSD "		kflag$i = 0\n";
			print MYCSD "	endif\n";

			$inst_num++;

		}

			print MYCSD "endin\n";

			$inst_num = 2;

		for ($i =1; $i <= $number_of_files; $i++) {
	
		
			print MYCSD "instr $inst_num\n";

			if ($inst_num == 3) {
			
				print MYCSD "	kpitch ctrl14 1, 11, 12, 0, 2\n";	
				print MYCSD "	aout diskin2 \"$files[$i]\", kpitch, 0\n";
				print MYCSD "	out aout*.80\n";
				print MYCSD "endin\n";

			} else {
				print MYCSD "	gkpitch$i pow 2, gkpitch$i\n";
				print MYCSD "	aout diskin2 \"$files[$i]\", gkpitch$i, 0\n";	
				print MYCSD "	out aout*.80\n";

				print MYCSD "endin\n";

			}

			$inst_num++;

		}
		
		print MYCSD "</CsInstruments>\n";
		print MYCSD "<CsScore>\n";

		print MYCSD "i1 0 \$INF\n";

		print MYCSD "</CsScore>\n";
		print MYCSD "</CsoundSynthesizer>\n";

	} else {

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
		print MYCSD "ksmps = 8\n";
		print MYCSD "nchnls = 1\n";
		print MYCSD "0dbfs = 1\n";

		for ($i = 1; $i <=$max_files_allowed; $i++) {
		
			print MYCSD "gkpitch$i init 0\n";
		
		}

		print MYCSD "instr 1\n";

		print MYCSD "	ksystem system 1, \"/home/scripts/fileLoadFeedback &\"\n";

		print MYCSD "	killall ctrl7 1, 28, 0, 127\n";

		print MYCSD "	kutility ctrl7 1, 23, 0, 127\n";

		print MYCSD "	if (kutility == 28) then\n";
		print MYCSD "		ksystem system 1, \"umount -l /dev/sda1 \"\n";
		print MYCSD "		ksystem system 1, \"echo 4 > /var/tmp/start_flag\"\n";
		print MYCSD "		event \"e\", 0, 0, 0\n";
		print MYCSD "	elseif (kutility == 26) then\n";
		print MYCSD "		ksystem system 1, \"echo 0 > /var/tmp/start_flag\"\n";
		print MYCSD "		event \"e\", 0, 0, 0\n";
		print MYCSD "	endif\n";

		print MYCSD "	if (killall == 127) then\n";

		for ($i = 2; $i <= $max_files_allowed+1; $i++) {
		
			print MYCSD "	turnoff2 $i, 0, 0\n";	
		
		}

		print MYCSD "	endif\n";

		for ($i = 1; $i <= $max_files_allowed; $i++) {

			print MYCSD "	initc7 1, $i, 0\n";
			print MYCSD "	ktrigger$i ctrl7 1, $i, 0, 127\n";
			print MYCSD "	kflag$i init 0\n";

			print MYCSD "	gkpitch$i ctrl14 1, $pitch_msb, $pitch_lsb, -3, 1\n";
			
			$pitch_msb += 2;
			$pitch_lsb += 2;

			if ($pitch_msb == 23) {
		
				$pitch_msb++;
				$pitch_lsb++;
			
			}

		}
		
		for ($i = 1; $i <= $max_files_allowed; $i++) {

			print MYCSD "	if (kflag$i == 0) then\n";
			print MYCSD "		if (ktrigger$i == 127) then\n";
			print MYCSD "			event \"i\", $inst_num, 0, 99999\n";
			print MYCSD "			turnoff2 $inst_num, 1, 0\n";
			print MYCSD "			kflag$i = 1\n";
			print MYCSD "		elseif (ktrigger$i == 63) then\n";
			print MYCSD "			turnoff2 $inst_num, 0, 0\n";
			print MYCSD "		endif\n";
			print MYCSD "	endif\n";

			print MYCSD "	if (ktrigger$i == 0) then\n";
			print MYCSD "		kflag$i = 0\n";
			print MYCSD "	endif\n";

			$inst_num++;

		}

			print MYCSD "endin\n";

			$inst_num = 2;

		for ($i =1; $i <= $max_files_allowed; $i++) {

			print MYCSD "instr $inst_num\n";
			#print MYCSD "	kpitch ctrl14 1, $pitch_msb, $pitch_lsb, -3, 1\n";

			if ($inst_num == 3) {
			
				print MYCSD "	kpitch ctrl14 1, 11, 12, 0, 2\n";	
				print MYCSD "	aout diskin2 \"$files[$i]\", kpitch, 0\n";
				print MYCSD "	out aout*.80\n";
				print MYCSD "endin\n";
			
			} else {

				print MYCSD "	gkpitch$i pow 2, gkpitch$i\n";
				print MYCSD "	aout diskin2 \"$files[$i]\", gkpitch$i, 0\n";	
				print MYCSD "	out aout*.80\n";
				print MYCSD "endin\n";

			}

			$inst_num++;

		}
		
		print MYCSD "</CsInstruments>\n";
		print MYCSD "<CsScore>\n";

		print MYCSD "i1 0 \$INF\n";

		print MYCSD "</CsScore>\n";
		print MYCSD "</CsoundSynthesizer>\n";

	}

system("perl /home/scripts/script_chooser.pl");
