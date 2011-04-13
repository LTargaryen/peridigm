/*! \file PdMaterialUtilities.h */

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

#ifndef PDMATERIALUTILITIES_H_
#define PDMATERIALUTILITIES_H_

#include <functional>
using std::binary_function;

namespace PdMaterialUtilities {

struct ViscoelasticBetaOperator : public binary_function< double, double, double > {
	ViscoelasticBetaOperator(double tau, double tau_b, double delta_t) : c1(tau_b/tau), c2(tau_b/delta_t)  {}
	double operator() (double deviatoric_extension, double delta_ed) const {
		return c1 * (deviatoric_extension - c2 * delta_ed);
	}
	double c1,c2;
};

enum PURE_SHEAR { XY=0, YZ, ZX };

void computeWeightedVolume
(
		const double* xOverlap,
		const double* volumeOverlap,
		double* mOwned,
		int myNumPoints,
		const int* localNeighborList
);

void computeDilatation
(
		const double* xOverlap,
		const double* yOverlap,
		const double* mOwned,
		const double* volumeOverlap,
		const double* bondDamage,
		double* dilatationOwned,
		const int* localNeighborList,
		int numOwnedPoints
);

void computeDilatation
(
		const double* xOverlap,
		const double* yOverlap,
		const double* mOwned,
		const double* volumeOverlap,
		const double* bondDamage,
		double* dilatationOwned,
		const int* ownedIDs,
		const int* localNeighborList,
		int numOwnedPoints
);

void computeInternalForceLinearElastic
(
		const double* xOverlapPtr,
		const double* yOverlapPtr,
		const double* mOwned,
		const double* volumeOverlapPtr,
		const double* dilatationOwned,
		const double* bondDamage,
		double* fInternalOverlapPtr,
		const int*  localNeighborList,
		int numOwnedPoints,
		double BULK_MODULUS,
		double SHEAR_MODULUS
);


void computeInternalForceLinearElastic
(
		const double* xOverlapPtr,
		const double* yOverlapPtr,
		const double* mOwned,
		const double* volumeOverlapPtr,
		const double* dilatationOwned,
		const double* bondDamage,
		double* fInternalOverlapPtr,
		const int*  ownedIDs,
		const int*  localNeighborList,
		int numOwnedPoints,
		double BULK_MODULUS,
		double SHEAR_MODULUS
);

void computeInternalForceIsotropicElasticPlastic
(
		const double* xOverlap,
		const double* yOverlap,
		const double* mOwned,
		const double* volumeOverlap,
		const double* dilatationOwned,
		const double* bondDamage,
		const double* dsfOwned_,
		const double* deviatoricPlasticExtensionStateN,
		double* deviatoricPlasticExtensionStateNp1,
		const double* lambdaN_,
		double* lambdaNP1_,
		double* fInternalOverlap,
		const int*  localNeighborList,
		int numOwnedPoints,
		double BULK_MODULUS,
		double SHEAR_MODULUS,
		double HORIZON,
		double yieldStress
);

void computeInternalForceIsotropicElasticPlastic
(
		const double* xOverlap,
		const double* yOverlap,
		const double* mOwned,
		const double* volumeOverlap,
		const double* dilatationOwned,
		const double* bondDamage,
		const double* dsfOwned,
		const double* deviatoricPlasticExtensionStateN,
		double* deviatoricPlasticExtensionStateNp1,
		const double* lambdaN,
		double* lambdaNP1,
		double* fInternalOverlap,
		const int*  ownedIDs,
		const int*  localNeighborList,
		int numOwnedPoints,
		double BULK_MODULUS,
		double SHEAR_MODULUS,
		double HORIZON,
		double yieldStress
);

void updateGeometry
(
		const double* xOverlap,
		const double* uOverlap,
		const double* velocityOverlap,
		double* yOverlap,
		int overLapLength,
		double dt
);

/**
 * Computes norm of deviatoric force state at a particular point
 * @param numNeigh -- number of neighbors at point
 * @param theta    -- dilatation at point
 * @param neighPtr -- list of neighbors at point
 * @param bondDamage     -- damage parameter for each bond at point
 * @param X              -- original coordinates of point
 * @param Y              -- current coordinates of point
 * @param xOverlap       -- pointer to overlap vector of original coordinates; use this to get neighbor original coordinates
 * @param yOverlap       -- pointer to overlap vector of current coordinates; use this to get neighbor current coordinates
 * @param volumeOverlap  -- pointer to volume overlap vector; use this to get volume of neighboring points
 * @param alpha          -- material property (alpha = 15 mu / m
 * @param OMEGA          -- weight function at point
 */
double computeDeviatoricForceStateNorm
(
		int numNeigh,
		double theta,
		const int *neighPtr,
		const double *bondDamage,
		const double *deviatoricPlasticExtensionState,
		const double *X,
		const double *Y,
		const double *xOverlap,
		const double *yOverlap,
		const double *volumeOverlap,
		double alpha,
		double OMEGA
);

/**
 * Call this function on a single point 'X'
 * NOTE: neighPtr to should point to 'numNeigh' for 'X'
 * and thus describe the neighborhood list as usual
 * NOTE: this function will overwrite entries in 'yOverlap'
 * for all of 'X' neighbors
 * OUTPUT: yOverlap such that there is a state of pure
 * shear at 'X'
 */
void set_pure_shear
(
		const int *neighPtr,
		const double *X,
		const double *xOverlap,
		double *yOverlap,
		PURE_SHEAR mode,
		double gamma
);


/**
 * Call this function on a single point 'X'
 * NOTE: neighPtr to should point to 'numNeigh' for 'X'
 * and thus describe the neighborhood list as usual
 */
double computeWeightedVolume
(
		const double *X,
		const double *xOverlap,
		const double* volumeOverlap,
		const int* localNeighborList
);

/**
 * Call this function on a single point 'X'
 * NOTE: neighPtr to should point to 'numNeigh' for 'X'
 * and thus describe the neighborhood list as usual
 */
double computeDilatation
(
		const int *neighPtr,
		const double *X,
		const double *xOverlap,
		const double *Y,
		const double *yOverlap,
		const double *volumeOverlap,
		double weightedVolume
);

/**
 * Call this function on a single point 'X'
 * NOTE: neighPtr to should point to 'numNeigh' for 'X'
 * and thus describe the neighborhood list as usual
 * Y is the deformed configuration of 'X' but because
 * this is a probe, Y=X
 * This function returns the norm of the
 * deviatoric extension state squared.
 */
double compute_norm_2_deviatoric_extension
(
		const int *neighPtr,
		const double *X,
		const double *xOverlap,
		const double *Y,
		const double *yOverlap,
		const double *volumeOverlap,
		double weighted_volume
);

void computeShearCorrectionFactor
(
		int numOwnedPoints,
		const double *xOverlap,
		double *yOverlap_scratch_required_work_space,
		const double *volumeOverlap,
		const double *owned_weighted_volume,
		const int*  localNeighborList,
		double horizon,
		double *shearCorrectionFactorOwned
);


}

#endif /* PDMATERIALUTILITIES_H_ */
