//! \file nonlocal_diffusion.h

//@HEADER
// ************************************************************************
//
//                             Peridigm
//                 Copyright (2011) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions?
// David J. Littlewood   djlittl@sandia.gov
// John A. Mitchell      jamitch@sandia.gov
// Michael L. Parks      mlparks@sandia.gov
// Stewart A. Silling    sasilli@sandia.gov
//
// ************************************************************************
//@HEADER
#ifndef DIFFUSION_H
#define DIFFUSION_H

namespace MATERIAL_EVALUATION {

//! Computes contributions to the internal force resulting from owned points.
template<typename ScalarT>
void computeInternalFluidFlow
(
    const double*  xOverlap,
    const ScalarT* yOverlap,
    const ScalarT* fluidPressureYOverlap,
    const double* volumeOverlap,
    const double* bondDamage,
    ScalarT* flowInternalOverlap,
    const int*  localNeighborList,
    int numOwnedPoints,
    double isotropicPermeabilityModulus,
    double isotropicPermeabilityPoissons,
    double fluidDensity,
    double baseDynamicViscosity,
    double permeabilityInflectionDamage,
    double permeabilityAlpha,
    double maxPermeability,
    double horizon,
    double ReynoldsThermalViscosityCoefficient = 0.0,
    const double* deltaTemperature = 0
);

//! Computes contributions to the internal force resulting from owned points.
template<typename ScalarT>
void computeInternalForceLinearElasticCoupled
(
    const double* xOverlap,
    const ScalarT* yOverlap,
    const ScalarT* fluidPressureYOverlap,
    const double* mOwned,
    const double* volumeOverlap,
    const ScalarT* dilatationOwned,
    const double* bondDamage,
    const double* dsfOwned,
    ScalarT* fInternalOverlap,
    const int*  localNeighborList,
    int numOwnedPoints,
    double BULK_MODULUS,
    double SHEAR_MODULUS,
    double horizon,
    double thermalExpansionCoefficient = 0.0,
    const double* deltaTemperature = 0
);

//! Computes contributions to the internal force resulting from owned points.
template<typename ScalarT>
void computeInternalFluidFlowDeadSimple
(
    const double*  xOverlap,
     const ScalarT* yOverlap,
    const ScalarT* fluidPressureYOverlap,
    const double* volumeOverlap,
    const double* bondDamage,
    ScalarT* flowInternalOverlap,
    const int*  localNeighborList,
    int numOwnedPoints,
    double isotropicPermeabilityModulus,
    double isotropicPermeabilityPoissons,
    double fluidDensity,
    double baseDynamicViscosity,
    double permeabilityInflectionDamage,
    double permeabilityAlpha,
    double maxPermeability,
    double horizon,
    double ReynoldsThermalViscosityCoefficient = 0.0,
    const double* deltaTemperature = 0
);

//! Computes contributions to the internal force resulting from owned points.
template<typename ScalarT>
void computeInternalForceLinearElasticCoupledDeadSimple
(
    const double* xOverlap,
    const ScalarT* yOverlap,
    const ScalarT* fluidPressureYOverlap,
    const double* mOwned,
    const double* volumeOverlap,
    const ScalarT* dilatationOwned,
    const double* bondDamage,
    const double* dsfOwned,
    ScalarT* fInternalOverlap,
    const int*  localNeighborList,
    int numOwnedPoints,
    double BULK_MODULUS,
    double SHEAR_MODULUS,
    double horizon,
    double thermalExpansionCoefficient = 0.0,
    const double* deltaTemperature = 0
);


}

#endif // DIFFUSION_H
