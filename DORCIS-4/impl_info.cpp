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
#include <stack>
#include <queue>

extern function_t start;
extern function_t arrival;
extern function_t unsorted_arrival;
extern function_t unsorted_function;
extern map<int, set<function_t> > f1_succ;
extern map<int, set<function_t> > f2_succ;
extern int count_list;
extern int max_impl;
extern int shortest_path;
extern int tdepthrec;
extern int gatecountrec;
extern bool tdepmode;
extern string implementation_id;
extern string conf_file;

int depth;
int tdepth;
int gatecount = 0;
int costs [4] = {0,0,0,0};
int tcosts [4] = {0,0,0,0};
std::stack<function_t> st;
std::queue<function_t> q;


void update_unsorted_function(function_t f)
{
  auto get_diff_index = [](function_t f1, function_t f2)
  {
    int i = 0;
    int j = 0;
    bool found = false;
    while(i < N)
    {
      while(j < N)
      {
        if(f1.bit_slice[i] == f2.bit_slice[j])
        {
          found = true;
          break;
        }
        j++;
      }
      if(found == false) return i;
      found = false;
      i++;
      j = 0;
    }
    return -1;
  };

  int i = get_diff_index(f, unsorted_function);
  int j = get_diff_index(unsorted_function, f);

  unsorted_function.bit_slice[j] = f.bit_slice[i];

  unsorted_function.prev = f.prev;
  unsorted_function.info_line = f.info_line;
  unsorted_function.info_op = f.info_op;

  UINT_ mod = f.bit_slice[f.info_line];

  for(int i = 0; i < N; i++)
    if(unsorted_function.bit_slice[i] == mod) unsorted_function.info_line = i;
}

string get_permut(function_t f1, function_t f2, char a, char b, bool qiskit)
{
  
  auto get_index = [](int n, function_t f1, function_t f2)
  {
    int i = 0;
    while( i < N )
    {
      if(f1.bit_slice[n] == f2.bit_slice[i]) return i;
      i++;
    }
    return -1;
  };

  string s;
  int i = 0;
  if(qiskit){
  if(a == 'X'){
    s = s + "print(circuit.depth()) #note that this is the non-decomposed depth\ncircuit.draw(output=\"mpl\")\nplt.show()\n";
  }
  while( i < N )
  {
    s = s + "#" + a + "[" + to_string(i) + "] = ";
    s = s + b + "[" + to_string(get_index(i, f2, f1)) + "];\n";
    i++;
  }
  if(a == 'F'){
    s = s + "\nfrom qiskit import QuantumCircuit\nimport matplotlib.pyplot as plt\ncircuit = QuantumCircuit(4)\n";
  }
  return s;
  }
  while( i < N )
  {
    s = s + a + "[" + to_string(i) + "] = ";
    s = s + b + "[" + to_string(get_index(i, f2, f1)) + "];\n";
    i++;
  }
  return s;
}

