/**
 * Optimizing Implementations of Lightweight Building Blocks
 *
 *  Copyright 2017 by
 *    Jade Tourteaux <Jade[dot]Tourteaux[at]gmail.com>
 *    Jérémy Jean <Jean[dot]Jeremy[at]gmail.com>
 *
 * This file is part of some open source application.
 * 
 * Some open source application is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU General Public 
 * License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Some open source application is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

#include "mitm.h"

vector<bool_op_t> b; // The boolean instructions (B in the paper)
function_t start;
function_t arrival;
function_t unsorted_arrival;
function_t unsorted_function;
map<int, set<function_t> > f1_succ;
map<int, set<function_t> > f2_succ;
long count_list;
int shortest_path = numeric_limits<int>::max();
int tdepthrec = numeric_limits<int>::max();
string implementation_id = "_";

int max_GE = 0;
bool verbose = false;
bool tdepmode = false;
bool one_expand = false;
bool write_in_file = false;
int omp_nb_threads = 20;
int max_ram = 30;

int gate_rnot1 = false;
int gate_cnot1 = false;
int gate_ccnot2 = false;

int rnot1_cost;
int cnot1_cost;
int ccnot2_cost;


function_t parse_function(string str)
{
  if(str.size() == 8)
  {
    if(str[2] == ' ' && str[5] == ' ')
    {
      stringstream ss(str);
      string number;
      function_t res;
      int i = -1;
      while(getline(ss, number, ' ') && ++i < N) res.bit_slice[i] = stoul(number, nullptr, 16);
      return res;
    }
    else
    {
      string s = "";
      int toAdd = 0;
      std::ostringstream ss;
      for(int i=0; i<8; i++){
        int add = 1;
        if(str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7'){
          for(int j=0; j<7-i; j++){
          add = add*2;
          }
          toAdd += add;
        }
      }
	    ss << std::hex << toAdd << " ";
      toAdd = 0;
      for(int i=0; i<8; i++){
        int add = 1;
        if(str[i] == '2' || str[i] == '3' || str[i] == '6' || str[i] == '7'){
          for(int j=0; j<7-i; j++){
          add = add*2;
          }
          toAdd += add;
        }
      }
	    ss << std::hex << toAdd << " ";
      toAdd = 0;
      for(int i=0; i<8; i++){
        int add = 1;
        if(str[i] == '1' || str[i] == '3' || str[i] == '5' || str[i] == '7'){
          for(int j=0; j<7-i; j++){
          add = add*2;
          }
          toAdd += add;
        }
      }
	    ss << std::hex << toAdd;
      string res = ss.str();
      return parse_function(res);
    } 
  }else{
    return parse_function("01234567");
  }
}

void reversible_gates()
{
  gate_rnot1 = true;
  gate_cnot1 = true;
  gate_ccnot2 = true;
}


int bool_op_cost(uint8_t op)
{
  switch (op)
  {
    case RNOT1             : return rnot1_cost;
    case CNOT1             : return cnot1_cost;
    case CCNOT2            : return ccnot2_cost;
    
    default                : return -1;
  }
}

int tcost(uint8_t op)
{
  switch (op)
  {
    case RNOT1             : return 1;
    case CNOT1             : return 1;
    case CCNOT2            : return 100;
    
    default                : return -1;
  }
}
//Change this to change the T-depth decomposition weights for each gate.

int cost(uint8_t op)
{
  switch (op)
  {
    case RNOT1             : return 100;
    case CNOT1             : return 100;
    case CCNOT2            : return 700;
    
    default                : return -1;
  }
}
//Change this to change the T-depth decomposition weights for each gate.

void init_b()
{

  if(tdepmode){
    rnot1_cost = 1;
    cnot1_cost = 1;
    ccnot2_cost = 100;
  }else{
    rnot1_cost = 100;
    cnot1_cost = 100;
    ccnot2_cost = 700;
  }

  /*
    initilisation of the set of bolean operations
  */

  if(gate_rnot1 && bool_op_cost(RNOT1)) 
  {
    b.push_back({RNOT1, bool_op_cost(RNOT1)});
  }
  if(gate_cnot1 && bool_op_cost(CNOT1)) 
  {
    b.push_back({CNOT1, bool_op_cost(CNOT1)});
  }
  if(gate_ccnot2 && bool_op_cost(CCNOT2))
  {
    b.push_back({CCNOT2, bool_op_cost(CCNOT2)});
  }

  sort(b.begin(), b.end());

  b.erase(remove_if(b.begin(), b.end(),
      [](bool_op_t bool_op)
      {
        static set<vector<function_t>> check_tt;
        const function_t f1({0x0f, 0x33, 0x55});
        vector<function_t> f;
        bool_op_fun(bool_op.op_id, f1, &f);
        sort(f.begin(), f.end());
        auto check = check_tt.insert(f);
        return !check.second;
      }), b.end());

}

int main(int argc, char *argv[])
{

  function_t f1({0x0f, 0x33, 0x55});
  function_t f2({0x0f, 0x33, 0x55});
  //function_t f2({0x00ff, 0x0f0f, 0x3333, 0x5555});

  struct option longopts[] = {
   { "rnot1", no_argument, &gate_rnot1, 1},
   { "cnot1", no_argument, &gate_cnot1, 1},
   { "ccnot2", no_argument, &gate_ccnot2, 1},
   {0, 0, 0, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "i:o:m:l:vuwtqp:r:s:", longopts, NULL)) != EOF)
  {
    switch(opt)
    {
      case 't': tdepmode = false; break; //tdepmode same as standard in 3 bit.
      case 'q': reversible_gates(); break;
      case 'v': verbose = true; break;
      case 'u': one_expand = true; break;
      case 'w': write_in_file = true; break;
      case 'i': f1 = parse_function(optarg); break;
      case 'o': f2 = parse_function(optarg); implementation_id = "_"; implementation_id += optarg; implementation_id += "_"; break;
      case 'p': omp_nb_threads = (atoi(optarg));  cout << "Thread number : "<< omp_nb_threads<<endl;break;
      case 'r': max_ram = atoi(optarg); break;
      case 's': implementation_id = "_"; implementation_id += optarg; implementation_id += "_"; break;
      case '?': fprintf(stderr, "wrong cmd line");
    }
  }
  

  cout << "\nFrom : " << f1.to_string() << endl;
  cout << "To   : " << f2.to_string() << endl;

  init_b();
  mitm(f1, f2);
  return 0;
}
