//# QuantumHolder.h: A holder for Quantities to enable record conversions
//# Copyright (C) 1998
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#if !defined(AIPS_QUANTUMHOLDER_H)
#define AIPS_QUANTUMHOLDER_H

//# Includes
#include <aips/aips.h>
#include <aips/Utilities/PtrHolder.h>
#include <aips/Utilities/RecordTransformable.h>
#include <aips/Mathematics/Complex.h>

//# Forward Declarations
class QBase;
class String;
class RecordInterface;
class GlishRecord;
template <class Qtype> class Quantum;
template <class T> class Vector;

// <summary> A holder for Quantums to enable record conversions </summary>

// <use visibility=export>

// <reviewed reviewer="" date="yyyy/mm/dd" tests="tQuantumHolder" demos="">
// </reviewed>

// <prerequisite>
//   <li> <linkto class=RecordInterface>RecordInterface</linkto> class
//   <li> <linkto class=GlishRecord>GlishRecord</linkto> class
//   <li> <linkto class=Quantum>Quantity</linkto> class
// </prerequisite>
//
// <etymology>
// A Holder of general Quantums
// </etymology>
//
// <synopsis>
// This class can be used to handle a heterogeneous list of Quantums, and
// can handle toRecord() and fromRecord() conversions.
// A QuantumHolder
// is created empty, from a Quantum (e.g. a <src>Quantum<Double></src>) or a
// <src>Quantum<Vector<Float> ></src>).
//
// The accepted range of Quantums is:
// <ul>
//  <li> <src>Quantum<Int>, Quantum<Float>, Quantum<Double> == Quantity</src>
//  <li> <src>Quantum<Complex>, Quantum<DComplex></src>
//  <li> <src>Quantum<Vector<Int> >, Quantum<Vector<Float> ></src>, 
//	 <src>Quantum<Vector<Double> ></src>
//  <li> <src>Quantum<Vector<Complex> >, Quantum<Vector<DComplex> ></src>
// </ul>
// Scalars in the same group can be converted to any in the same group (e.g.
// Int to Double); Vectors of length 1 can be converted to scalars in the 
// corresponding group; Scalars can always be converted to Vectors in the 
// corresponding group. Real scalar values can be converted to Complex values.
// Vectors cannot be converted to other type vectors.
//
// Checks on the contents can be made with functions like
// <src>isQuantity</src> and the contents can be obtained with
// functions like <src>asQuantity</src>. It is an error to try and
// retrieve a Quantum of the wrong type and doing so will generate an
// exception (AipsError).
// </synopsis>
//
// <example>
// <srcblock>
//	TableRecord rec;		// an empty record
//	Quantity x(12.5, "km/s");	// a Quantity
//	String error;			// an error message
//	if (!QuantumHolder(x).toRecord(error, rec)) {  // make record
//		cout << error << endl;
//	};
//	GlishRecord grec;		// a GlishRecord
//	if (!QuantumHolder(x).toRecord(error, grec)) {  // make record
//		cout << error << endl;
//	};
// // Note that for GlishRecords use can be made of the to/fromGlishrecord()
// // methods	
// </srcblock>
// </example>
//
// <motivation>
// To make general conversions between Quantums and records, without knowing
// the actual Quantum being converted.
// </motivation>
//
// <todo asof="1998/04/14">
//   <li> possible change if GlishRecord derived from RecordInterface
// </todo>

class QuantumHolder : public RecordTransformable {

public:

//# Friends

//# Enumerations

//# Constructors
  // Creates an empty holder
  QuantumHolder();
  // Create from a Quantum (copy semantics)
  QuantumHolder(const QBase &in);
  // Copy a holder (copy semantics)
  QuantumHolder(const QuantumHolder &other);
//# Destructor
  ~QuantumHolder();

//# Operators
  // Assignment (copy semantics)
  QuantumHolder &operator=(const QuantumHolder &other);

//# Member Functions
  // Check if it holds a Quantity. Note that a Vector of length 1 will give
  // True to scalar questions.
  // <group>
  Bool isEmpty() const;
  Bool isQuantum() const;
  Bool isScalar() const;
  Bool isArray() const;
  Bool isReal() const;
  Bool isComplex() const;
  Bool isQuantity() const;
  Bool isQuantumDouble() const;
  Bool isQuantumFloat() const;
  Bool isQuantumInt() const;
  Bool isQuantumComplex() const;
  Bool isQuantumDComplex() const;
  Bool isQuantumVectorDouble() const;
  Bool isQuantumVectorFloat() const;
  Bool isQuantumVectorInt() const;
  Bool isQuantumVectorComplex() const;
  Bool isQuantumVectorDComplex() const;
  // </group>
  // Get number of numeric elements (1 if scalar, else
  // vector length)
  // <thrown>
  //  <li> AipsError if holder empty
  // </thrown>
  Int nelements() const;

  // Get a Quantum from the holder (with lifetime as long 
  // as holder exists). Conversions done if necessary and as described in
  // introduction.
  // <thrown>
  // <li> AipsError if holder empty or no conversion possible
  // </thrown>
  // <group>
  const QBase &asQuantum() const;
  const Quantum<Double> &asQuantity() ;
  const Quantum<Double> &asQuantumDouble() ;
  const Quantum<Float> &asQuantumFloat() ;
  const Quantum<Int> &asQuantumInt() ;
  const Quantum<Complex> &asQuantumComplex() ;
  const Quantum<DComplex> &asQuantumDComplex() ;
  const Quantum<Vector<Double> > &asQuantumVectorDouble() ;
  const Quantum<Vector<Float> > &asQuantumVectorFloat() ;
  const Quantum<Vector<Int> > &asQuantumVectorInt() ;
  const Quantum<Vector<Complex> > &asQuantumVectorComplex() ;
  const Quantum<Vector<DComplex> > &asQuantumVectorDComplex() ;
  // </group>

  // Create a Quantum from a record
  // A valid record will contain the following fields:
  // <ul>
  //  <li> value: contains a numeric value of Int, Float, Double, Complex,
  //		DComplex or a vector thereof
  //  <li> unit: a string with a unit valid.
  // </ul>
  // Illegal values or units will return False and write an error message.
  // <group>
  virtual Bool fromRecord(String &error, const RecordInterface &in);
  Bool fromRecord(String &error, const GlishRecord &in);
  // </group>
  // Create a record from a Quantum. A False return and an error message is
  // only generated if there is no valid Quantum in the holder.
  // <group>
  virtual Bool toRecord(String &error, RecordInterface &out) const;
  Bool toRecord(String &error, GlishRecord &out) const;
  // </group>

private:

//# Data Members
  // Pointer to a Quantity
  PtrHolder<QBase> hold_p;

//# General member functions
  // Convert to a different real scalar quantum
  void toReal(const uInt &tp);
  // Convert to a different complex scalar quantum
  void toComplex(const uInt &tp);
  // Convert scalar to Array
  void toVector();
};

#endif