void getMax(function_t f, bool reverse){
  
    switch (f.info_op)
  {
    case 78 :
    {
    costs[f.info_line]++;
    break;
    }
    case 79 :
    {
    int firstInput;
    int secondInput;

    function_t fun_prev = f;
    if(!reverse)
    {
      fun_prev.bit_slice[f.info_line] = f.prev;
      for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) firstInput = i;
    }
    else firstInput = f.info_line;
    //finding first input


    uint16_t a = 0, b;
    for(secondInput = 0; secondInput < N; secondInput++)
    {
    a = (fun_prev.bit_slice[firstInput]) ^ (fun_prev.bit_slice[secondInput]);  
    if(!reverse) b = f.bit_slice[f.info_line];
    else b = f.prev;
    if(a == b) break;
    }
    int maxInputCost = costs[firstInput];

    if(costs[secondInput] > maxInputCost){
      maxInputCost = costs[secondInput];
    }
    costs[firstInput] =  maxInputCost+(cost(79)/100);
    costs[secondInput] = maxInputCost+(cost(79)/100);
    break;
    }

    case 80    :
    {
    int firstInput;
    int secondInput;
    int thirdInput;

    function_t fun_prev = f;
    if(!reverse)
    {
      fun_prev.bit_slice[f.info_line] = f.prev;
      for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) firstInput = i;
    }
    else firstInput = f.info_line;
    //finding first input
    int maxInputCost = costs[firstInput];

    uint16_t a = 0, b;
    for(secondInput = 0; secondInput < N; secondInput++)
    {
      for(thirdInput =0; thirdInput < N; thirdInput++){
        a = (fun_prev.bit_slice[secondInput] & fun_prev.bit_slice[thirdInput]) ^ fun_prev.bit_slice[firstInput];  

        if(!reverse) b = f.bit_slice[f.info_line];
        else b = f.prev;
        if(a == b) break;
      }
      if(a == b) break;
    }
    
    
    if(costs[secondInput] > maxInputCost){
      maxInputCost = costs[secondInput];
    }
    if(costs[thirdInput] > maxInputCost){
      maxInputCost = costs[thirdInput];
    }
    costs[firstInput] = maxInputCost+(cost(80)/100);
    costs[secondInput] = maxInputCost+(cost(80)/100);
    costs[thirdInput] = maxInputCost+(cost(80)/100);

    maxInputCost = tcosts[firstInput];
    if(tcosts[secondInput] > maxInputCost){
      maxInputCost = tcosts[secondInput];
    }
    if(tcosts[thirdInput] > maxInputCost){
      maxInputCost = tcosts[thirdInput];
    }
    tcosts[firstInput] = maxInputCost+(tcost(80)/100);
    tcosts[secondInput] = maxInputCost+(tcost(80)/100);
    tcosts[thirdInput] = maxInputCost+(tcost(80)/100);

    break;      
    }
    case 81    :
    {
    int firstInput;
    int secondInput;
    int thirdInput;
    int fourthInput;
    int maxInputCost = 0;
    function_t fun_prev = f;
    if(!reverse)
    {
      fun_prev.bit_slice[f.info_line] = f.prev;
      for(int i = 0; i < N; i++) if(fun_prev.bit_slice[i] == f.prev) firstInput = i;
    }
    else firstInput = f.info_line;
    //finding first input

    maxInputCost = costs[firstInput];

    uint16_t a = 0, b;

    for(secondInput = 0; secondInput < N; secondInput++)
    {
      for(thirdInput =0; thirdInput < N; thirdInput++){
        for(fourthInput = 0; fourthInput < N; fourthInput++){
          a = (fun_prev.bit_slice[secondInput] & fun_prev.bit_slice[thirdInput] & fun_prev.bit_slice[fourthInput]) ^ fun_prev.bit_slice[firstInput];  

          if(!reverse) b = f.bit_slice[f.info_line];
          else b = f.prev;
          if(a == b) break;
        }
        if(a == b) break;
      }
      if(a == b) break;
    }
      
       if(costs[secondInput] > maxInputCost){
      maxInputCost = costs[secondInput];
    }
    if(costs[thirdInput] > maxInputCost){
      maxInputCost = costs[thirdInput];
    }
    if(costs[fourthInput] > maxInputCost){
      maxInputCost = costs[fourthInput];
    }
    costs[firstInput] = maxInputCost+(cost(81)/100);
    costs[secondInput] = maxInputCost+(cost(81)/100);
    costs[thirdInput] = maxInputCost+(cost(81)/100);
    costs[fourthInput] = maxInputCost+(cost(81)/100);

    maxInputCost = tcosts[firstInput];
    if(tcosts[secondInput] > maxInputCost){
      maxInputCost = tcosts[secondInput];
    }
    if(tcosts[thirdInput] > maxInputCost){
      maxInputCost = tcosts[thirdInput];
    }
    if(tcosts[fourthInput] > maxInputCost){
      maxInputCost = tcosts[fourthInput];
    }
    tcosts[firstInput] = maxInputCost+(tcost(81)/100);
    tcosts[secondInput] = maxInputCost+(tcost(81)/100);
    tcosts[thirdInput] = maxInputCost+(tcost(81)/100);
    tcosts[fourthInput] = maxInputCost+(tcost(81)/100);
    break;
    }
  }
  return;
} 

void get_string_impl(string *s, function_t f, bool reverse, bool qiskit)
{
  
  //costs[f.info_line] += bool_op_cost(f.info_op);
  //make a stack, holding pairs of lines & costs to add in order?
  if( !reverse ){
   // s->insert(0, "Info_Op:  " + to_string(f.info_op) + ", Info_Line: " + to_string(f.info_line) + ", Op_Cost: " + to_string(((double)(bool_op_cost(f.info_op)))/100) + ", Line Cost: " + to_string(((double)(costs[f.info_line]))/100) + "\n\n");
    s->insert(0, bool_op_to_string(f, f.info_op, reverse, qiskit));
    st.push(f);
    
  } 
  else{
    //use the stack to add the reversed gates from first gate -> last gate.
  s->append(bool_op_to_string(f, f.info_op, reverse, qiskit));
  //*s = *s + "Info_Op:  " + to_string(f.info_op) + ", maxInput: " + to_string(maxInputCost) + ", Info_Line: " + to_string(f.info_line) + ", Op_Cost: " + to_string(((double)(bool_op_cost(f.info_op)))/100) + ", Line Cost: " + to_string(((double)(costs[f.info_line]))/100) + "\n\n";
  q.push(f); 
    
  }

}

