# TSEC/KL-7 Simulator with Command Line Interface

## Introduction

The TSEC/KL-7 cipher machine (KL-7 for short) is a rotor based cipher machine that was
introduced in 1952 by the newly formed NSA.  It was the successor the high level ECM 
Mark II (SIGABA) cipher machine and the low level M-209 machine.  It was supplied to
NATO allies and it stayed in service until 1983.  It incorpoated an irregular stepping scheme
and introduced the reencipherment process.  KL-7 communciations were breached a 
number of times as a result of expionage thefts, but there is no known case of the
cipher being broken without the theft of the key sheets.

## Motivation

Although Dirk Rijmenants developed a very faithful simulator with an impressive graphical
user interface, he has not released the source code.  The current package is intented to
provide an open source version of the cryptological engine of the KL-7 with a command 
line interface.  It is interoperable with Dirk Rijmenants' simulator as well as the Java based
simulator developed by Uri Blumenthal of MIT.

## Installation
The software is written in C++, and is provided with meson build files, which should 
allow for easy compilation by any standard C++11 compiler.  It uses some of the 
Boost libraries which must be installed prior to the build process.  Once meson, ninja
(the backend for the meson build system) and Boost are installed the following sequence
will build the package.

    meson build
    cd build
    ninja
    
which compiles the programs and produces doxygen documentation with the results
placed in various subdirectors of the build directory.  To run some of the test programs
type:

    ninja test
    
If everything works the test protocol will report whether the tests were successful.  The
output of the tests is placed in the test-log.txt file in the meson-logs subdirector of
the build directory.

## Running the program

The program is run from the command line.  For instance 

    cd build
    ./kl7-cli/kl7 -h

produces the following output:

    kl7: CLI to KL-7 cipher machine simulator:
    -h [ --help ]                         display help message
    -e [ --encrypt ]                      perform an encrypt operation
    -d [ --decrypt ]                      perform a decrypt operation
    --systemIndicator arg (=00000)        system indicator, e.g. 28604
    --rotorCore arg (=ABCDEFGH)           rotor core A-M e.g. "ABCDEFGH"
    --alphaRingSet arg (=1 1 1 1 1 1 1 1) alpha ring set 1-36 e.g. "1 2 3 4 5 6 7 8"
    --notchRingNum arg (=1 2 3 4 5 6 7)   notch ring number 1-11 e.g. "1 2 3 4 5 6 7"
    --notchRingSet arg (=A A A A A A A)   notch ring set e.g. "A B B+ C D E E+"
    --letterCheck arg                     36 to 45 letter check when encrypting 
                                          45 L's
    --messageIndicator arg                message indicator e.g. AAAAA
    -t [ --text ] arg                     input text to encrypt/decrypt
    -i [ --input ] arg                    file to read input text from

Much more extensive documentation of the KL-7 is contained in Dirk Rijmenants' help file,
which is contained in the doc subdirectory of the source distribution, and the original
operation manuals, which are also contained in the doc directory.

The wiring of the actual rotors used by the government is still classified.  Dirk Rijmenants
developed his own wiring for use in his simulator.  This program uses that wiring so that
it can interoperate with Dirk Rijmenants' simulator.

## Discrepancy with the Original Operation Manual

The simulator interprets the meaning of the notchRingSet differently from that described
in the government operations manuals.  Quoting the manual:

> Setting notch ring to designated letter of alphabet ring:
> (1) Depress the notch ring and rotate it relative to the core until the paired bench marks
> (line and arrow) bracket the designated letter of the alphabet ring (D).

This simulaor follows Dirk Rijmenants' in interpreting the notch ring set as if the
notch ring itself contains letter positions and the designated letter of the notch ring is set
opposite the 1 position on the rotor core.  Since none of the original machines are extant, 
we followed Rijmenants' interpretation in order to preserve interoperability.

## Copyright, License

The software is copyright (c) Joseph Dunn Sept. 9, 2019.

Since the present simulator is in part derived from Dirk Rijmenants' simulator, we've
chosen to follow his license which he states as follows:

> This program is provided as freeware and can be used and distributed under the
> following conditions: it is strictly forbidden to use this software or copies
> or parts of it for commercial purposes or to sell or lease this software, or
> to make profit from this program by any means. You are allowed to use this
> software only if you agree to these conditions.

## Disclaimer of Warranties

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
