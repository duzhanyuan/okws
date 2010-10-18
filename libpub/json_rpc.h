// -*-c++-*-

#include "async.h"
#include "arpc.h"
#include "pub3.h"

//-----------------------------------------------------------------------

class json_XDR_dispatch_t : public v_XDR_dispatch_t {
public:
  ptr<v_XDR_t> alloc (u_int32_t rpcvers, XDR *input);
};

//-----------------------------------------------------------------------

class json_XDR_t : public v_XDR_t {
public:
  json_XDR_t (ptr<v_XDR_dispatch_t> d, XDR *x);
  bool rpc_traverse (u_int32_t &obj);
  bool rpc_traverse (u_int64_t &obj);
  bool rpc_encode (str s);
  bool rpc_decode (str *s);
  bool rpc_traverse (bigint &b);
  void enter_field (const char *f);
  void exit_field (const char *f);
  void enter_array (size_t i);
  void exit_array ();
  void enter_slot (size_t i);
  void exit_slot (size_t i);
  bool enter_pointer (bool &nn);
  bool exit_pointer (bool n);
  bool init_decode (const char *msg, ssize_t sz);
  bool init_decode (str s);
  bool init_decode (ptr<pub3::expr_t> x);
private:
  vec<ptr<pub3::expr_t> > m_stack;
  ptr<pub3::expr_t> m_root;
  str m_payload;
};

//-----------------------------------------------------------------------
