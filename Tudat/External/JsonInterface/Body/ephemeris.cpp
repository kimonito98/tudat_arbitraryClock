/*    Copyright (c) 2010-2017, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 */

#include "ephemeris.h"

namespace tudat
{

namespace ephemerides
{

//! Convert `ApproximatePlanetPositionsBase::BodiesWithEphemerisData` to `json`.
void to_json( json& jsonObject, const ApproximatePlanetPositionsBase::BodiesWithEphemerisData& bodyWithEphemerisData )
{
    jsonObject = json( json_interface::stringFromEnum( bodyWithEphemerisData, bodiesWithEphemerisData ) );
}

//! Convert `json` to `ApproximatePlanetPositionsBase::BodiesWithEphemerisData`.
void from_json( const json& jsonObject, ApproximatePlanetPositionsBase::BodiesWithEphemerisData& bodyWithEphemerisData )
{
    bodyWithEphemerisData = json_interface::enumFromString( jsonObject.get< std::string >( ), bodiesWithEphemerisData );
}

} // namespace ephemerides


namespace simulation_setup
{

//! Convert `EphemerisType` to `json`.
void to_json( json& jsonObject, const EphemerisType& ephemerisType )
{
    jsonObject = json( json_interface::stringFromEnum( ephemerisType, ephemerisTypes ) );
}

//! Convert `json` to `EphemerisType`.
void from_json( const json& jsonObject, EphemerisType& ephemerisType )
{
    ephemerisType = json_interface::enumFromString( jsonObject.get< std::string >( ), ephemerisTypes );
}

//! Create a `json` object from a shared pointer to a `EphemerisSettings` object.
void to_json( json& jsonObject, const boost::shared_ptr< EphemerisSettings >& ephemerisSettings )
{
    using namespace json_interface;
    using Keys = Keys::Body::Ephemeris;

    // Initialise
    jsonObject = json( );

    // Common keys
    jsonObject[ Keys::type ] = ephemerisSettings->getEphemerisType( );
    jsonObject[ Keys::frameOrigin ] = ephemerisSettings->getFrameOrigin( );
    jsonObject[ Keys::frameOrientation ] = ephemerisSettings->getFrameOrientation( );
    jsonObject[ Keys::makeMultiArc ] = ephemerisSettings->getMakeMultiArcEphemeris( );

    /// ApproximatePlanetPositionSettings
    boost::shared_ptr< ApproximatePlanetPositionSettings > approximatePlanetPositionSettings =
            boost::dynamic_pointer_cast< ApproximatePlanetPositionSettings >( ephemerisSettings );
    if ( approximatePlanetPositionSettings )
    {
        jsonObject[ Keys::bodyIdentifier ] = approximatePlanetPositionSettings->getBodyIdentifier( );
        jsonObject[ Keys::useCircularCoplanarApproximation ] =
                approximatePlanetPositionSettings->getUseCircularCoplanarApproximation( );
        return;
    }

    /// DirectSpiceEphemerisSettings
    boost::shared_ptr< DirectSpiceEphemerisSettings > directSpiceEphemerisSettings =
            boost::dynamic_pointer_cast< DirectSpiceEphemerisSettings >( ephemerisSettings );
    if ( directSpiceEphemerisSettings )
    {
        jsonObject[ Keys::correctForStellarAbberation ] =
                directSpiceEphemerisSettings->getCorrectForStellarAbberation( );
        jsonObject[ Keys::correctForLightTimeAbberation ] =
                directSpiceEphemerisSettings->getCorrectForLightTimeAbberation( );
        jsonObject[ Keys::convergeLighTimeAbberation ] =
                directSpiceEphemerisSettings->getConvergeLighTimeAbberation( );

        /// InterpolatedSpiceEphemerisSettings
        boost::shared_ptr< InterpolatedSpiceEphemerisSettings > interpolatedSpiceEphemerisSettings =
                boost::dynamic_pointer_cast< InterpolatedSpiceEphemerisSettings >( directSpiceEphemerisSettings );
        if ( interpolatedSpiceEphemerisSettings )
        {
            jsonObject[ Keys::initialTime ] = interpolatedSpiceEphemerisSettings->getInitialTime( );
            jsonObject[ Keys::finalTime ] = interpolatedSpiceEphemerisSettings->getFinalTime( );
            jsonObject[ Keys::timeStep ] = interpolatedSpiceEphemerisSettings->getTimeStep( );
            // jsonObject[ Keys::interpolator ] = interpolatedSpiceEphemerisSettings->getInterpolatorSettings( );
            jsonObject[ Keys::useLongDoubleStates ] = interpolatedSpiceEphemerisSettings->getUseLongDoubleStates( );
            return;
        }

        return;
    }

    /// TabulatedEphemerisSettings
    boost::shared_ptr< TabulatedEphemerisSettings > tabulatedEphemerisSettings =
            boost::dynamic_pointer_cast< TabulatedEphemerisSettings >( ephemerisSettings );
    if ( tabulatedEphemerisSettings )
    {
        jsonObject[ Keys::bodyStateHistory ] = tabulatedEphemerisSettings->getBodyStateHistory( );
        jsonObject[ Keys::useLongDoubleStates ] = tabulatedEphemerisSettings->getUseLongDoubleStates( );
        return;
    }

    /// ConstantEphemerisSettings
    boost::shared_ptr< ConstantEphemerisSettings > constantEphemerisSettings =
            boost::dynamic_pointer_cast< ConstantEphemerisSettings >( ephemerisSettings );
    if ( constantEphemerisSettings )
    {
        jsonObject[ Keys::constantState ] = constantEphemerisSettings->getConstantState( );
        return;
    }

    /// KeplerEphemerisSettings
    boost::shared_ptr< KeplerEphemerisSettings > keplerEphemerisSettings =
            boost::dynamic_pointer_cast< KeplerEphemerisSettings >( ephemerisSettings );
    if ( keplerEphemerisSettings )
    {
        jsonObject[ Keys::initialStateInKeplerianElements ] =
                keplerEphemerisSettings->getInitialStateInKeplerianElements( );
        jsonObject[ Keys::epochOfInitialState ] =
                keplerEphemerisSettings->getEpochOfInitialState( );
        jsonObject[ Keys::centralBodyGravitationalParameter ] =
                keplerEphemerisSettings->getCentralBodyGravitationalParameter( );
        jsonObject[ Keys::rootFinderAbsoluteTolerance ] =
                keplerEphemerisSettings->getRootFinderAbsoluteTolerance( );
        jsonObject[ Keys::rootFinderMaximumNumberOfIterations ] =
                keplerEphemerisSettings->getRootFinderMaximumNumberOfIterations( );
        return;
    }

    /// CustomEphemerisSettings
    boost::shared_ptr< CustomEphemerisSettings > customEphemerisSettings =
            boost::dynamic_pointer_cast< CustomEphemerisSettings >( ephemerisSettings );
    if ( customEphemerisSettings )
    {
        throw std::runtime_error( "CustomEphemerisSettings not supported by json_interface." ); // FIXME
    }
}

} // namespace simulation_setup


namespace json_interface
{

//! Create a shared pointer to a `EphemerisSettings` object from a `json` object.
boost::shared_ptr< simulation_setup::EphemerisSettings > createEphemerisSettings(
        const json& settings, const KeyTree& keyTree )
{
    using namespace simulation_setup;
    using Keys = Keys::Body::Ephemeris;

    // Get atmosphere model type
    const EphemerisType ephemerisType = getValue< EphemerisType >( settings, keyTree + Keys::type );

    switch ( ephemerisType ) {
    case approximate_planet_positions:
        return boost::make_shared< ApproximatePlanetPositionSettings >(
                    getValue< ephemerides::ApproximatePlanetPositionsBase::BodiesWithEphemerisData >(
                        settings, keyTree + Keys::bodyIdentifier ),
                    getValue< bool >( settings, keyTree + Keys::useCircularCoplanarApproximation ) );
    case direct_spice_ephemeris:
    {
        DirectSpiceEphemerisSettings defaults;

        const std::string frameOrigin = getValue( settings, keyTree + Keys::frameOrigin,
                                                  defaults.getFrameOrigin( ) );
        const std::string frameOrientation = getValue( settings, keyTree + Keys::frameOrientation,
                                                       defaults.getFrameOrientation( ) );
        const bool correctForStellarAbberation = getValue( settings, keyTree + Keys::correctForStellarAbberation,
                                                           defaults.getCorrectForStellarAbberation() );
        const bool correctForLightTimeAbberation = getValue( settings, keyTree + Keys::correctForLightTimeAbberation,
                                                             defaults.getCorrectForLightTimeAbberation( ) );
        const bool convergeLighTimeAbberation = getValue( settings, keyTree + Keys::convergeLighTimeAbberation,
                                                          defaults.getConvergeLighTimeAbberation( ) );

        return boost::make_shared< DirectSpiceEphemerisSettings >(
                    frameOrigin, frameOrientation, correctForStellarAbberation,
                    correctForLightTimeAbberation, convergeLighTimeAbberation );
    }
    case tabulated_ephemeris:
    {
        TabulatedEphemerisSettings defaults( { } );

        const std::map< double, Eigen::Vector6d > bodyStateHistory =
                getValue< std::map< double, Eigen::Vector6d > >( settings, keyTree + Keys::bodyStateHistory );
        const std::string frameOrigin =
                getValue( settings, keyTree + Keys::frameOrigin, defaults.getFrameOrigin( ) );
        const std::string frameOrientation =
                getValue( settings, keyTree + Keys::frameOrientation, defaults.getFrameOrientation( ) );

        TabulatedEphemerisSettings tabulatedEphemerisSettings( bodyStateHistory, frameOrigin, frameOrientation );
        tabulatedEphemerisSettings.setUseLongDoubleStates(
                    getValue( settings, keyTree + Keys::useLongDoubleStates, defaults.getUseLongDoubleStates( ) ) );

        return boost::make_shared< TabulatedEphemerisSettings >( tabulatedEphemerisSettings );
    }
    case interpolated_spice:
    {
        InterpolatedSpiceEphemerisSettings defaults( TUDAT_NAN, TUDAT_NAN, TUDAT_NAN );

        const double initialTime = getValue< double >( settings, keyTree + Keys::initialTime );
        const double finalTime = getValue< double >( settings, keyTree + Keys::finalTime );
        const double timeStep = getValue< double >( settings, keyTree + Keys::timeStep );
        const std::string frameOrigin =
                getValue( settings, keyTree + Keys::frameOrigin, defaults.getFrameOrigin( ) );
        const std::string frameOrientation =
                getValue( settings, keyTree + Keys::frameOrientation, defaults.getFrameOrientation( ) );
        // const boost::shared_ptr< interpolators::InterpolatorSettings > interpolatorSettings =
        //         getValue( settings, keyTree + Keys::interpolator, defaults.getInterpolatorSettings( ) );
        const boost::shared_ptr< interpolators::InterpolatorSettings > interpolatorSettings
                = defaults.getInterpolatorSettings( );
        // FIXME

        InterpolatedSpiceEphemerisSettings interpolatedSpiceEphemerisSettings(
                    initialTime, finalTime, timeStep, frameOrigin, frameOrientation, interpolatorSettings );
        interpolatedSpiceEphemerisSettings.setUseLongDoubleStates(
                    getValue( settings, keyTree + Keys::useLongDoubleStates, defaults.getUseLongDoubleStates( ) ) );

        return boost::make_shared< InterpolatedSpiceEphemerisSettings >( interpolatedSpiceEphemerisSettings );
    }
    case constant_ephemeris:
    {
        ConstantEphemerisSettings defaults( Eigen::Vector6d::Zero( ) );

        const Eigen::Vector6d constantState = getValue< Eigen::Vector6d >( settings, keyTree + Keys::constantState );
        const std::string frameOrigin =
                getValue( settings, keyTree + Keys::frameOrigin, defaults.getFrameOrigin( ) );
        const std::string frameOrientation =
                getValue( settings, keyTree + Keys::frameOrientation, defaults.getFrameOrientation( ) );

        return boost::make_shared< ConstantEphemerisSettings >(
                    constantState, frameOrigin, frameOrientation );
    }
    case kepler_ephemeris:
    {
        KeplerEphemerisSettings defaults( Eigen::Vector6d::Zero( ), TUDAT_NAN, TUDAT_NAN );

        const Eigen::Vector6d initialStateInKeplerianElements =
                getValue< Eigen::Vector6d >( settings, keyTree + Keys::initialStateInKeplerianElements );
        const double epochOfInitialState =
                getValue< bool >( settings, keyTree + Keys::epochOfInitialState );
        const double centralBodyGravitationalParameter =
                getValue< bool >( settings, keyTree + Keys::centralBodyGravitationalParameter );
        const std::string frameOrigin =
                getValue( settings, keyTree + Keys::frameOrigin, defaults.getFrameOrigin( ) );
        const std::string frameOrientation =
                getValue( settings, keyTree + Keys::frameOrientation, defaults.getFrameOrientation( ) );
        const double rootFinderAbsoluteTolerance = getValue( settings, keyTree + Keys::rootFinderAbsoluteTolerance,
                                                             defaults.getRootFinderAbsoluteTolerance( ) );
        const double rootFinderMaximumNumberOfIterations = getValue(
                    settings, keyTree + Keys::rootFinderMaximumNumberOfIterations,
                    defaults.getRootFinderMaximumNumberOfIterations( ) );

        return boost::make_shared< KeplerEphemerisSettings >(
                    initialStateInKeplerianElements, epochOfInitialState, centralBodyGravitationalParameter,
                    frameOrigin, frameOrientation, rootFinderAbsoluteTolerance, rootFinderMaximumNumberOfIterations );
    }
        /* FIXME
    case custom_ephemeris:
    {

    }
    */
    default:
        throw std::runtime_error( stringFromEnum( ephemerisType, ephemerisTypes )
                                  + " not supported by json_interface." );
    }
}

} // namespace json_interface

} // namespace tudat
