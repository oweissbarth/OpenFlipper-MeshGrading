/*===========================================================================*\
*                                                                            *
*                                 Mesh2HRTF                                  *
*                Copyright (C) 2015 by Harald Ziegelwanger,                  *
*        Acoustics Research Institute, Austrian Academy of Sciences          *
*                        mesh2hrtf.sourceforge.net                           *
*                                                                            *
*--------------------------------------------------------------------------- *
*                                                                            *
*  Mesh2HRTF is licensed under the GNU Lesser General Public License as      *
*  published by the Free Software Foundation, either version 3 of            *
*  the License, or (at your option) any later version.                       *
*                                                                            *
*  Mesh2HRTF is distributed in the hope that it will be useful,              *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
*  GNU Lesser General Public License for more details.                       *
*                                                                            *
*  You should have received a copy of the GNU LesserGeneral Public           *
*  License along with Mesh2HRTF. If not, see                                 *
*  <http://www.gnu.org/licenses/lgpl.html>.                                  *
*                                                                            *
*  If you use Mesh2HRTF:                                                     *
*  - Provide credits:                                                        *
*    "Mesh2HRTF, H. Ziegelwanger, ARI, OEAW (mesh2hrtf.sourceforge.net)"     *
*  - In your publication, cite both articles:                                *
*    [1] Ziegelwanger, H., Kreuzer, W., and Majdak, P. (2015). "Mesh2HRTF:   *
*        Open-source software package for the numerical calculation of       *
*        head-related transfer functions," in Proceedings of the 22nd        *
*        ICSV, Florence, IT.                                                 *
*    [2] Ziegelwanger, H., Majdak, P., and Kreuzer, W. (2015). "Numerical    *
*        calculation of listener-specific head-related transfer functions    *
*        and sound localization: Microphone model and mesh discretization,"  *
*        The Journal of the Acoustical Society of America, 138, 208-222.     *
*                                                                            *
*  If you use Plugin-MeshGrading:                                            *
*  - In your publication, cite:                                              *
*    [3] Ziegelwanger, H., and Majdak, P., Kreuzer, W. (submitted).          *
*        "A-priori mesh grading for the numerical calculation of the         *
*        head-related transfer functions," Applied Acoustics, , -.           *
*                                                                            *
*============================================================================*
*                                                                            *
*  This file is based on "Plugin-IsotropicRemesher" (OperFlipper)            *
*                                                                            *
*============================================================================*
*                                                                            *
*                              OpenFlipper                                   *
*      Copyright (C) 2001-2014 by Computer Graphics Group, RWTH Aachen       *
*                           www.openflipper.org                              *
*                                                                            *
*--------------------------------------------------------------------------- *
*  OpenFlipper is free software: you can redistribute it and/or modify       *
*  it under the terms of the GNU Lesser General Public License as            *
*  published by the Free Software Foundation, either version 3 of            *
*  the License, or (at your option) any later version with the               *
*  following exceptions:                                                     *
*                                                                            *
*  If other files instantiate templates or use macros                        *
*  or inline functions from this file, or you compile this file and          *
*  link it with other files to produce an executable, this file does         *
*  not by itself cause the resulting executable to be covered by the         *
*  GNU Lesser General Public License. This exception does not however        *
*  invalidate any other reasons why the executable file might be             *
*  covered by the GNU Lesser General Public License.                         *
*                                                                            *
*  OpenFlipper is distributed in the hope that it will be useful,            *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*  GNU Lesser General Public License for more details.                       *
*                                                                            *
\*===========================================================================*/

#ifndef MESHGRADING_HH
#define MESHGRADING_HH
#include "ProgressEmitter.hh"


template< class MeshT >
class MeshGrading{

public:

  MeshGrading(ProgressEmitter* _prgEmt = NULL) : prgEmt_(_prgEmt)  {};
  ~MeshGrading() {};

  void grading( MeshT& _mesh, const double _minEdgeLengthGlobal, const double _maxEdgeLengthGlobal, const unsigned int _ear, const unsigned int _gradingFunction, const double _gradingOrder );

private:

  void splitLongEdges( MeshT& _mesh, const double _minEdgeLengthGlobal, const double _maxEdgeLengthGlobal, const typename MeshT::Point earVertexLeft, const typename MeshT::Point earVertexRight, const unsigned int _ear, const unsigned int _gradingFunction, const double _gradingOrder);

  void collapseShortEdges( MeshT& _mesh, const double _minEdgeLengthGlobal, const double _maxEdgeLengthGlobal, const typename MeshT::Point earVertexLeft, const typename MeshT::Point earVertexRight, const unsigned int _ear, const unsigned int _gradingFunction, const double _gradingOrder);

  void equalizeValences( MeshT& _mesh );

  double compute_distance(const typename MeshT::Point vec_midpoint, const unsigned int _ear,const typename MeshT::Point earVertex, const typename MeshT::Point earVertexLeft, const typename MeshT::Point earVertexRight);

  inline
  int targetValence( MeshT& _mesh, const typename MeshT::VertexHandle& _vh );

  void tangentialRelaxation( MeshT& _mesh );

  template <class SpatialSearchT>
  typename MeshT::Point
  findNearestPoint(const MeshT&                   _mesh,
                   const typename MeshT::Point&   _point,
                   typename MeshT::FaceHandle&    _fh,
                   SpatialSearchT*                _ssearch,
                   double*                        _dbest);

  OpenMeshTriangleBSPT< MeshT >* getTriangleBSP(MeshT& _mesh);

  template< class SpatialSearchT >
  void projectToSurface( MeshT& _mesh, MeshT& _original, SpatialSearchT* _ssearch );

  inline
  bool isBoundary( MeshT& _mesh, const typename MeshT::VertexHandle& _vh);

  inline
  bool isFeature( MeshT& _mesh, const typename MeshT::VertexHandle& _vh);

  private:
    ProgressEmitter* prgEmt_;
};

//=============================================================================
#if defined(INCLUDE_TEMPLATES) && !defined(MESHGRADING_C)
#define MESHGRADING_TEMPLATES
#include "MeshGradingT.cc"
#endif
//=============================================================================
#endif // MESHGRADING_HH defined
//=============================================================================
