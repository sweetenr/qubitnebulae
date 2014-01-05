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

while (1) {

	open FILE, "/var/tmp/start_flag";

		while (<FILE>) {
		
			chomp $_;
			$flag = $_;
		
		}

	close (FILE);

	if ($flag == 0) {
		
		system("csound /var/tmp/nebulae.csd");
	
	
	} elsif ($flag == 1) {

		system("mount /dev/sda1 /mnt/memory");
		system("csound /var/tmp/nebulae_oneshot.csd");	
	
	} elsif ($flag == 3) {
	
		system("echo 0 > /var/tmp/start_flag");	
		system("sh /home/scripts/initialize_b.sh");
	
	} elsif ($flag == 4) {
	
		system("echo 1 > /var/tmp/start_flag");
		system("sh /home/scripts/initialize_b.sh");
	
	}

}
