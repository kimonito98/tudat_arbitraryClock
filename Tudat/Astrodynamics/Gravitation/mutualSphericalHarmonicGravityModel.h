/*    Copyright (c) 2010-2016, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#ifndef TUDAT_MUTUALSPHERICALHARMONICGRAVITYMODEL_H
#define TUDAT_MUTUALSPHERICALHARMONICGRAVITYMODEL_H


#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "Tudat/Astrodynamics/BasicAstrodynamics/accelerationModel.h"
#include "Tudat/Astrodynamics/Gravitation/sphericalHarmonicsGravityModelBase.h"
#include "Tudat/Astrodynamics/Gravitation/sphericalHarmonicsGravityModel.h"
#include "Tudat/Mathematics/BasicMathematics/legendrePolynomials.h"
#include "Tudat/Mathematics/BasicMathematics/linearAlgebraTypes.h"

namespace tudat
{

namespace gravitation
{

//! Function to manually remove the C(0,0) term from cosine coefficients,
/*!
 *  Function to manually remove the C(0,0) term from cosine coefficients, used by
 *  MutualSphericalHarmonicsGravitationalAccelerationModel. By using this function, the original function returning the sh
 *  coefficients is left untouched, not compromising the environment  model, while the C(0,0) term is not calculated doubly
 *  by the MutualSphericalHarmonicsGravitationalAccelerationModel class.
 */
Eigen::MatrixXd setDegreeAndOrderCoefficientToZero( const boost::function< Eigen::MatrixXd( ) > originalCosineCoefficientFunction );

//! Class to calculate the mutual spherical harmonic gravitational acceleration between two bodies.
/*!
 *  Class to calculate the mutual spherical harmonic gravitational acceleration between two extended bodies A and B.
 *  The calculations include the interaction of the point masses A and B, extended body A and point mass B, as well as
 *  extended bodyB and point mass A.  As an example, the model can be used for precise calculations of the dynamics of
 *  planetary system (Earth-Moon, Mars-Phoboss-Deimos, Jupiter-Galilean satellites).
 *  Model is taken from Lainey et al. (2001, 2004)
 */
