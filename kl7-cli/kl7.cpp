//
///  \file kl7.cpp
///  \package kl7
//
///  \author Joseph Dunn on 9/5/19.
///  \copyright © 2019 Joseph Dunn. 
//

/*
 Dirk Rijmenants's original simulator copyright © 2006-2013
 
 Copyright Information
 This program is provided as freeware and can be used and distributed under the
 following conditions: it is strictly forbidden to use this software or copies
 or parts of it for commercial purposes or to sell or lease this software, or
 to make profit from this program by any means. You are allowed to use this
 software only if you agree to these conditions.
 
 Disclaimer of Warranties
 This software and the accompanying files are supplied “as is” and without
 warranties of any kind, either expressed or implied, with respect to this
 product, its quality, performance, or fitness for any particular purpose.
 The entire risk as to its quality and performance is with the user. In no
 event will the author of this software be liable for any direct, indirect
 or consequential damages, resulting out of the use or inability to use this
 software.
 */

#include "kl7.h"

array<char,36> KL7::ring { 65, 66, 32, 67, 68, 69, 32, 70, 71, 32, 72, 73, 74, 32, 75, 76, 77, 32, 78, 79, 32, 80, 81, 82, 32, 83, 84, 32, 85, 86, 87, 32, 88, 89, 90, 32 };
array<char,26> KL7::alpha_to_ring;

array< array<char, 36>, 13> KL7::wiring;
array< array<char, 36>, 13> KL7::inverse_wiring;
array<char, 36> KL7::base_plate;
array<char, 26> KL7::alpha_to_plate;
array<char, 10> KL7::num_to_plate;
array< array<bool,36> , 11> KL7::notch_ring;
string KL7::plus_letters;

