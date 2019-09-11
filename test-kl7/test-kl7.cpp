//
/// \file test-kl7.cpp
/// \package kl7
//
/// \author  Joseph Dunn on 9/5/19.
/// \copyright © 2019 Joseph Dunn.
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

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include "kl7.h"
#include "internal_method.h"
#include "dr_wiring.h"

int main(int argc, const char * argv[]) {
  cout << "// Check whether the wiring uses internal method" << endl << endl;
  int i = 1;
  for (auto a : DR_wiring::wiring) {
    cout << "// Rotor: " << i++ << endl;
    vector<int> a_vec;
    for (auto b : a)
      a_vec.push_back(b-1);
    Checker chk(a_vec);
    cout << chk << endl;
  }
  
  KL7::initialize_static(DR_wiring::wiring, DR_wiring::notch_ring,
                         DR_wiring::base_plate);  
  
  cout << "Run with Appendix B messages from the help file" << endl << endl;
  cout << "Setting system with indicator 28604" << endl << endl;
  KL7SystemIndicator si;
  si.indicator = "28604";
  si.rotor_core={'E','H','F','L','I','A','G','B'};
  si.alphabet_ring_set={4,28,4,16,9,32,8,11};
  si.notch_ring_num={5,10,6,7,1,8,3};
  si.notch_ring_set={"C","M+","E","B","E+","Y","K"};
  si.letter_check = "ASMTH ISXPI";
  
  KL7 kl7(si);
  
  // 28604 ECHO ZULU INDIA YANKEE WHISKEY
  string preface;
  string msg_1_plain_text = kl7.decrypt_file("../data/msg_1_cipher_text.txt", preface);
  cout << endl << "Message 1 preface & plain text: " << endl;
  cout << preface << endl;
  cout << line_wrap(msg_1_plain_text, 70) << endl;
  
  // 28604 FOXTROT BRAVO NOVEMBER KILO TANGO
  string msg_2_plain_text = kl7.decrypt_file("../data/msg_2_cipher_text.txt", preface);
  cout << endl << "Message 2 preface & plain text:" << endl;
  cout << preface << endl;
  cout << line_wrap(msg_2_plain_text, 70) << endl;
  
  return 0;
}
