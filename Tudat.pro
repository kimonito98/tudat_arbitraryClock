# -------------------------------------------------
# Project created by QtCreator 2010-09-30T01:39:33
# -------------------------------------------------
QT -= gui
TARGET = Tudat
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += Astrodynamics/Bodies/body.cpp \
    Astrodynamics/Bodies/CelestialBodies/celestialBody.cpp \
    Astrodynamics/Bodies/CelestialBodies/predefinedPlanets.cpp \
    Astrodynamics/Bodies/Vehicles/vehicle.cpp \
    Astrodynamics/Bodies/Vehicles/vehicleExternalModel.cpp \
    Astrodynamics/EnvironmentModels/GravityFieldModel/gravityFieldModel.cpp \
    Astrodynamics/EnvironmentModels/GravityFieldModel/predefinedGravityFieldModels.cpp \
    Astrodynamics/EnvironmentModels/GravityFieldModel/sphericalHarmonicsGravityField.cpp \
    Astrodynamics/EnvironmentModels/GravityFieldModel/unitTestSphericalHarmonicsGravityField.cpp \
    Astrodynamics/ForceModels/gravity.cpp \
    Astrodynamics/ForceModels/Aerothermodynamics/aerodynamics.cpp \
    Astrodynamics/ForceModels/Aerothermodynamics/aerodynamicCoefficientGenerator.cpp \
    Astrodynamics/ForceModels/Aerothermodynamics/hypersonicLocalInclinationAnalysis.cpp \
    Astrodynamics/ForceModels/Aerothermodynamics/unitTestAerodynamicsNamespace.cpp \
    Astrodynamics/ForceModels/Aerothermodynamics/unitTestCoefficientGenerator.cpp \
    Astrodynamics/physicalConstants.cpp \
    Astrodynamics/unitTestPhysicalConstants.cpp \
    Astrodynamics/Propagators/keplerPropagator.cpp \
    Astrodynamics/Propagators/propagatorDataContainer.cpp \
    Astrodynamics/Propagators/propagator.cpp \
    Astrodynamics/Propagators/numericalPropagator.cpp \
    Astrodynamics/States/state.cpp \
    Astrodynamics/States/orbitalElements.cpp \
    Astrodynamics/States/orbitalElementConversions.cpp \
    Astrodynamics/States/keplerianElements.cpp \
    Astrodynamics/States/cartesianElements.cpp \
    Astrodynamics/States/cartesianPositionElements.cpp \
    Astrodynamics/States/cartesianVelocityElements.cpp \
    Astrodynamics/States/unitTestKeplerianElements.cpp \
    Astrodynamics/States/unitTestCartesianElements.cpp \
    Astrodynamics/States/unitTestOrbitalElementConversions.cpp \
    Astrodynamics/MissionSegments/trajectoryDesignMethod.cpp \
    Astrodynamics/MissionSegments/EscapeAndCapture/unitTestEscapeAndCapture.cpp \
    Astrodynamics/MissionSegments/EscapeAndCapture/escapePhase.cpp \
    Astrodynamics/MissionSegments/EscapeAndCapture/escapeAndCapture.cpp \
    Astrodynamics/MissionSegments/EscapeAndCapture/capturePhase.cpp \
    Astrodynamics/MissionSegments/GravityAssist/unitTestGravityAssist.cpp \
    Astrodynamics/MissionSegments/GravityAssist/gravityAssist.cpp \
    Astrodynamics/MissionSegments/LambertTargeter/lambertTargeter.cpp \
    Astrodynamics/MissionSegments/LambertTargeter/unitTestLambertTargeter.cpp \
    Basics/basicFunctions.cpp \
    Mathematics/basicMathematicsFunctions.cpp \
    Mathematics/randomNumberGenerator.cpp \
    Mathematics/unitTestRandomNumberGenerator.cpp \
    Mathematics/GeometricShapes/compositeSurfaceGeometry.cpp \
    Mathematics/GeometricShapes/geometricShape.cpp \
    Mathematics/GeometricShapes/singleSurfaceGeometry.cpp \
    Mathematics/GeometricShapes/surfaceGeometry.cpp \
    Mathematics/GeometricShapes/torus.cpp \
    Mathematics/GeometricShapes/sphereSegment.cpp \
    Mathematics/GeometricShapes/conicalFrustum.cpp \
    Mathematics/GeometricShapes/capsule.cpp \
    Mathematics/GeometricShapes/unitTestLawgsSurfaceGeometry.cpp \
    Mathematics/GeometricShapes/quadrilateralMeshedSurfaceGeometry.cpp \
    Mathematics/GeometricShapes/lawgsPartGeometry.cpp \
    Mathematics/LinearAlgebra/linearAlgebra.cpp \
    Mathematics/NumericalIntegrators/rungeKutta4thOrderFixedStepsize.cpp \
    Mathematics/NumericalIntegrators/integrator.cpp \
    Mathematics/NumericalIntegrators/euler.cpp \
    Mathematics/NumericalIntegrators/singleStepIntegrationMethods.cpp \
    Mathematics/RootFindingMethods/unitTestNewtonRaphson.cpp \
    Mathematics/RootFindingMethods/rootFinder.cpp \
    Mathematics/RootFindingMethods/newtonRaphson.cpp \
    Mathematics/unitTestUnitConversions.cpp \
    Output/writingOutputToFile.cpp \
    unitTests.cpp
