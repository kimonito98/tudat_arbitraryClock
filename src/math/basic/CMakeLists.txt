#    Copyright (c) 2010-2019, Delft University of Technology
#    All rigths reserved
#
#    This file is part of the Tudat. Redistribution and use in source and
#    binary forms, with or without modification, are permitted exclusively
#    under the terms of the Modified BSD license. You should have received
#    a copy of the license with this file. If not, please or visit:
#    http://tudat.tudelft.nl/LICENSE.
#

# Add source files.
set(basic_mathematics_SOURCES
        "coordinateConversions.cpp"
        "legendrePolynomials.cpp"
        "nearestNeighbourSearch.cpp"
        "numericalDerivative.cpp"
        "sphericalHarmonics.cpp"
        "rotationAboutArbitraryAxis.cpp"
        "basicMathematicsFunctions.cpp"
        "coordinateConversions.cpp"
        "linearAlgebra.cpp"
        "leastSquaresEstimation.cpp"
        "rotationRepresentations.cpp"
        )

# Add header files.
set(basic_mathematics_HEADERS
        "basicFunction.h"
        "convergenceException.h"
        "coordinateConversions.h"
        "function.h"
        "functionProxy.h"
        "legendrePolynomials.h"
        "linearAlgebra.h"
        "nearestNeighbourSearch.h"
        "numericalDerivative.h"
        "sphericalHarmonics.h"
        "rotationAboutArbitraryAxis.h"
        "basicMathematicsFunctions.h"
        "coordinateConversions.h"
        "linearAlgebra.h"
        "mathematicalConstants.h"
        "leastSquaresEstimation.h"
        "rotationRepresentations.h"
        )

# Add library.
TUDAT_ADD_LIBRARY("basic_mathematics"
        "${basic_mathematics_SOURCES}"
        "${basic_mathematics_HEADERS}"
        PRIVATE_LINKS "${Boost_LIBRARIES}"
        PRIVATE_INCLUDES "${EIGEN3_INCLUDE_DIRS}" "${Boost_INCLUDE_DIRS}"
        )

# Add tests.
TUDAT_ADD_TEST_CASE(MathematicalConstants)
TUDAT_ADD_TEST_CASE(LinearAlgebra PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(CoordinateConversions PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(NearestNeighbourSearch PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(NumericalDerivative PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(LegendrePolynomials PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(SphericalHarmonics PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(RotationAboutArbitraryAxis PRIVATE_LINKS tudat_basic_mathematics)
TUDAT_ADD_TEST_CASE(RotationPartials PRIVATE_LINKS tudat_basic_mathematics tudat_reference_frames)