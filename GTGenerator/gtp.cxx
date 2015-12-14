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

#include "gtp.hxx"

// gtproj
// 

const gtproj::proj_sequence& gtproj::
proj () const
{
  return this->proj_;
}

gtproj::proj_sequence& gtproj::
proj ()
{
  return this->proj_;
}

void gtproj::
proj (const proj_sequence& s)
{
  this->proj_ = s;
}

const gtproj::fversion_optional& gtproj::
fversion () const
{
  return this->fversion_;
}

gtproj::fversion_optional& gtproj::
fversion ()
{
  return this->fversion_;
}

void gtproj::
fversion (const fversion_type& x)
{
  this->fversion_.set (x);
}

void gtproj::
fversion (const fversion_optional& x)
{
  this->fversion_ = x;
}

void gtproj::
fversion (::std::auto_ptr< fversion_type > x)
{
  this->fversion_.set (x);
}


// proj
// 

const proj::name_optional& proj::
name () const
{
  return this->name_;
}

proj::name_optional& proj::
name ()
{
  return this->name_;
}

void proj::
name (const name_type& x)
{
  this->name_.set (x);
}

void proj::
name (const name_optional& x)
{
  this->name_ = x;
}

void proj::
name (::std::auto_ptr< name_type > x)
{
  this->name_.set (x);
}

const proj::frame_count_optional& proj::
frame_count () const
{
  return this->frame_count_;
}

proj::frame_count_optional& proj::
frame_count ()
{
  return this->frame_count_;
}

void proj::
frame_count (const frame_count_type& x)
{
  this->frame_count_.set (x);
}

void proj::
frame_count (const frame_count_optional& x)
{
  this->frame_count_ = x;
}

const proj::label_count_optional& proj::
label_count () const
{
  return this->label_count_;
}

proj::label_count_optional& proj::
label_count ()
{
  return this->label_count_;
}

void proj::
label_count (const label_count_type& x)
{
  this->label_count_.set (x);
}

void proj::
label_count (const label_count_optional& x)
{
  this->label_count_ = x;
}

const proj::video_source_path_optional& proj::
video_source_path () const
{
  return this->video_source_path_;
}

proj::video_source_path_optional& proj::
video_source_path ()
{
  return this->video_source_path_;
}

void proj::
video_source_path (const video_source_path_type& x)
{
  this->video_source_path_.set (x);
}

void proj::
video_source_path (const video_source_path_optional& x)
{
  this->video_source_path_ = x;
}

void proj::
video_source_path (::std::auto_ptr< video_source_path_type > x)
{
  this->video_source_path_.set (x);
}

const proj::subsampling_enabled_optional& proj::
subsampling_enabled () const
{
  return this->subsampling_enabled_;
}

proj::subsampling_enabled_optional& proj::
subsampling_enabled ()
{
  return this->subsampling_enabled_;
}

void proj::
subsampling_enabled (const subsampling_enabled_type& x)
{
  this->subsampling_enabled_.set (x);
}

void proj::
subsampling_enabled (const subsampling_enabled_optional& x)
{
  this->subsampling_enabled_ = x;
}

const proj::subsampling_value_optional& proj::
subsampling_value () const
{
  return this->subsampling_value_;
}

proj::subsampling_value_optional& proj::
subsampling_value ()
{
  return this->subsampling_value_;
}

void proj::
subsampling_value (const subsampling_value_type& x)
{
  this->subsampling_value_.set (x);
}

void proj::
subsampling_value (const subsampling_value_optional& x)
{
  this->subsampling_value_ = x;
}

const proj::subsampling_step_optional& proj::
subsampling_step () const
{
  return this->subsampling_step_;
}

proj::subsampling_step_optional& proj::
subsampling_step ()
{
  return this->subsampling_step_;
}

void proj::
subsampling_step (const subsampling_step_type& x)
{
  this->subsampling_step_.set (x);
}

void proj::
subsampling_step (const subsampling_step_optional& x)
{
  this->subsampling_step_ = x;
}

const proj::bgs_iterations_optional& proj::
bgs_iterations () const
{
  return this->bgs_iterations_;
}

proj::bgs_iterations_optional& proj::
bgs_iterations ()
{
  return this->bgs_iterations_;
}

void proj::
bgs_iterations (const bgs_iterations_type& x)
{
  this->bgs_iterations_.set (x);
}

void proj::
bgs_iterations (const bgs_iterations_optional& x)
{
  this->bgs_iterations_ = x;
}

const proj::bgs_loaded_optional& proj::
bgs_loaded () const
{
  return this->bgs_loaded_;
}

proj::bgs_loaded_optional& proj::
bgs_loaded ()
{
  return this->bgs_loaded_;
}

void proj::
bgs_loaded (const bgs_loaded_type& x)
{
  this->bgs_loaded_.set (x);
}

void proj::
bgs_loaded (const bgs_loaded_optional& x)
{
  this->bgs_loaded_ = x;
}

const proj::bgs_computed_optional& proj::
bgs_computed () const
{
  return this->bgs_computed_;
}

