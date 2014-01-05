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

system("mount /dev/sda1 /mnt/memory");

system("perl /home/scripts/csd_check.pl");

system("ls /mnt/memory/*.wav > /var/tmp/fileNames");
system("ls /mnt/memory/*.aif >> /var/tmp/fileNames");
system("ls /mnt/memory/*.flac >> /var/tmp/fileNames");
system("ls /mnt/memory/*.ogg >> /var/tmp/fileNames");

open FILE, "/var/tmp/fileNames";

$i = 1;
$sr = 20000;
$number_of_files = 0;
$max_size = 74449;
$size = 0;
$max_size_flag = 0;
$num_samples = 0;
$each_samples = 0;
$max_samples = 24696000;

while (<FILE>) {

	chomp $_;

	$old_file = $_;
	$cmd_line_name = $_;
	
	$_ =~ s/'//g;
	$_ =~ tr/ //ds;
	$_ =~ s/\$//g;
	$_ =~ s/\?//g;
	$_ =~ s/\!//g;
	$_ =~ s/\@//g;
	$_ =~ s/\&//g;
	$_ =~ s/\*//g;
	$_ =~ s/\;//g;

	$cmd_line_name =~ s/(?= [' !@&*()?:;] ) /\\/xg;

	system("mv $cmd_line_name '$_'");	

	$each_samples = `soxi -s '$_'`;
	$num_samples += $each_samples;

	if ($num_samples > $max_samples) {
			
		$num_samples -= $each_samples;
		$max_size_flag = 1;
			
	} else {

		$filechannels = `sox --i '$_' | grep -i "Channels"`;

		if ($filechannels =~ /2/) {

			if ($_ =~ /\.wav$/i) {
		
				system("sox '$_' -c 1 /mnt/memory/temp.wav");
				system("mv /mnt/memory/temp.wav '$_'");	

			} elsif ($_ =~ /\.aif$/i) {
				
				system("sox '$_' -c 1 /mnt/memory/temp.aif");
				system("mv /mnt/memory/temp.aif '$_'");
			
			} elsif ($_ =~ /\.flac$/i) {
			
				system("sox '$_' -c 1 /mnt/memory/temp.flac");
				system("mv /mnt/memory/temp.flac '$_'");

			} elsif ($_ =~ /\.ogg$/i) {
			
				system("sox '$_' -c 1 /mnt/memory/temp.ogg");
				system("mv /mnt/memory/temp.ogg '$_'");

			}

		$files[$i] = $_;
		$number_of_files++;
		$i++;


		} else {
		
			$files[$i] = $_;
			$number_of_files++;	
			$i++;

		}
	}
}

close(FILE);

open (FILES, '>/var/tmp/fileNames');

for ($i = 1; $i <= $number_of_files; $i++) {
	
	print FILES "$files[$i]\n";

}

close (FILES);

system("perl /home/scripts/csd_creator.pl");

