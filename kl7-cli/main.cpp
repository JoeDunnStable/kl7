//
/// \file kl7-cli.cpp
/// \package kl7
//
/// \author Joseph Dunn on 9/9/19.
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
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
using boost::filesystem::path;
#include <boost/algorithm/string/split.hpp>
using boost::algorithm::split;
using boost::algorithm::token_compress_on;
#include "kl7.h"
#include "dr_wiring.h"

int main(int argc, const char * argv[]) {
  path p(argv[0]);
  string program_name = p.filename().string();
  KL7::initialize_static(DR_wiring::wiring, DR_wiring::notch_ring,
                         DR_wiring::base_plate);
  using namespace boost::program_options;
  bool encrypt{false}, decrypt{false};
  string rotor_core_str, alphabet_ring_set_str, notch_ring_num_str,
  notch_ring_set_str;
  string system_indicator, letter_check, message_indicator;
  string input_text, input_file;
  
  options_description desc{program_name + ": CLI to KL-7 cipher machine simulator"};
  
  desc.add_options()
  ("help,h", "display help message")
  ("encrypt,e", bool_switch(&encrypt), "perform an encrypt operation")
  ("decrypt,d", bool_switch(&decrypt), "perform a decrypt operation")
  ("systemIndicator", value<string>(&system_indicator)->default_value("00000"), "system indicator, e.g. 28604")
  ("rotorCore",value<string>(&rotor_core_str)->default_value("ABCDEFGH"),"rotor core e.g. \"ABCDEFGH\"")
  ("alphaRingSet",value<string>(&alphabet_ring_set_str)->default_value("1 1 1 1 1 1 1 1"),"alpha ring set e.g. \"1 2 3 4 5 6 7 8\"")
  ("notchRingNum",value<string>(&notch_ring_num_str)->default_value("1 2 3 4 5 6 7"),"notch ring number e.g. \"1 2 3 4 5 6 7\"")
  ("notchRingSet",value<string>(&notch_ring_set_str)->default_value("A A A A A A A"),"notch ring set e.g. \"A B B+ C D E E+\"")
  ("letterCheck",value<string>(&letter_check),"36 to 45 letter check when encrypting 45 L's")
  ("messageIndicator",value<string>(&message_indicator),"message indicator e.g. AAAAA")
  ("text,t",value<string>(&input_text),"input text to encrypt/decrypt")
  ("input,i", value<string>(&input_file),"file from which to read input");
  
  variables_map vm;

  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);
  
  if (vm.count("help")) {
    cout << desc << endl;
    return 0;
  }
  
  if (!decrypt && !encrypt) {
    cout << program_name << ": Specify encrypt or decrypt" << endl;
    return 1;
  }
  if (encrypt && decrypt) {
    cout << program_name << ": Supply either -e or -d, not both" << endl;
    return 1;
  }
  KL7SystemIndicator si;
  si.indicator = system_indicator;
  
  if (rotor_core_str.size() != 8) {
    cout << program_name << ": Rotor core is not of length 8" << endl;
    return 1;
  }
  for (size_t i=0; i<8; ++i) {
    char c = rotor_core_str[i];
    if (c < 'A' || c > 'M') {
      cout << program_name << ": Rotor core must be letters in A-M" << endl;
      return 1;
    }
    if (i>0 && rotor_core_str.substr(0,i).find(c) != string::npos) {
      cout << program_name << " Rotor " << c
      << " is repeated.  Rotors must be distinct" << endl;
      return 1;
    }
    si.rotor_core.at(i) = c;
  }
  
  vector<string> alpha_str_vec;
  split(alpha_str_vec, alphabet_ring_set_str, isspace, token_compress_on);
  if (alpha_str_vec.size() != 8) {
    cout << program_name << ": Alphabet ring set must have 8 positions" << endl;
    return 1;
  }
  for (size_t i=0; i<8; ++i) {
    istringstream iss(alpha_str_vec.at(i));
    int a{-1};
    if (!(iss >> a) || a<1 || a>36) {
      cout << program_name << ": Each alphabet ring set must be integer between 1 and 36" << endl;
      return 1;
    }
    si.alphabet_ring_set.at(i) = a;
  }
  
  vector<string> notch_ring_vec;
  split(notch_ring_vec, notch_ring_num_str, isspace, token_compress_on);
  if (notch_ring_vec.size() != 7) {
    cout << program_name << ": Notch ring number must have 7 positions" << endl;
    return 1;
  }
  for (size_t i=0; i<7; ++i) {
    istringstream iss(notch_ring_vec.at(i));
    int a{-1};
    if (!(iss >> a) || a<1 || a>11) {
      cout << program_name << ": Each notch ring number must be integer between 1 and 11" << endl;
      return 1;
    }
    auto itr = si.notch_ring_num.begin();
    if (i>0 && std::find(itr, itr+i, a) < itr + i) {
      cout << program_name << " Notch Ring " << a
      << " is repeated.  Rotors must be distinct" << endl;
      return 1;
    }
    si.notch_ring_num.at(i) = a;
  }
  
  vector<string> notch_ring_set_vec;
  split(notch_ring_set_vec, notch_ring_set_str, isspace, token_compress_on);
  if (notch_ring_set_vec.size() !=7) {
    cout << program_name << ": Notch ring set must have 7 positions" << endl;
    return 1;
  }
  for (size_t i=0; i<7; ++i) {
    string a = notch_ring_set_vec.at(i);
    if (a[0] < 'A' || a[0] > 'Z'
        || (a.size()==2 && (KL7::plus_letters.find(a[0])==string::npos || a[1] != '+'))) {
      cout << program_name << ": Notch ring sets must be A-Z or "
           << KL7::plus_letters << " with a plus" << endl;
      return 1;
    }
    si.notch_ring_set.at(i) = a;
  }
  
  if (vm.count("letterCheck") > 0) {
    si.letter_check = letter_check;
  }
  
  if (!vm.count("text") && !vm.count("input")) {
    cout << program_name << ": " << "Supply either -t or -i" << endl;
    return 1;
  }
  
  if (vm.count("text") && vm.count("input")) {
    cout << program_name << ": " << "Supply either -t or -i, not both" << endl;
    return 1;
  }
  

  KL7 kl7(si);
  
  if (vm.count("text")>0) {
    array<char,7> message_pos;
    if (vm.count("mesaageIndicator") > 0 && message_indicator.size()==5) {
      kl7.set_position(array<char, 7>{'A','A','A','A','A','A','A'});
      string m = kl7.encrypt(message_indicator);
      if (m.size() != 5) {
        message_pos = {'A','A','A','A','A','A','A'};
      }
      else {
        message_pos = {m[0],m[1],m[2],m[3],m[4],m[0],m[1]};
      }
    } else
      message_pos ={'A','A','A','A','A','A','A'};
    kl7.set_position(message_pos);
    if (encrypt) {
      cout << line_wrap(kl7.encrypt(input_text),70) << endl;
    } else {
      cout << line_wrap(kl7.decrypt(input_text),70) << endl;
    }
  }
  
  if (vm.count("input")>0) {
    string text, preface;
    if (encrypt) {
      text = kl7.encrypt_file(input_file, preface );
    } else
      text = kl7.decrypt_file(input_file, preface);
    cout << preface << endl;
    cout << text << endl;
  }
  
  return 0;
}
