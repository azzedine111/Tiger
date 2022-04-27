/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e) {
    ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    ostr_ << e.var_get() << "." << e.name_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }


  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // FIXME: Some code was deleted here.
  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << '"' << misc::escape(e.string_get()) << '"';
  }

  void PrettyPrinter::operator()(const NilExp& e) { ostr_ << "nil"; }
  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get() << '(';
    auto args = e.args_get();
    for (int k = 0; k < args.size(); k++)
      {
        if (k != 0){
            ostr_ << ", " << *args[k];
          }
        else
          ostr_ << *args[0];

      }

    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
    PrettyPrinter::operator()(e.left_get());
    ostr_ << ' ';
    ostr_ << str(e.oper_get());
    ostr_ << ' ';
    PrettyPrinter::operator()(e.right_get());
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.type_name_get() << " { ";
    auto field = e.fields_get();
    for (int k = 0; k < field.size(); k++)
      {
        if (k != 0)
          ostr_ << ", " << field[k]->name_get() << " = " << field[k]->init_get();
        else
          ostr_ << field[k]->name_get() << " = " << field[k]->init_get();
      }
    ostr_ << " }";
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    if (&e.exps_get() == nullptr)
      {
        ostr_ << "()";
        return;
      }
    auto exps = e.exps_get();
    ostr_ << "(";
    misc::incindent(ostr_);
    for (int k = 0; k < exps.size(); k++)
      {
        if (k != exps.size() - 1)
          {
            misc::iendl(ostr_);
            exps[k]->accept(*this);
            if (exps.size() > 1)
              ostr_ << ";";
          }
        else
          {
            misc::iendl(ostr_);
            exps[k]->accept(*this);
          }
      }
    misc::decendl(ostr_);
    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get();
  }

  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "(if (";
    PrettyPrinter::operator()(e.test_get());
    ostr_ << ')';
    misc::incindent(ostr_);
    misc::iendl(ostr_);
    ostr_ << "then (";
    PrettyPrinter::operator()(e.thenclause_get());
    ostr_ << ")";
    if (e.elseclause_get() != nullptr)
      {
        misc::iendl(ostr_);
        ostr_ << "else (";
        PrettyPrinter::operator()(e.elseclause_get());
        ostr_ << ')';
      }
    ostr_ << ')';
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while " << e.test_get() << " do";
    misc::incendl(ostr_);
    ostr_ << e.body_get();
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for ";
    ostr_ << e.vardec_get().name_get() << " := ";
    PrettyPrinter::operator()(e.vardec_get().init_get());
    ostr_ << " to ";
    PrettyPrinter::operator()(e.hi_get());
    ostr_ << " do ";
    PrettyPrinter::operator()(e.body_get());
  }

  void PrettyPrinter::operator()(const BreakExp& e) { ostr_ << "break"; }

  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let";
    misc::incendl(ostr_);
    PrettyPrinter::operator()(e.decs_get());
    misc::resetindent(ostr_);
    misc::incindent(ostr_);
    misc::incendl(ostr_);
    ostr_ << "in";
    misc::iendl(ostr_);
    PrettyPrinter::operator()(e.body_get());
    misc::iendl(ostr_);
    ostr_<< "end";
  }

  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.type_name_get().name_get()  << " [" << e.size_get() << ']';
    if (e.init_get() != nullptr)
      {
        ostr_ << " of ";
        PrettyPrinter::operator()(e.init_get());
      }
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << "var " << e.name_get() << " := " << e.init_get();
  }

  void PrettyPrinter::operator()(const ChunkList& e)
  {
    auto chunks = e.chunks_get();
    auto it = chunks.begin();
    while (it != chunks.end())
      {
        if (it != chunks.begin())
          {
            misc::iendl(ostr_);
          }
        PrettyPrinter::operator()(*it);
        it++;
      }
  }
/*
  void PrettyPrinter::operator()(const ChunkType& e)
  {
    //?
  }
  */

  void PrettyPrinter::operator()(const VarChunk& e)
  {
    auto vars = e.decs_get();
    for (int k = 0; k < vars.size(); k++)
      {
        PrettyPrinter::operator()(vars[k]);
      }
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    if (e.type_name_get() != nullptr)
      ostr_ << "var " << e.name_get() << " : " << e.type_name_get()->name_get() << " := ";
    else
      {
        ostr_ << "var " << e.name_get() << " := ";
      }
    if (e.init_get() != nullptr)
      {
        PrettyPrinter::operator()(e.init_get());
      }
  }

  void PrettyPrinter::operator()(const FunctionChunk& e)
  {
    auto functions = e.decs_get();
    for (int k = 0; k < functions.size(); k++)
      {
        if (functions[k])
          {
            PrettyPrinter::operator()(functions[k]);
          }
      }
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    if (e.body_get() != nullptr)
      ostr_ << "function " << e.name_get() << "(";
    else
      ostr_ << "primitive " << e.name_get() << "(";
    auto vars = e.formals_get().decs_get();
    for (int k = 0; k < vars.size(); k++)
      {
        if (k != 0)
          ostr_ << ", " << vars[k]->name_get() << " : " << vars[k]->type_name_get()->name_get();
        else
          {
            ostr_ << vars[k]->name_get() << " : " << vars[k]->type_name_get()->name_get();
          }
      }
    ostr_ << ")";
    if (e.result_get() != nullptr)
      {
        ostr_ << " : " << e.result_get()->name_get();
      }

    if (e.body_get() != nullptr)
      {
        ostr_ << " =";
        misc::incindent(ostr_);
        misc::iendl(ostr_);
        PrettyPrinter::operator()(e.body_get());
      }
    else
      misc::iendl(ostr_);
  }

  void PrettyPrinter::operator()(const TypeChunk& e)
  {
    auto type = e.decs_get();
    for (int k = 0; k < type.size(); k++)
      {
        if (k != 0)
          misc::iendl(ostr_);
        PrettyPrinter::operator()(type[k]);
      }
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get().name_get();
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << "{ ";
    auto field = e.fields_get();
    for (int k = 0; k < field.size(); k++)
      {
        if (k != 0)
          ostr_ << ", " << field[k]->name_get() << " : " << field[k]->type_name_get();
        else
          ostr_ << field[k]->name_get() << " : " << field[k]->type_name_get();
      }
    ostr_ << " }";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get() << " = " << e.ty_get();

  }



  void PrettyPrinter::operator()(const Field& e){}

  void PrettyPrinter::operator()(const MethodChunk& e)
  {
    auto methods = e.decs_get();
    for (int k = 0; k < methods.size(); k++)
      {
        PrettyPrinter::operator()(methods[k]);
      }
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << "method " << e.name_get() << '(';
    auto vars = e.formals_get().decs_get();
    for (int k = 0; k < vars.size(); k++)
      {
        if (k != 0)
          ostr_ << ", " << vars[k]->name_get() << ' : ' << vars[k]->type_name_get();
        else
          ostr_ << vars[k]->name_get() << ': ' << vars[k]->type_name_get();
      }
    ostr_ << ") = (" << e.body_get() << ")";
  }


  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.object_get() << " " << e.name_get() << "(";
    auto exps = e.exps_get();
    for (int k = 0; k < exps.size(); k++)
      {
        if (k != 0)
          ostr_ << ", " << exps[k];
        else
          ostr_ << exps[k];
      }
    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << e.type_name_get().name_get();
  }




} // namespace ast