//change what this returns to be T-depth, not gate costs.
void get_semi_impl(function_t f,
                    int count_vlist,
                    map<int, set<function_t> > *g,
                    string *s,
                    bool reverse, bool qiskit=false)
{

  int cost = bool_op_cost(f.info_op);
  //cout << "here " << endl;
  auto found = g->at(0).find(f);
  unsorted_function = f;
  while(count_vlist >= 0)
  {
    update_unsorted_function(f);
    get_string_impl(s, unsorted_function, reverse, qiskit);
    if(qiskit){
      //prevent redundancy
      gatecount = gatecount + 1;
    }
    
    f.bit_slice[f.info_line] = f.prev;
    f.sort();
    count_vlist -= bool_op_cost(f.info_op);
    if( count_vlist <= 0) break;
    if( count_vlist % 100 != 0 && !tdepmode) break;
    //cout << count_vlist << " " << g->size() << endl;
    found = g->at(count_vlist).find(f);
    //hashes a set of boolean operations keyed with a value of count_vlist
    f = *found;
    cost += bool_op_cost(f.info_op);
    
    //f.info_op states what gate it is.
    //f.prev = the line which was in the previous function
    //f.info_line = index of changed line
  }

  unsorted_function.bit_slice[unsorted_function.info_line] = unsorted_function.prev;

//stores the printed out info to be printed later
//bruh just use the printed info to calculate cost? lmao
  if( !reverse )
  {
    s->insert(0, "\n" + get_permut(start, unsorted_function, 'F', 'X', qiskit) + "\n", qiskit);
    if(qiskit){
      s->insert(0, "# from : " + start.to_string() + "\n");
    }else{
    s->insert(0, "// from : " + start.to_string() + "\n");
    }
  }
  else
  {
    s->append("\n" + get_permut(unsorted_function, unsorted_arrival, 'X', 'F', qiskit) + "\n", qiskit);
    if(qiskit){
    s->append("# to : " + unsorted_arrival.to_string() + "\n");  
    }else{
    s->append("// to : " + unsorted_arrival.to_string() + "\n");
    }
  }
}

void get_implementation(function_t f1,
                      function_t f2,
                      int v,
                      map<int, set<function_t> > *g1,
                      map<int, set<function_t> > *g2)
{
  static int impl_number = 0;
  gatecount = 0;
  string s1, s2;
  if(g1 == &f1_succ)
  {
    get_semi_impl(f1, count_list+bool_op_cost(f1.info_op), g1, &s1, false, true);
    get_semi_impl(f2, v, g2, &s2, true, true);
    while(!st.empty()){
      getMax(st.top(), true);
      st.pop();  
    }
    while(!q.empty()){
      getMax(q.front(), false);
      q.pop();  
    }
  }
  else
  {
    get_semi_impl(f1, count_list+bool_op_cost(f1.info_op), g1, &s1, true, true);
    get_semi_impl(f2, v, g2, &s2, false, true);
    while(!st.empty()){
      getMax(st.top(), false);
      st.pop();  
    }
    while(!q.empty()){
      getMax(q.front(), true);
      q.pop();  
    }
  }
  depth = costs[0];
    for(int i=0; i<4; i++){
      if(costs[i] > depth){
        depth = costs[i];
      }
      costs[i] = 0;
    }
  tdepth = tcosts[0];
    for(int i=0; i<4; i++){
      if(tcosts[i] > tdepth){
        tdepth = tcosts[i];
      }
      tcosts[i] = 0;
    }
  unsorted_function.sort();
  if((!tdepmode && (depth < shortest_path || (depth == shortest_path && tdepth < tdepthrec) || (depth == shortest_path && tdepth == tdepthrec && gatecount < gatecountrec))) || (tdepmode && (tdepth < tdepthrec || (tdepth == tdepthrec && depth < shortest_path) || (tdepth == tdepthrec && depth == shortest_path && gatecount < gatecountrec))))
  {
    cout << "Generating implementation " << impl_number << endl;
    gatecountrec = gatecount;
    tdepthrec = tdepth;
    shortest_path = depth;
    ofstream qis("impqiskit" + implementation_id + to_string(impl_number) + ".py");
    bool x = false;
    if(unsorted_function == start){
      x = true;
    } 
    if(x) qis << s2 << s1;
    else qis << s1 << s2;
    qis << "# T-Depth : " << (double)(tdepth) << endl;
    qis << "# Depth : " << (double)(depth) << endl;
    qis << "# Gate Count : " << (double)(gatecount) << endl;
     
    qis.close();

    string t1, t2;
    if(g1 == &f1_succ)
    {
      get_semi_impl(f1, count_list+bool_op_cost(f1.info_op), g1, &t1, false);
      get_semi_impl(f2, v, g2, &t2, true);
      while(!st.empty()){
        getMax(st.top(), true);
        st.pop();  
      }
      while(!q.empty()){
        getMax(q.front(), false);
        q.pop();  
      }
    }
    else
    {
      get_semi_impl(f1, count_list+bool_op_cost(f1.info_op), g1, &t1, true);
      get_semi_impl(f2, v, g2, &t2, false);
      while(!st.empty()){
        getMax(st.top(), false);
        st.pop();  
      }
      while(!q.empty()){
        getMax(q.front(), true);
        q.pop();  
      }
    }
    ofstream impl("implementation" + implementation_id + to_string(impl_number) + ".c");
    if(x) impl << t2 << t1;
    else impl << t1 << t2;
    impl << "// T-Depth : " << (double)(tdepth) << endl;
    impl << "// Depth : " << (double)(depth) << endl;
    impl << "// Gate Count : " << (double)(gatecount) << endl;
     
    impl.close();
    unsorted_function.sort();

    impl_number ++;
 }

}