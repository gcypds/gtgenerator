// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "labels.hxx"

// gtlabels
// 

const gtlabels::label_sequence& gtlabels::
label () const
{
  return this->label_;
}

gtlabels::label_sequence& gtlabels::
label ()
{
  return this->label_;
}

void gtlabels::
label (const label_sequence& s)
{
  this->label_ = s;
}

const gtlabels::fversion_optional& gtlabels::
fversion () const
{
  return this->fversion_;
}

gtlabels::fversion_optional& gtlabels::
fversion ()
{
  return this->fversion_;
}

void gtlabels::
fversion (const fversion_type& x)
{
  this->fversion_.set (x);
}

void gtlabels::
fversion (const fversion_optional& x)
{
  this->fversion_ = x;
}

void gtlabels::
fversion (::std::auto_ptr< fversion_type > x)
{
  this->fversion_.set (x);
}


// label
// 

const label::id_optional& label::
id () const
{
  return this->id_;
}

label::id_optional& label::
id ()
{
  return this->id_;
}

void label::
id (const id_type& x)
{
  this->id_.set (x);
}

void label::
id (const id_optional& x)
{
  this->id_ = x;
}

const label::name_optional& label::
name () const
{
  return this->name_;
}

label::name_optional& label::
name ()
{
  return this->name_;
}

void label::
name (const name_type& x)
{
  this->name_.set (x);
}

void label::
name (const name_optional& x)
{
  this->name_ = x;
}

void label::
name (::std::auto_ptr< name_type > x)
{
  this->name_.set (x);
}

const label::color_optional& label::
color () const
{
  return this->color_;
}

label::color_optional& label::
color ()
{
  return this->color_;
}

void label::
color (const color_type& x)
{
  this->color_.set (x);
}

void label::
color (const color_optional& x)
{
  this->color_ = x;
}

void label::
color (::std::auto_ptr< color_type > x)
{
  this->color_.set (x);
}

const label::removed_optional& label::
removed () const
{
  return this->removed_;
}

label::removed_optional& label::
removed ()
{
  return this->removed_;
}

void label::
removed (const removed_type& x)
{
  this->removed_.set (x);
}

void label::
removed (const removed_optional& x)
{
  this->removed_ = x;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// gtlabels
//

gtlabels::
gtlabels ()
: ::xml_schema::type (),
  label_ (this),
  fversion_ (this)
{
}

gtlabels::
gtlabels (const gtlabels& x,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  label_ (x.label_, f, this),
  fversion_ (x.fversion_, f, this)
{
}

gtlabels::
gtlabels (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f,
          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  label_ (this),
  fversion_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, true);
    this->parse (p, f);
  }
}

void gtlabels::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // label
    //
    if (n.name () == "label" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< label_type > r (
        label_traits::create (i, f, this));

      this->label_.push_back (r);
      continue;
    }

    break;
  }

  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "fversion" && n.namespace_ ().empty ())
    {
      this->fversion_.set (fversion_traits::create (i, f, this));
      continue;
    }
  }
}

gtlabels* gtlabels::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class gtlabels (*this, f, c);
}

gtlabels& gtlabels::
operator= (const gtlabels& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->label_ = x.label_;
    this->fversion_ = x.fversion_;
  }

  return *this;
}

gtlabels::
~gtlabels ()
{
}

// label
//

label::
label ()
: ::xml_schema::string (),
  id_ (this),
  name_ (this),
  color_ (this),
  removed_ (this)
{
}

label::
label (const char* _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  id_ (this),
  name_ (this),
  color_ (this),
  removed_ (this)
{
}

label::
label (const ::std::string& _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  id_ (this),
  name_ (this),
  color_ (this),
  removed_ (this)
{
}

label::
label (const ::xml_schema::string& _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  id_ (this),
  name_ (this),
  color_ (this),
  removed_ (this)
{
}

label::
label (const label& x,
       ::xml_schema::flags f,
       ::xml_schema::container* c)
: ::xml_schema::string (x, f, c),
  id_ (x.id_, f, this),
  name_ (x.name_, f, this),
  color_ (x.color_, f, this),
  removed_ (x.removed_, f, this)
{
}

label::
label (const ::xercesc::DOMElement& e,
       ::xml_schema::flags f,
       ::xml_schema::container* c)
: ::xml_schema::string (e, f | ::xml_schema::flags::base, c),
  id_ (this),
  name_ (this),
  color_ (this),
  removed_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, false, true);
    this->parse (p, f);
  }
}

void label::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "id" && n.namespace_ ().empty ())
    {
      this->id_.set (id_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "name" && n.namespace_ ().empty ())
    {
      this->name_.set (name_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "color" && n.namespace_ ().empty ())
    {
      this->color_.set (color_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "removed" && n.namespace_ ().empty ())
    {
      this->removed_.set (removed_traits::create (i, f, this));
      continue;
    }
  }
}

label* label::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class label (*this, f, c);
}

label& label::
operator= (const label& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::string& > (*this) = x;
    this->id_ = x.id_;
    this->name_ = x.name_;
    this->color_ = x.color_;
    this->removed_ = x.removed_;
  }

  return *this;
}

label::
~label ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::gtlabels >
gtlabels_ (const ::std::string& u,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (const ::std::string& u,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (const ::std::string& u,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtlabels_ (isrc, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtlabels_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtlabels_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           const ::std::string& sid,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtlabels_ (isrc, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           const ::std::string& sid,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtlabels_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::std::istream& is,
           const ::std::string& sid,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtlabels_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::xercesc::InputSource& i,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::xercesc::InputSource& i,
           ::xml_schema::error_handler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::xercesc::InputSource& i,
           ::xercesc::DOMErrorHandler& h,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtlabels > (
    ::gtlabels_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (const ::xercesc::DOMDocument& doc,
           ::xml_schema::flags f,
           const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::auto_ptr< ::gtlabels > (
      ::gtlabels_ (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "gtlabels" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::gtlabels > r (
      ::xsd::cxx::tree::traits< ::gtlabels, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "gtlabels",
    "");
}

::std::auto_ptr< ::gtlabels >
gtlabels_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d,
           ::xml_schema::flags f,
           const ::xml_schema::properties&)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "gtlabels" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::gtlabels > r (
      ::xsd::cxx::tree::traits< ::gtlabels, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "gtlabels",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