HEADERS += Astrodynamics/Bodies/body.h \
    Astrodynamics/Bodies/CelestialBodies/predefinedPlanets.h \
    Astrodynamics/Bodies/CelestialBodies/celestialBody.h \
    Astrodynamics/Bodies/Vehicles/vehicle.h \
    Astrodynamics/Bodies/Vehicles/vehicleExternalModel.h \
    Astrodynamics/EnvironmentModels/environmentModel.h \
    Astrodynamics/EnvironmentModels/GravityFieldModel/gravityFieldModel.h \
    Astrodynamics/EnvironmentModels/GravityFieldModel/predefinedGravityFieldModels.h \
    Astrodynamics/EnvironmentModels/GravityFieldModel/sphericalHarmonicsGravityField.h \
    Astrodynamics/EnvironmentModels/GravityFieldModel/unitTestSphericalHarmonicsGravityField.h \
    Astrodynamics/ForceModels/gravity.h \
    Astrodynamics/ForceModels/forceModel.h \
    Astrodynamics/ForceModels/Aerothermodynamics/aerodynamics.h \
    Astrodynamics/ForceModels/Aerothermodynamics/aerodynamicCoefficientGenerator.h \
    Astrodynamics/ForceModels/Aerothermodynamics/hypersonicLocalInclinationAnalysis.h \
    Astrodynamics/ForceModels/Aerothermodynamics/unitTestAerodynamicsNamespace.h \
    Astrodynamics/ForceModels/Aerothermodynamics/unitTestCoefficientGenerator.h \
    Astrodynamics/physicalConstants.h \
    Astrodynamics/unitTestPhysicalConstants.h \
    Astrodynamics/Propagators/keplerPropagator.h \
    Astrodynamics/Propagators/propagatorDataContainer.h \
    Astrodynamics/Propagators/propagator.h \
    Astrodynamics/Propagators/numericalPropagator.h \
    Astrodynamics/States/state.h \
    Astrodynamics/States/orbitalElements.h \
    Astrodynamics/States/orbitalElementConversions.h \
    Astrodynamics/States/keplerianElements.h \
    Astrodynamics/States/cartesianElements.h \
    Astrodynamics/States/cartesianPositionElements.h \
    Astrodynamics/States/cartesianVelocityElements.h \
    Astrodynamics/States/unitTestKeplerianElements.h \
    Astrodynamics/States/unitTestCartesianElements.h \
    Astrodynamics/States/unitTestOrbitalElementConversions.h \
    Astrodynamics/MissionSegments/trajectoryDesignMethod.h \
    Astrodynamics/MissionSegments/EscapeAndCapture/unitTestEscapeAndCapture.h \
    Astrodynamics/MissionSegments/EscapeAndCapture/escapePhase.h \
    Astrodynamics/MissionSegments/EscapeAndCapture/escapeAndCapture.h \
    Astrodynamics/MissionSegments/EscapeAndCapture/capturePhase.h \
    Astrodynamics/MissionSegments/GravityAssist/unitTestGravityAssist.h \
    Astrodynamics/MissionSegments/GravityAssist/gravityAssist.h \
    Astrodynamics/MissionSegments/LambertTargeter/lambertTargeter.h \
    Astrodynamics/MissionSegments/LambertTargeter/unitTestLambertTargeter.h \
    Basics/basicFunctions.h \
    Mathematics/unitConversions.h \
    Mathematics/unitTestUnitConversions.h \
    Mathematics/basicMathematicsFunctions.h \
    Mathematics/randomNumberGenerator.h \
    Mathematics/unitTestRandomNumberGenerator.h \
    Mathematics/GeometricShapes/compositeSurfaceGeometry.h \
    Mathematics/GeometricShapes/geometricShape.h \
    Mathematics/GeometricShapes/singleSurfaceGeometry.h \
    Mathematics/GeometricShapes/surfaceGeometry.h \
    Mathematics/GeometricShapes/torus.h \
    Mathematics/GeometricShapes/sphereSegment.h \
    Mathematics/GeometricShapes/conicalFrustum.h \
    Mathematics/GeometricShapes/capsule.h \
    Mathematics/GeometricShapes/unitTestLawgsSurfaceGeometry.h \
    Mathematics/GeometricShapes/quadrilateralMeshedSurfaceGeometry.h \
    Mathematics/GeometricShapes/lawgsPartGeometry.h \
    Mathematics/LinearAlgebra/linearAlgebra.h \
    Mathematics/NumericalIntegrators/singleStepIntegrationMethods.h \
    Mathematics/NumericalIntegrators/rungeKutta4thOrderFixedStepsize.h \
    Mathematics/NumericalIntegrators/integrator.h \
    Mathematics/NumericalIntegrators/integratorBase.h \
    Mathematics/NumericalIntegrators/integratorAdaptor.h \
    Mathematics/NumericalIntegrators/euler.h \
    Mathematics/RootFindingMethods/unitTestNewtonRaphson.h \
    Mathematics/RootFindingMethods/rootFinderBase.h \
    Mathematics/RootFindingMethods/rootFinder.h \
    Mathematics/RootFindingMethods/newtonRaphsonBase.h \
    Mathematics/RootFindingMethods/newtonRaphsonAdaptor.h \
    Mathematics/RootFindingMethods/newtonRaphson.h \
    Output/outputHandling.h \
    Output/writingOutputToFile.h
INCLUDEPATH += External/Eigen-2.0.15 \
    Astrodynamics \
    Astrodynamics/Bodies \
    Astrodynamics/Bodies/CelestialBodies \
    Astrodynamics/Bodies/Vehicles \
    Astrodynamics/EnvironmentModels \
    Astrodynamics/EnvironmentModels/GravityFieldModel \
    Astrodynamics/ForceModels \
    Astrodynamics/ForceModels/Aerothermodynamics \
    Astrodynamics/Propagators \
    Astrodynamics/States \
    Astrodynamics/MissionSegments \
    Astrodynamics/MissionSegments/EscapeAndCapture \
    Astrodynamics/MissionSegments/GravityAssist \
    Astrodynamics/MissionSegments/LambertTargeter \
    Basics \
    Mathematics \
    Mathematics/GeometricShapes \
    Mathematics/LinearAlgebra \
    Mathematics/NumericalIntegrators \
    Mathematics/RootFindingMethods \
    Output
