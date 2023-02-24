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

void bool_op_simple_gates(function_t f, vector<function_t> *v, int operation)
{
  function_t fun_tmp = f;
  
  if(operation == RNOT1) 
  {
    for(int i = 0; i < N; i++) 
    {
      fun_tmp.bit_slice[i] = ~(f.bit_slice[i]);
      //RNOT implementation
      fun_tmp.info_line = (uint8_t)i;
      fun_tmp.info_op = (uint8_t)operation;
      fun_tmp.prev = f.bit_slice[i];
      fun_tmp.sort();
      v->push_back(fun_tmp);
      fun_tmp = f;
    }
  }
  else
  {
    for(int i = 0; i < N; i++)
    {
      for(int j = 0; j < N; j++)
      {
        if(i != j)
        {
          fun_tmp.bit_slice[i] = (f.bit_slice[i])^(f.bit_slice[j]); 
          int _ = f.bit_slice[i]; 
          //CNOT implementation         
          fun_tmp.prev = f.bit_slice[i];
          fun_tmp.info_line = (uint8_t)i;
          fun_tmp.info_op = (uint8_t)operation;
          fun_tmp.sort();
          v->push_back(fun_tmp);
          fun_tmp = f;
        }
      }
      fun_tmp = f;
    }
  }
}

void bool_op_double_gates(function_t f, vector<function_t> *v, int operation)
{
  auto two_inputs = [](const function_t f, int i, int a, int b, int operation)
  {
    auto fun_tmp = f;
    
    fun_tmp.bit_slice[i] = (f.bit_slice[(i+a)%N]&f.bit_slice[(i+b)%N])^f.bit_slice[i];
    int _ = f.bit_slice[(i+a)%N];
    int __ = f.bit_slice[(i+b)%N];
    //CCNOT implementation
   
    fun_tmp.prev = f.bit_slice[i];
    fun_tmp.info_line = i;
    fun_tmp.info_op = operation;
    fun_tmp.sort();
    return fun_tmp;
  };

  auto three_inputs = [](const function_t f, int i, int a, int b, int c, int operation)
  {
    auto fun_tmp = f;
    
    fun_tmp.bit_slice[i] = (f.bit_slice[(i+a)%N]&f.bit_slice[(i+b)%N]&f.bit_slice[(i+c)%N])^f.bit_slice[i];
    int _ = f.bit_slice[(i+a)%N];
    int __ = f.bit_slice[(i+b)%N];
    int ___ = f.bit_slice[(i+c)%N];
    //CCCNOT implementation
    
    fun_tmp.prev = f.bit_slice[i];
    fun_tmp.info_line = (uint8_t)i;
    fun_tmp.info_op = (uint8_t)operation;
    fun_tmp.sort();
    return fun_tmp;
  };

  switch (operation)
  {
    case CCCNOT2          :
                       for (int i = 0; i < N; i++)
                       {
                         v->push_back(three_inputs(f, i, 1, 2, 3, operation));
                       }
                       break;

    case CCNOT2      :
                       for (int i = 0; i < N; i++)
                       {
                         v->push_back(two_inputs(f, i, 1, 2, operation));
                         v->push_back(two_inputs(f, i, 2, 3, operation));
                         v->push_back(two_inputs(f, i, 1, 3, operation));
                       }
                       break;
  }
}

void bool_op_fun( int op_id, function_t f, vector<function_t> *v)
{
  switch (op_id)
  {
    case RNOT1 :
    case CNOT1 : bool_op_simple_gates(f, v, op_id); break;

    case CCNOT2           : 
    case CCCNOT2          : bool_op_double_gates(f, v, op_id); break;
  }
}