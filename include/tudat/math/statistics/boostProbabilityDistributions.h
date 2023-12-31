/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#ifndef TUDAT_BOOSTPROBABILITYDISTRIBUTIONS_H
#define TUDAT_BOOSTPROBABILITYDISTRIBUTIONS_H

#include <cmath>
#include <memory>

#include <boost/math/distributions.hpp>

#include "tudat/math/basic/mathematicalConstants.h"
#include "tudat/math/statistics/continuousProbabilityDistributions.h"


namespace tudat
{

namespace statistics
{

//! Interface for continuous random variable calculations using distributions implemented in boost
/*!
 *  Interface for continuous random variable calculations using distributions implemented in boost. Derives from the
 *  InvertibleContinuousProbabilityDistribution class, uses boost implementation for evaluating distribution functions
 *  (pdf, cdf and inverse cdf). Class may be automatically generated by createBoostRandomVariable function.
 *  \tparam Template parameter defining boost distribution type, NOT to be confused with
 *  ContinuousBoostStatisticalDistributions enum. Input should be consistent with first required input parameter to
 *  boost::math::pdf/cdf/quantile< double > functions.
 */
template< typename BoostDistributionType >
class BoostContinuousProbabilityDistribution: public InvertibleContinuousProbabilityDistribution< double >
{
public:

    //! Constructor, sets distribution type
    /*!
     *  Constructor, sets distribution type
     *  \param distribution Distribution type implemented in boost
     */
    BoostContinuousProbabilityDistribution( const BoostDistributionType distribution ):
        distribution_( distribution ){ }

    //! Destructor
    ~BoostContinuousProbabilityDistribution( ){ }

    //! Function to evaluate pdf of distribution
    /*!
     *  Function to evaluate probability distribution function at given independentVariable value by calling boost
     *  implementation
     *  \param independentVariable Value of independent variable
     *  \return Evaluated pdf
     */
    double evaluatePdf( const double& independentVariable )
    {
        return boost::math::pdf< double >( distribution_, independentVariable );
    }


    //! Function to evaluate pcdfdf of distribution
    /*!
     *  Function to evaluate cumulative distribution function at given independentVariable value by calling boost
     * implementation
     *  \param independentVariable Value of independent variable
     *  \return Evaluated cdf
     */
    double evaluateCdf( const double& independentVariable )
    {
        return boost::math::cdf< double >( distribution_, independentVariable );
    }

    //! Function to evaluate pdf of distribution
    /*!
     *  Function to evaluate inverse cumulative distribution function at given probability value
     *  \param independentVariable Value of probability at which inverse cdf is to be computed (must be in the domain [0,1]).
     *  Computed by calling boost implementation
     *  \return Evaluated inverse cdf
     */
    double evaluateInverseCdf( const double independentVariable )
    {
        return boost::math::quantile< double >( distribution_, independentVariable );
    }
private:

    //! Boost dustribution type, must be possible first input argument for boost::math::pdf/cdf/quantile< double > functions
    BoostDistributionType distribution_;

};

//! Function to create a random variable class of BoostContinuousProbabilityDistribution type
/*!
 *  Function to create a random variable class of BoostContinuousProbabilityDistribution type, which links random variable
 *  interfaces of this architecture to implementations from boost.
 *  \param boostDistribution Type of distribution of which a random variable class is to be generated
 *  \param parameters Free parameters of requested distribution (for instance mean and standard deviation for Gaussian
 *  distribution, see  implementation for order of parameter, if relevant)
 *  \return Random variable class of BoostContinuousProbabilityDistribution type
 */
std::shared_ptr< InvertibleContinuousProbabilityDistribution< double > > createBoostRandomVariable(
        const ContinuousBoostStatisticalDistributions boostDistribution, const std::vector< double >& parameters );

} // namespace statistics

} // namespace tudat


#endif // TUDAT_BOOSTPROBABILITYDISTRIBUTIONS_H
