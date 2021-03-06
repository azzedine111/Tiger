/**
 ** Test the tweast.
 **/

#include <iostream>
#include <ast/chunk-list.hh>
#include <ast/libast.hh>
#include <ast/name-ty.hh>
#include <ast/seq-exp.hh>
#include <ast/simple-var.hh>
#include <misc/contract.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/location.hh>
#include <parse/tweast.hh>

const char* program_name = "test-tweast";

int main()
{
  try
    {
      parse::Tweast in;
      parse::location l;
      ast::Exp* exp = new ast::SeqExp(l, new ast::exps_type);
      ast::Var* var = new ast::SimpleVar(l, "a");
      ast::NameTy* namety = new ast::NameTy(l, "int");
      ast::ChunkList* chunks = new ast::ChunkList(l);

      in << chunks << " function f(a :" << namety << ") : " << namety << " = ("
         << exp << "; " << var << ")";

      assertion(chunks == in.take<ast::ChunkList>(0));
      assertion(namety == in.take<ast::NameTy>(1));
      assertion(namety == in.take<ast::NameTy>(2));
      assertion(exp == in.take<ast::Exp>(3));
      assertion(var == in.take<ast::Var>(4));

      delete exp;
      delete var;
      delete namety;
      delete chunks;
    }
  catch (const misc::error& e)
    {
      std::cerr << e;
      exit(e.status_get_value());
    }
}