class MutualSphericalHarmonicsGravitationalAccelerationModel
        : public basic_astrodynamics::AccelerationModel< Eigen::Vector3d >
{
private:

    //! Typedef for coefficient-matrix-returning function.
    typedef boost::function< Eigen::MatrixXd( ) > CoefficientMatrixReturningFunction;

    //! Typedef for function returning body position.
    typedef boost::function< Eigen::Vector3d( ) > StateFunction;

    //! Typedef for function returning gravitational parameter.
    typedef boost::function< double( ) > DataReturningFunction;

public:

    //! Constructor.
    /*!
     *  Constructor, provides the position functions of the involved bodies, and the required data on their gravitational
     * fields.
     *  \param positionOfBodySubjectToAccelerationFunction Function returning the current position of the body undergoing
     *  the acceleration.
     *  \param positionOfBodyExertingAccelerationFunction Function returning the current position of the body exerting
     *  the acceleration.
     *  \param gravitationalParameterFunction Function returning the current gravitational parameter, either of the body
     *  exerting the acceleration or the sum of that of both bodies, depending on value of useCentralBodyFixedFrame,
     *  (false for former, true for latter).
     *  \param equatorialRadiusOfBodyExertingAcceleration Equatorial radius used in representation of spherical harmonic
     *  coefficients of body exerting acceleration.
     *  \param equatorialRadiusOfBodyUndergoingAcceleration Equatorial radius used in representation of spherical harmonic
     *  coefficients of body undergoing acceleration.
     *  \param cosineHarmonicCoefficientsFunctionOfBodyExertingAcceleration Function returning the spherical harmonic cosine
     *  coefficients of the body exerting the acceleration.
     *  \param sineHarmonicCoefficientsFunctionOfBodyExertingAcceleration Function returning the spherical harmonic sine
     *  coefficients of  the body exerting the acceleration.
     *  \param cosineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration Function returning the spherical harmonic
     *  cosine coefficients of the body undergoing the acceleration.
     *  \param sineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration Function returning the spherical harmonic
     *  sine coefficients of the body undergoing the acceleration.
     *  \param toLocalFrameOfBodyExertingAccelerationTransformation Function returning the quaternion to rotate from the
     *  body-fixed frame of  the body exerting the acceleration, in  which the spherical harmonic coefficients are defined,
     *  to the inertially oriented frame, in which the acceleration is expressed.
     *  \param toLocalFrameOfBodyUndergoingAccelerationTransformation Function returning the quaternion to rotate from the
     *  body-fixed frame of the body undergoing the acceleration, in  which the spherical harmonic coefficients are defined,
     *  to the inertially oriented frame, in which the acceleration is expressed.
     *  \param useCentralBodyFixedFrame Boolean denoting whether the acceleration is expressed in a frame centered on the
     *  body exerting the acceleration, in which case the gravitational parameter that is used is the some of the
     *  gravitational parameters of both bodies, to take into  account the inertial acceleration of the reference frame in
     *  which the acceleration is performed.
     *  \param sphericalHarmonicsCacheOfBodyExertingAcceleration Caching object for computation of spherical harmonic
     *  potential (gradient) of body exerting acceleration.
     *  *  \param sphericalHarmonicsCacheOfBodyUndergoingAcceleration Caching object for computation of spherical harmonic
     *  potential (gradient) of body undergoing acceleration.
     */
    MutualSphericalHarmonicsGravitationalAccelerationModel(
            const StateFunction& positionOfBodySubjectToAccelerationFunction,
            const StateFunction& positionOfBodyExertingAccelerationFunction,
            const DataReturningFunction& gravitationalParameterFunction,
            const double equatorialRadiusOfBodyExertingAcceleration,
            const double equatorialRadiusOfBodyUndergoingAcceleration,
            const CoefficientMatrixReturningFunction& cosineHarmonicCoefficientsFunctionOfBodyExertingAcceleration,
            const CoefficientMatrixReturningFunction& sineHarmonicCoefficientsFunctionOfBodyExertingAcceleration,
            const CoefficientMatrixReturningFunction& cosineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration,
            const CoefficientMatrixReturningFunction& sineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration,
            const boost::function< Eigen::Quaterniond( ) >& toLocalFrameOfBodyExertingAccelerationTransformation,
            const boost::function< Eigen::Quaterniond( ) >& toLocalFrameOfBodyUndergoingAccelerationTransformation,
            const bool useCentralBodyFixedFrame,
            boost::shared_ptr< basic_mathematics::SphericalHarmonicsCache >
            sphericalHarmonicsCacheOfBodyExertingAcceleration =
            boost::make_shared< basic_mathematics::SphericalHarmonicsCache >( ),
            boost::shared_ptr< basic_mathematics::SphericalHarmonicsCache >
            sphericalHarmonicsCacheOfBodyUndergoingAcceleration =
            boost::make_shared< basic_mathematics::SphericalHarmonicsCache >( ) ):
        useCentralBodyFixedFrame_( useCentralBodyFixedFrame ),
        gravitationalParameterFunction_( gravitationalParameterFunction )
    {

        // Create spherical harmonic acceleration due to expansion of body exerting acceleration
        accelerationModelFromShExpansionOfBodyExertingAcceleration_ = boost::make_shared<
                SphericalHarmonicsGravitationalAccelerationModel >(
                    positionOfBodySubjectToAccelerationFunction, gravitationalParameterFunction,
                    equatorialRadiusOfBodyExertingAcceleration,
                    cosineHarmonicCoefficientsFunctionOfBodyExertingAcceleration,
                    sineHarmonicCoefficientsFunctionOfBodyExertingAcceleration,
                    positionOfBodyExertingAccelerationFunction,
                    toLocalFrameOfBodyExertingAccelerationTransformation,
                    useCentralBodyFixedFrame, sphericalHarmonicsCacheOfBodyExertingAcceleration );

        // Create spherical harmonic acceleration due to expansion of body undergoing acceleration, with the C(0,0) term set
        // to zero to prevent the double computation of the central term. Note that the order of the position functions is
        // switched wrt the regular input, to ensure that the acceleration vector points in the right direction
        // (i.e. from body undergoing to body exerting acceleration).
        accelerationModelFromShExpansionOfBodyundergoingAcceleration_ = boost::make_shared<
                SphericalHarmonicsGravitationalAccelerationModel >(
                    positionOfBodyExertingAccelerationFunction, gravitationalParameterFunction,
                    equatorialRadiusOfBodyUndergoingAcceleration,
                    boost::bind( &setDegreeAndOrderCoefficientToZero,
                                 cosineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration ),
                    sineHarmonicCoefficientsFunctionOfBodyUndergoingAcceleration,
                    positionOfBodySubjectToAccelerationFunction,
                    toLocalFrameOfBodyUndergoingAccelerationTransformation,
                    useCentralBodyFixedFrame, sphericalHarmonicsCacheOfBodyUndergoingAcceleration );
    }

    //! Update member variables used by the acceleration model.
    /*!
     *  Update member variables used by the two constituent sh acceleration models.
     */
    virtual void updateMembers( const double currentTime = TUDAT_NAN )
    {
        accelerationModelFromShExpansionOfBodyExertingAcceleration_->updateMembers( currentTime );
        accelerationModelFromShExpansionOfBodyundergoingAcceleration_->updateMembers( currentTime );
        this->currentTime_ = currentTime;
    }

    //! Function to reset the current time
    /*!
     * Function to reset the current time of the acceleration model.
     * \param currentTime Current time (default NaN).
     */
    virtual void resetTime( const double currentTime = TUDAT_NAN )
    {
        currentTime_ = currentTime;

        accelerationModelFromShExpansionOfBodyExertingAcceleration_->resetTime( currentTime );
        accelerationModelFromShExpansionOfBodyundergoingAcceleration_->resetTime( currentTime );
    }

    //! Function to get the mutual sh acceleration value.
    /*!
     *  Function to get the mutual sh acceleration value, determined from the sum of the two constituent acceleration models.
     */
    Eigen::Vector3d getAcceleration( )
    {
        return accelerationModelFromShExpansionOfBodyExertingAcceleration_->getAcceleration( ) -
                accelerationModelFromShExpansionOfBodyundergoingAcceleration_->getAcceleration( );
    }

    //! Function returning whether the acceleration is expressed in a frame centered on the body exerting the acceleration.
    /*!
     *  Function returning whether the acceleration is expressed in a frame centered on the body exerting the acceleration.
     */
    bool getUseCentralBodyFixedFrame( )
    {
        return useCentralBodyFixedFrame_;
    }

    //! Function to return the function returning the relevant gravitational parameter.
    /*!
     * Function to return the function returning the relevant gravitational parameter.
     * \return Function returning the gravitational parameter used in the computations.
     */
    DataReturningFunction getGravitationalParameterFunction( )
    {
        return gravitationalParameterFunction_;
    }

    //! Function returning the object calculating spherical harmonic acceleration due to the body exerting acceleration
    /*!
     *  Function returning the object calculating spherical harmonic acceleration due to the body exerting acceleration
     */
    boost::shared_ptr< SphericalHarmonicsGravitationalAccelerationModel >
    getAccelerationModelFromShExpansionOfBodyExertingAcceleration( )
    {
        return accelerationModelFromShExpansionOfBodyExertingAcceleration_;
    }

    //! Function returning the object calculating spherical harmonic acceleration due to the body undergoing acceleration
    /*!
     *  Function returning the object calculating spherical harmonic acceleration due to the body undergoing acceleration
     */
    boost::shared_ptr< SphericalHarmonicsGravitationalAccelerationModel >
    getAccelerationModelFromShExpansionOfBodyUndergoingAcceleration( )
    {
        return accelerationModelFromShExpansionOfBodyundergoingAcceleration_;
    }

protected:

    //! Boolean denoting whether the acceleration is expressed in a frame centered on the body exerting the acceleration
    /*!
     *  Boolean denoting whether the acceleration is expressed in a frame centered on the body exerting the acceleration,
     *  in which case the gravitational parameter that is used is the some of the gravitational parameters of both bodies,
     *  to take into  account the inertial acceleration of the reference frame in which the acceleration is performed.
     */
    bool useCentralBodyFixedFrame_;

    //! Function returning the gravitational parameter used for both spherical harmonic accelerations.
    DataReturningFunction gravitationalParameterFunction_;

    //! Object calculating spherical harmonic acceleration due to the body exerting acceleration
    /*!
     *  Object calculating spherical harmonic acceleration due to the body exerting acceleration
     */
    boost::shared_ptr< SphericalHarmonicsGravitationalAccelerationModel >
    accelerationModelFromShExpansionOfBodyExertingAcceleration_;

    //! Object calculating spherical harmonic acceleration due to the body undergoing acceleration
    /*!
     *  Object calculating spherical harmonic acceleration due to the body undergoing acceleration, as felt by the body
     *  undergoing the acceleration due to the figure-point mass coupling between the body undergoing and the body
     *  exerting the acceleration. Note that this acceleration has no central-central term (i.e. C(0,0) is set to zero),
     *  as this term is only calculated by accelerationModelFromShExpansionOfBodyExertingAcceleration_.
     */
    boost::shared_ptr< SphericalHarmonicsGravitationalAccelerationModel >
    accelerationModelFromShExpansionOfBodyundergoingAcceleration_;


};

} // namespace gravitation

} // namespace tudat

#endif // TUDAT_MUTUALSPHERICALHARMONICGRAVITYMODEL_H
