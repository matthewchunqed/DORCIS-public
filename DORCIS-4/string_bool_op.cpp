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

void write_c(string *s, vector<int> tmp_tab, bool qiskit, bool to_reverse = false, bool x = false)
{
  if(qiskit){
  int i = 0;
  auto pos = s->find_first_of("(");
  if(x){
  s->insert(pos+1, to_string(tmp_tab[0]));
  }
  if (to_reverse) { reverse(tmp_tab.begin(), tmp_tab.end()); }
  while((pos = s->find_first_of("(", pos+1)) != string::npos)
  {
    s->insert(pos+1, to_string(tmp_tab[i%(tmp_tab.size())]));
    i++;
  }
  }else{
    int i = 0;
    auto pos = s->find_first_of("[");
    s->insert(pos+1, to_string(tmp_tab[0]));
    if (to_reverse) { reverse(tmp_tab.begin(), tmp_tab.end()); }
    while((pos = s->find_first_of("[", pos+1)) != string::npos)
    {
      s->insert(pos+1, to_string(tmp_tab[i%(tmp_tab.size())]));
      i++;
    }
  }
}

string bool_op_not(const function_t f, string s, bool reverse, bool qiskit)
{
  int tmp;
  function_t fun_prev = f;
  if(!reverse)
  {
    fun_prev.bit_slice[f.info_line] = f.prev;
    for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) tmp = i;
  }
  else tmp = f.info_line;
  write_c(&s, {tmp}, qiskit, false, true);
  return s;
}

string bool_op_two_inputs(const function_t f, string s, bool reverse, bool qiskit)
{
  int tmp;
  function_t fun_prev = f;
  if(!reverse)
  {
    fun_prev.bit_slice[f.info_line] = f.prev;
    for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) tmp = i;
  }
  else tmp = f.info_line;

  UINT_ a = 0, b;

  int j;
  for(j = 0; j < N; j++)
  {
    a = (fun_prev.bit_slice[tmp]) ^ (fun_prev.bit_slice[j]); 
    
    if(!reverse) b = f.bit_slice[f.info_line];
    else b = f.prev;
    if(a == b) break;
  }
  //tmp and j hold the inputs
  write_c(&s, {tmp, j}, qiskit, true);
  return s;
}

string bool_op_super_gates(const function_t f, int operation, string s, bool reverse, bool qiskit)
{
  int tmp;
  function_t fun_prev = f;
  if(!reverse)
  {
    fun_prev.bit_slice[f.info_line] = f.prev;
    for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) tmp = i;
  }
  else tmp = f.info_line;

  UINT_ a = 0, b;
  switch(operation)
  {
    case CCNOT2      :
          for(int k = 0; k < N; k++)
          {
            for(int j = 0; j < N; j++)
            {
               a = (fun_prev.bit_slice[k] & fun_prev.bit_slice[j]) ^ fun_prev.bit_slice[tmp]; 
              if(!reverse) b = f.bit_slice[f.info_line];
              else b = f.prev;
              if( a == b )
              {
                write_c(&s, {tmp, k, j}, qiskit, true);
                return s;
              }
            }
          }
          break;
    case CCCNOT2          :
          for(int k = 0; k < N; k++)
          {
            for(int j = 0; j < N; j++)
            {
              for(int l = 0; l < N; l++)
              {
                a = (fun_prev.bit_slice[k]&fun_prev.bit_slice[j]&fun_prev.bit_slice[l])^fun_prev.bit_slice[tmp];  
                
                if(!reverse) b = f.bit_slice[f.info_line];
                else b = f.prev;
                if( a == b )
                {
                  write_c(&s, {tmp, l, j, k}, qiskit, true);
                  return s;
                }
              }
            }
          }
  }
  return s;
}

string bool_op_base_string(uint8_t op, bool qiskit)
{
    if(qiskit){
    switch (op)
    {
      case RNOT1             : return "circuit.x()\n";
      case CNOT1             : return "circuit.cx((),())\n";
      case CCNOT2            : return "circuit.ccx((),(),())\n";
      case CCCNOT2           : return "#circuit.cccx((),(),(),())\n#Qiskit doesn't natively support CCCX gates.\n";
    }
    }
    string feq   = "F[] = ";
    switch (op)
    {
      case RNOT1             : return feq+"RNOT1(F[]);\n";
      case CNOT1             : return feq+"CNOT1(F[], F[]);\n";
      case CCNOT2            : return feq+"CCNOT2(F[], F[], F[]);\n";
    }
    return "";
}

string bool_op_to_string(const function_t f, uint8_t op, bool reverse, bool qiskit)
{
  switch (op)
  {
    case RNOT1 :
    return bool_op_not(f, bool_op_base_string(op, qiskit), reverse, qiskit);

    case CNOT1 :
    return bool_op_two_inputs(f, bool_op_base_string(op, qiskit), reverse, qiskit);

    case CCNOT2         :
    case CCCNOT2        :
    return bool_op_super_gates(f, op, bool_op_base_string(op, qiskit), reverse, qiskit);
  }
  return "";
}
