/*    Copyright (c) 2010-2018, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 */

#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

#include "Tudat/Basics/testMacros.h"
#include "Tudat/InputOutput/basicInputOutput.h"
#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/Mathematics/Filters/linearKalmanFilter.h"
#include "Tudat/Mathematics/NumericalIntegrators/createNumericalIntegrator.h"

namespace tudat
{

namespace unit_tests
{

BOOST_AUTO_TEST_SUITE( test_linear_kalman_filter )

// Test implementation of linear Kalman filter class. Tested by comparison with code by https://github.com/hmartiro/kalman-cpp.
BOOST_AUTO_TEST_CASE( testLinearKalmanFilter )
{
    using namespace tudat::filters;

    // Set initial conditions
    const double initialTime = 0;
    const double timeStep = 1.0 / 30.0;
    const unsigned int numberOfTimeSteps = 45;

    Eigen::Vector3d initialStateVector = Eigen::Vector3d::Zero( );
    initialStateVector[ 0 ] = 1.04202710058;
    initialStateVector[ 2 ] = -9.81;

    Eigen::Vector3d initialEstimatedStateVector = Eigen::Vector3d::Zero( );
    initialEstimatedStateVector[ 0 ] = 1.04202710058;
    initialEstimatedStateVector[ 2 ] = -9.81;

    Eigen::Matrix3d initialEstimatedStateCovarianceMatrix = Eigen::Matrix3d::Zero( );
    initialEstimatedStateCovarianceMatrix( 0, 0 ) = 0.1;
    initialEstimatedStateCovarianceMatrix( 0, 1 ) = 0.1;
    initialEstimatedStateCovarianceMatrix( 0, 2 ) = 0.1;
    initialEstimatedStateCovarianceMatrix( 1, 0 ) = 0.1;
    initialEstimatedStateCovarianceMatrix( 1, 1 ) = 10000.0;
    initialEstimatedStateCovarianceMatrix( 1, 2 ) = 10.0;
    initialEstimatedStateCovarianceMatrix( 2, 0 ) = 0.1;
    initialEstimatedStateCovarianceMatrix( 2, 1 ) = 10.0;
    initialEstimatedStateCovarianceMatrix( 2, 2 ) = 100.0;

    // Set system dynamics and measurement
    Eigen::Matrix3d stateTransitionMatrix = Eigen::Matrix3d::Zero( );
    Eigen::Matrix3d controlMatrix = Eigen::Matrix3d::Zero( );
    Eigen::RowVector3d measurementMatrix = Eigen::RowVector3d::Zero( );
    stateTransitionMatrix( 0, 0 ) = 1.0;
    stateTransitionMatrix( 0, 1 ) = timeStep;
    stateTransitionMatrix( 1, 1 ) = 1.0;
    stateTransitionMatrix( 1, 2 ) = timeStep;
    stateTransitionMatrix( 2, 2 ) = 1.0;
    measurementMatrix[ 0 ] = 1.0;

    // Set system and measurement uncertainty
    Eigen::Matrix3d systemUncertainty = Eigen::Matrix3d::Zero( );
    Eigen::Vector1d measurementUncertainty = Eigen::Vector1d::Zero( );
    systemUncertainty( 0, 0 ) = 0.05;
    systemUncertainty( 0, 1 ) = 0.05;
    systemUncertainty( 1, 0 ) = 0.05;
    systemUncertainty( 1, 1 ) = 0.05;
    measurementUncertainty[ 0 ] = 0.5;

    // Create linear Kalman filter object
    KalmanFilterDoublePointer linearFilter = boost::make_shared< LinearKalmanFilterDouble >(
                boost::lambda::constant( stateTransitionMatrix ),
                boost::lambda::constant( controlMatrix ),
                boost::lambda::constant( measurementMatrix ),
                systemUncertainty, measurementUncertainty,
                initialTime, initialEstimatedStateVector, initialEstimatedStateCovarianceMatrix );

    // Loop over each time step
    const bool showProgress = false;
    double currentTime = initialTime;
    Eigen::Vector3d currentStateVector = initialStateVector;
    Eigen::Vector3d currentControlVector = Eigen::Vector3d::Zero( );
    Eigen::Vector1d currentMeasurementVector;
    std::map< double, Eigen::Vector3d > actualStateVectorHistory;
    std::map< double, Eigen::Vector1d > measurementVectorHistory;
    for( unsigned int i = 0; i < numberOfTimeSteps; i++ )
    {
        // Compute actual values and perturb them
        currentTime += timeStep;
        actualStateVectorHistory[ currentTime ] = stateTransitionMatrix * currentStateVector +
                controlMatrix * currentControlVector;
        currentStateVector = actualStateVectorHistory[ currentTime ] + linearFilter->produceSystemNoise( );
        currentMeasurementVector = measurementMatrix * currentStateVector + linearFilter->produceMeasurementNoise( );
        measurementVectorHistory[ currentTime ] = currentMeasurementVector;

        // Update filter
        linearFilter->updateFilter( currentTime, currentControlVector, currentMeasurementVector );

        // Print progress
        if ( showProgress )
        {
            std::cout << "Time: " << currentTime << std::endl
                      << "Measurement: " << currentMeasurementVector.transpose( ) << std::endl
                      << "Estimated State: " << linearFilter->getCurrentStateEstimate( ).transpose( ) << std::endl;
        }
    }

    Eigen::Vector3d expectedFinalState;
    expectedFinalState << -6.4864733265253589, -10.658714466072745, -7.1799113529409091;
    for ( unsigned int i = 0; i < expectedFinalState.rows( ); i++ )
    {
        BOOST_CHECK_SMALL( linearFilter->getCurrentStateEstimate( )[ i ] - expectedFinalState[ i ],
                           std::numeric_limits< double >::epsilon( ) );
    }
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests

} // namespace tudat
