//
///  \file dr_wiring.cpp
///  \package kl7
//
///  \author Joseph Dunn on 9/9/19.
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

#include "dr_wiring.h"

/*
 The government wiring, base_plate and notch_ring are still classifies
 The items below are from Dirk Rijmenants's help file for his simultor
 */

array< array<char, 36>, 13> DR_wiring::wiring ={
  array<char, 36>{ 29, 27, 14, 8, 35, 4, 28, 11, 5, 13, 20, 3, 25, 33, 18, 15, 7, 12, 34, 16, 17, 1, 9, 30, 24, 23, 2, 32, 10, 19, 6, 26, 36, 22, 31, 21 },
  array<char, 36>{ 23, 19, 26, 16, 2, 13, 14, 35, 21, 4, 17, 31, 25, 3, 18, 27, 12, 34, 36, 10, 30, 6, 7, 15, 28, 1, 11, 33, 29, 20, 32, 24, 5, 22, 8, 9 },
  array<char, 36>{ 19, 26, 28, 36, 6, 25, 31, 18, 27, 10, 5, 1, 32, 9, 11, 33, 23, 17, 29, 12, 13, 2, 16, 15, 35, 8, 24, 22, 30, 3, 34, 14, 7, 20, 21, 4 },
  array<char, 36>{ 15, 26, 36, 13, 1, 31, 25, 33, 3, 32, 21, 23, 17, 29, 7, 22, 20, 24, 12, 10, 14, 30, 19, 28, 4, 35, 5, 8, 6, 9, 16, 27, 2, 11, 34, 18 },
  array<char, 36>{ 13, 4, 2, 16, 17, 30, 21, 5, 33, 7, 29, 8, 9, 36, 35, 23, 34, 25, 20, 22, 28, 15, 1, 19, 24, 27, 10, 11, 6, 12, 32, 26, 14, 3, 18, 31 },
  array<char, 36>{ 26, 34, 27, 14, 2, 1, 31, 36, 11, 9, 35, 18, 15, 12, 4, 7, 29, 8, 23, 19, 3, 30, 20, 17, 28, 21, 22, 5, 25, 33, 16, 13, 24, 6, 10, 32 },
  array<char, 36>{ 20, 19, 9, 32, 36, 2, 6, 33, 12, 28, 4, 10, 3, 24, 29, 16, 22, 18, 30, 17, 7, 34, 15, 23, 31, 25, 27, 1, 21, 26, 8, 5, 13, 35, 11, 14 },
  array<char, 36>{ 28, 19, 23, 5, 17, 36, 27, 14, 16, 20, 21, 7, 12, 22, 11, 35, 13, 15, 1, 32, 8, 18, 33, 4, 9, 29, 26, 24, 25, 34, 10, 6, 3, 30, 2, 31 },
  array<char, 36>{ 25, 6, 35, 12, 21, 22, 19, 32, 20, 23, 30, 18, 1, 16, 31, 11, 24, 13, 33, 7, 36, 9, 34, 2, 10, 8, 26, 29, 15, 17, 4, 28, 14, 3, 27, 5 },
  array<char, 36>{ 8, 31, 1, 28, 20, 6, 32, 5, 33, 21, 30, 12, 4, 14, 15, 34, 7, 35, 16, 18, 29, 22, 25, 26, 36, 11, 23, 19, 3, 2, 13, 27, 24, 10, 17, 9 },
  array<char, 36>{ 15, 13, 36, 23, 6, 21, 32, 18, 31, 20, 1, 24, 10, 35, 19, 28, 7, 8, 26, 12, 29, 22, 25, 30, 5, 9, 2, 27, 16, 4, 17, 3, 34, 14, 11, 33 },
  array<char, 36>{ 8, 18, 15, 33, 7, 26, 20, 16, 34, 23, 36, 27, 12, 24, 19, 13, 2, 3, 14, 29, 1, 6, 32, 10, 25, 30, 9, 5, 28, 17, 22, 31, 4, 11, 21, 35 },
  array<char, 36>{ 36, 6, 29, 28, 24, 26, 21, 22, 20, 35, 15, 19, 23, 30, 1, 8, 12, 7, 13, 27, 31, 32, 9, 33, 10, 16, 14, 18, 34, 2, 3, 17, 25, 11, 4, 5 }
};

array<char,36> DR_wiring::base_plate { 81, 80, 0, 78, 70, 67, 3, 89, 79, 77, 9, 71, 82, 8, 85, 73, 7, 66, 72, 2, 86, 84, 87, 6, 88, 83, 4, 74, 76, 90, 5, 68, 75, 69, 65, 1 };

array< array<bool,36> , 11> DR_wiring::notch_ring = {
  array<bool, 36>{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1 },
  array<bool, 36>{ 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 },
  array<bool, 36>{ 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0 },
  array<bool, 36>{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0 },
  array<bool, 36>{ 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
  array<bool, 36>{ 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1 },
  array<bool, 36>{ 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0 },
  array<bool, 36>{ 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
  array<bool, 36>{ 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0 },
  array<bool, 36>{ 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0 },
  array<bool, 36>{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 }
};