proj::bgs_computed_optional& proj::
bgs_computed ()
{
  return this->bgs_computed_;
}

void proj::
bgs_computed (const bgs_computed_type& x)
{
  this->bgs_computed_.set (x);
}

void proj::
bgs_computed (const bgs_computed_optional& x)
{
  this->bgs_computed_ = x;
}

const proj::descriptors_computed_optional& proj::
descriptors_computed () const
{
  return this->descriptors_computed_;
}

proj::descriptors_computed_optional& proj::
descriptors_computed ()
{
  return this->descriptors_computed_;
}

void proj::
descriptors_computed (const descriptors_computed_type& x)
{
  this->descriptors_computed_.set (x);
}

void proj::
descriptors_computed (const descriptors_computed_optional& x)
{
  this->descriptors_computed_ = x;
}

const proj::labels_created_optional& proj::
labels_created () const
{
  return this->labels_created_;
}

proj::labels_created_optional& proj::
labels_created ()
{
  return this->labels_created_;
}

void proj::
labels_created (const labels_created_type& x)
{
  this->labels_created_.set (x);
}

void proj::
labels_created (const labels_created_optional& x)
{
  this->labels_created_ = x;
}

const proj::rois_created_optional& proj::
rois_created () const
{
  return this->rois_created_;
}

proj::rois_created_optional& proj::
rois_created ()
{
  return this->rois_created_;
}

void proj::
rois_created (const rois_created_type& x)
{
  this->rois_created_.set (x);
}

void proj::
rois_created (const rois_created_optional& x)
{
  this->rois_created_ = x;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// gtproj
//

gtproj::
gtproj ()
: ::xml_schema::type (),
  proj_ (this),
  fversion_ (this)
{
}

gtproj::
gtproj (const gtproj& x,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  proj_ (x.proj_, f, this),
  fversion_ (x.fversion_, f, this)
{
}

gtproj::
gtproj (const ::xercesc::DOMElement& e,
        ::xml_schema::flags f,
        ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  proj_ (this),
  fversion_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, true);
    this->parse (p, f);
  }
}

void gtproj::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // proj
    //
    if (n.name () == "proj" && n.namespace_ ().empty ())
    {
      ::std::auto_ptr< proj_type > r (
        proj_traits::create (i, f, this));

      this->proj_.push_back (r);
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

gtproj* gtproj::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class gtproj (*this, f, c);
}

gtproj& gtproj::
operator= (const gtproj& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->proj_ = x.proj_;
    this->fversion_ = x.fversion_;
  }

  return *this;
}

gtproj::
~gtproj ()
{
}

// proj
//

proj::
proj ()
: ::xml_schema::string (),
  name_ (this),
  frame_count_ (this),
  label_count_ (this),
  video_source_path_ (this),
  subsampling_enabled_ (this),
  subsampling_value_ (this),
  subsampling_step_ (this),
  bgs_iterations_ (this),
  bgs_loaded_ (this),
  bgs_computed_ (this),
  descriptors_computed_ (this),
  labels_created_ (this),
  rois_created_ (this)
{
}

proj::
proj (const char* _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  name_ (this),
  frame_count_ (this),
  label_count_ (this),
  video_source_path_ (this),
  subsampling_enabled_ (this),
  subsampling_value_ (this),
  subsampling_step_ (this),
  bgs_iterations_ (this),
  bgs_loaded_ (this),
  bgs_computed_ (this),
  descriptors_computed_ (this),
  labels_created_ (this),
  rois_created_ (this)
{
}

proj::
proj (const ::std::string& _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  name_ (this),
  frame_count_ (this),
  label_count_ (this),
  video_source_path_ (this),
  subsampling_enabled_ (this),
  subsampling_value_ (this),
  subsampling_step_ (this),
  bgs_iterations_ (this),
  bgs_loaded_ (this),
  bgs_computed_ (this),
  descriptors_computed_ (this),
  labels_created_ (this),
  rois_created_ (this)
{
}

proj::
proj (const ::xml_schema::string& _xsd_string_base)
: ::xml_schema::string (_xsd_string_base),
  name_ (this),
  frame_count_ (this),
  label_count_ (this),
  video_source_path_ (this),
  subsampling_enabled_ (this),
  subsampling_value_ (this),
  subsampling_step_ (this),
  bgs_iterations_ (this),
  bgs_loaded_ (this),
  bgs_computed_ (this),
  descriptors_computed_ (this),
  labels_created_ (this),
  rois_created_ (this)
{
}

proj::
proj (const proj& x,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (x, f, c),
  name_ (x.name_, f, this),
  frame_count_ (x.frame_count_, f, this),
  label_count_ (x.label_count_, f, this),
  video_source_path_ (x.video_source_path_, f, this),
  subsampling_enabled_ (x.subsampling_enabled_, f, this),
  subsampling_value_ (x.subsampling_value_, f, this),
  subsampling_step_ (x.subsampling_step_, f, this),
  bgs_iterations_ (x.bgs_iterations_, f, this),
  bgs_loaded_ (x.bgs_loaded_, f, this),
  bgs_computed_ (x.bgs_computed_, f, this),
  descriptors_computed_ (x.descriptors_computed_, f, this),
  labels_created_ (x.labels_created_, f, this),
  rois_created_ (x.rois_created_, f, this)
{
}

proj::
proj (const ::xercesc::DOMElement& e,
      ::xml_schema::flags f,
      ::xml_schema::container* c)
: ::xml_schema::string (e, f | ::xml_schema::flags::base, c),
  name_ (this),
  frame_count_ (this),
  label_count_ (this),
  video_source_path_ (this),
  subsampling_enabled_ (this),
  subsampling_value_ (this),
  subsampling_step_ (this),
  bgs_iterations_ (this),
  bgs_loaded_ (this),
  bgs_computed_ (this),
  descriptors_computed_ (this),
  labels_created_ (this),
  rois_created_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, false, false, true);
    this->parse (p, f);
  }
}

void proj::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  while (p.more_attributes ())
  {
    const ::xercesc::DOMAttr& i (p.next_attribute ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    if (n.name () == "name" && n.namespace_ ().empty ())
    {
      this->name_.set (name_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "frame_count" && n.namespace_ ().empty ())
    {
      this->frame_count_.set (frame_count_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "label_count" && n.namespace_ ().empty ())
    {
      this->label_count_.set (label_count_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "video_source_path" && n.namespace_ ().empty ())
    {
      this->video_source_path_.set (video_source_path_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "subsampling_enabled" && n.namespace_ ().empty ())
    {
      this->subsampling_enabled_.set (subsampling_enabled_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "subsampling_value" && n.namespace_ ().empty ())
    {
      this->subsampling_value_.set (subsampling_value_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "subsampling_step" && n.namespace_ ().empty ())
    {
      this->subsampling_step_.set (subsampling_step_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "bgs_iterations" && n.namespace_ ().empty ())
    {
      this->bgs_iterations_.set (bgs_iterations_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "bgs_loaded" && n.namespace_ ().empty ())
    {
      this->bgs_loaded_.set (bgs_loaded_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "bgs_computed" && n.namespace_ ().empty ())
    {
      this->bgs_computed_.set (bgs_computed_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "descriptors_computed" && n.namespace_ ().empty ())
    {
      this->descriptors_computed_.set (descriptors_computed_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "labels_created" && n.namespace_ ().empty ())
    {
      this->labels_created_.set (labels_created_traits::create (i, f, this));
      continue;
    }

    if (n.name () == "rois_created" && n.namespace_ ().empty ())
    {
      this->rois_created_.set (rois_created_traits::create (i, f, this));
      continue;
    }
  }
}

proj* proj::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class proj (*this, f, c);
}

proj& proj::
operator= (const proj& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::string& > (*this) = x;
    this->name_ = x.name_;
    this->frame_count_ = x.frame_count_;
    this->label_count_ = x.label_count_;
    this->video_source_path_ = x.video_source_path_;
    this->subsampling_enabled_ = x.subsampling_enabled_;
    this->subsampling_value_ = x.subsampling_value_;
    this->subsampling_step_ = x.subsampling_step_;
    this->bgs_iterations_ = x.bgs_iterations_;
    this->bgs_loaded_ = x.bgs_loaded_;
    this->bgs_computed_ = x.bgs_computed_;
    this->descriptors_computed_ = x.descriptors_computed_;
    this->labels_created_ = x.labels_created_;
    this->rois_created_ = x.rois_created_;
  }

  return *this;
}

proj::
~proj ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::auto_ptr< ::gtproj >
gtproj_ (const ::std::string& u,
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

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (const ::std::string& u,
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

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (const ::std::string& u,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtproj_ (isrc, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtproj_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::gtproj_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtproj_ (isrc, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         const ::std::string& sid,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtproj_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::std::istream& is,
         const ::std::string& sid,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::gtproj_ (isrc, h, f, p);
}

::std::auto_ptr< ::gtproj >
gtproj_ (::xercesc::InputSource& i,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (::xercesc::InputSource& i,
         ::xml_schema::error_handler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (::xercesc::InputSource& i,
         ::xercesc::DOMErrorHandler& h,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::auto_ptr< ::gtproj > (
    ::gtproj_ (
      d, f | ::xml_schema::flags::own_dom, p));
}

::std::auto_ptr< ::gtproj >
gtproj_ (const ::xercesc::DOMDocument& doc,
         ::xml_schema::flags f,
         const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::auto_ptr< ::gtproj > (
      ::gtproj_ (
        d, f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "gtproj" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::gtproj > r (
      ::xsd::cxx::tree::traits< ::gtproj, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "gtproj",
    "");
}

::std::auto_ptr< ::gtproj >
gtproj_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d,
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

  if (n.name () == "gtproj" &&
      n.namespace_ () == "")
  {
    ::std::auto_ptr< ::gtproj > r (
      ::xsd::cxx::tree::traits< ::gtproj, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "gtproj",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

